import { MailerService } from '@nestjs-modules/mailer';
import { forwardRef, HttpException, Inject, Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { JwtService } from '@nestjs/jwt';
import { User } from '@prisma/client';
import { FortyTwoUserProfile } from 'src/user/user.interface';
import { UserService } from 'src/user/user.service';
import { Socket } from 'socket.io';
import { ChatService } from 'src/chat/chat.service';
import { GameService } from 'src/game/game.service';

@Injectable()
export class AuthService {
  constructor(
    private jwtService: JwtService,
    private userService: UserService,
    private config: ConfigService,
    private mailerService: MailerService,
    @Inject(forwardRef(() => ChatService))
    private chatService: ChatService,
    @Inject(forwardRef(() => GameService))
    private gameService: GameService,
  ) {}

  verifyJWT(token: string) {
    try {
      return this.jwtService.verify(token);
    } catch (err) {
      console.log('jwt verify failed');
      return;
    }
  }

  verifyRJWT(token: string) {
    try {
      return this.jwtService.verify(token, {
        secret: this.config.get<string>('JWTREF_SECRET'),
      });
    } catch (err) {
      console.log('jwt ref verify failed');
      return;
    }
  }

  async getUserFromSocket(socket: Socket): Promise<User> {
    const aheader = socket.handshake?.headers?.authorization;
    const jwt = aheader && aheader.split(' ')[1];
    if (!jwt) return;
    const payload = this.verifyRJWT(jwt);
    if (!payload) return;
    const user = await this.userService.getUser({ id: +payload.sub });
    if (!user) return;
    if (user.rtoken !== jwt) return;
    return user;
  }

  async verifySocket(socket: Socket): Promise<boolean> {
    const user = await this.getUserFromSocket(socket);
    if (!user) return false;
    socket.data.user = user;
    return true;
  }

  async logout(uid: number): Promise<void> {
    this.userService.delRefreshToken(uid);
    this.userService.updateStatus(uid, 'offline');
  }

  async genAuthToken(uid: number, tfa: boolean): Promise<string> {
    this.userService.updateLTT(uid);
    return this.jwtService.signAsync(
      {
        sub: uid,
        tfa_done: tfa,
      },
      {
        secret: this.config.get<string>('JWT_SECRET'),
        expiresIn: this.config.get<string>('JWT_VTIME'),
      },
    );
  }

  async genRefreshToken(uid: number, tfa: boolean): Promise<string> {
    const token = this.jwtService.sign(
      {
        sub: uid,
        tfa_done: tfa,
      },
      {
        secret: this.config.get<string>('JWTREF_SECRET'),
        expiresIn: this.config.get<string>('JWTREF_VTIME'),
      },
    );

    await this.userService.saveRefreshToken(uid, token);
    return token;
  }

  async checkRefreshToken(uid: number, token: string) {
    const dbt = await this.userService.queryUser({ id: uid }, { rtoken: true });
    if (!dbt?.rtoken) throw new HttpException('no such user in DB', 500);
    return dbt.rtoken === token;
  }

  async refreshAuthToken(
    uid: number,
    tfa_done: boolean,
    rtok: string,
  ): Promise<{ accessToken: string }> {
    if (!this.verifyRJWT(rtok)) throw new HttpException('token invalid', 401);
    if (!(await this.checkRefreshToken(uid, rtok)))
      throw new HttpException('token invalidated', 401);
    const token = await this.genAuthToken(uid, tfa_done);
    return {
      accessToken: token,
    };
  }

  async login(
    user: FortyTwoUserProfile,
  ): Promise<{
    accessToken: string;
    refreshToken: string;
    tfa: boolean;
    isFirst: boolean;
  }> {
    const iid = +user.id;

    let udb: User = await this.userService.getUser({ id: iid });
    let isNew: boolean = false;

    if (!udb) {
      udb = await this.userService.createUser(user);
      isNew = true;
    }
    // else this.userService.updateStatus(iid, 'online');

    this.chatService.getSocket(iid)?.emit('goHome');
    this.gameService.getSocket(iid)?.emit('goHome');
    this.userService.sockets.get(iid)?.emit('goHome');
    this.gameService.getGamePlaySocket(iid)?.emit('goHome');
    // const token = this.jwtService.sign({ sub: user.id, tfa_done: false });
    const token = await this.genAuthToken(user.id, !udb.tfa);
    const rtoken = await this.genRefreshToken(user.id, !udb.tfa);

    return {
      accessToken: token,
      refreshToken: rtoken,
      tfa: udb.tfa,
      isFirst: isNew,
    };
  }

  signTFA(uid: number): string {
    return this.jwtService.sign({ sub: uid, tfa_done: true });
  }

  async loginOTP(uid: number, otp: string): Promise<boolean> {
    return this.userService.checkOTP({ id: uid }, otp);
  }

  async setOTP(uid: number): Promise<void> {
    const code = await this.userService.generateOTP({ id: uid });
    const mail = await this.getEmail(uid);
    this.sendMail(mail.email, code);
  }

  async getEmail(ids: number): Promise<{ email: string }> {
    return this.userService.getEmail({ id: ids });
    // return query.email;
  }

  async sendMail(email: string, code: string) {
    // console.log(email, code);
    try {
      this.mailerService.sendMail({
        to: email,
        from: 'ts_42@naver.com', // hardcoded, can't modify anyway
        subject: 'TS 이메일 인증 코드',
        html: 'code: [' + code + ']\n',
      });
    } catch (err) {
      console.log(err);
    }
  }
}
