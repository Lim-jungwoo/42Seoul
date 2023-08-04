import { HttpException, Injectable } from '@nestjs/common';
import { Prisma, User, Block } from '@prisma/client';
import { PrismaService } from 'src/prisma/prisma.service';
import { ConfigService } from '@nestjs/config';
import { FriendRequestService } from 'src/friendRequest/friend-request.service';
import { Socket } from 'socket.io';
import * as crypto from 'crypto';

@Injectable()
export class UserService {
  sockets: Map<number, Socket> = new Map();
  constructor(
    private prisma: PrismaService,
    private config: ConfigService,
    private friendRequestService: FriendRequestService,
  ) {}

  async getUser(userWhereUniqueInput: Prisma.UserWhereUniqueInput) {
    return this.prisma.user.findUnique({
      where: userWhereUniqueInput,
    });
  }

  async getUserProfile(userWhereUniqueInput?: Prisma.UserWhereUniqueInput) {
    return this.prisma.user.findUnique({
      where: userWhereUniqueInput,
      select: {
        email: true,
        username: true,
        nickname: true,
        avatar: true,
        status: true,
        ladderrating: true,
        ladderscore: true,
        tfa: true,
      },
    });
  }

  async getNumberUser() {
    return this.prisma.user.count({});
  }

  async getFiveUser(
    page: {
      currentpage: number;
      nextpage: number;
      firstusername: string;
      lastusername: string;
    },
    userid: number,
  ) {
    const movePage = page.nextpage - page.currentpage;
    const skip = 1;
    const take = movePage >= 0 ? 5 : -5;
    const cursor =
      movePage === 0
        ? null
        : movePage > 0
        ? page.lastusername
        : page.firstusername;
    if (cursor === null) {
      return this.prisma.user.findMany({
        take: take,
        orderBy: {
          username: 'asc',
        },
        where: {
          NOT: {
            id: userid,
          },
        },
        select: {
          email: true,
          username: true,
          nickname: true,
          avatar: true,
          status: true,
          ladderrating: true,
          ladderscore: true,
        },
      });
    }
    return this.prisma.user.findMany({
      skip: skip + (Math.abs(movePage) - 1) * Math.abs(take),
      take: take,
      cursor: { username: cursor },
      orderBy: {
        username: 'asc',
      },
      where: {
        NOT: {
          id: userid,
        },
      },

      select: {
        email: true,
        username: true,
        nickname: true,
        avatar: true,
        status: true,
        ladderrating: true,
        ladderscore: true,
        // tfa: true,
      },
    });
  }

  async checkIsFriend(user1name: string, user2name: string) {
    const usertest = this.prisma.user.findUnique({
      where: { username: user1name },
    });
    const ttt = (await usertest.friends()).find(
      ({ username }) => username === user2name,
    );
    if (ttt) {
      return true;
    }
    return false;
  }

  async getTotalNumberFriend(userid: number) {
    return this.prisma.user.findMany({
      where: { id: userid },
      include: {
        _count: {
          select: { friends: true },
        },
      },
    });
  }

  async getFiveFriend(
    page: {
      currentpage: number;
      nextpage: number;
      firstusername: string;
      lastusername: string;
    },
    userid: number,
  ) {
    const movePage = page.nextpage - page.currentpage;
    const skip = 1;
    const take = movePage >= 0 ? 5 : -5;
    const cursor =
      movePage === 0
        ? null
        : movePage > 0
        ? page.lastusername
        : page.firstusername;
    if (cursor === null) {
      return this.prisma.user.findUnique({
        where: { id: userid },
        select: {
          friends: {
            take: take,
            orderBy: {
              username: 'asc',
            },
            select: {
              email: true,
              username: true,
              nickname: true,
              avatar: true,
              status: true,
              ladderrating: true,
              ladderscore: true,
            },
          },
        },
      });
    }
    return this.prisma.user.findUnique({
      where: { id: userid },
      select: {
        friends: {
          skip: skip + (Math.abs(movePage) - 1) * Math.abs(take),
          take: take,
          cursor: { username: cursor },
          orderBy: {
            username: 'asc',
          },
          select: {
            email: true,
            username: true,
            nickname: true,
            avatar: true,
            status: true,
            ladderrating: true,
            ladderscore: true,
          },
        },
      },
    });
  }

  async getAllRequest(userid: number) {
    const allRequest = await this.prisma.user.findUnique({
      where: { id: userid },
      select: {
        friendsrequests: true,
      },
    });
    return allRequest.friendsrequests;
  }

  async getFiveFriendRequest(
    page: {
      currentpage: number;
      nextpage: number;
      firstusername: string;
      lastusername: string;
    },
    userid: number,
  ) {
    const movePage = page.nextpage - page.currentpage;
    const firstrequestinfo = await this.friendRequestService.getFriendRequest(
      userid,
      page.firstusername,
    );
    const lastrequestinfo = await this.friendRequestService.getFriendRequest(
      userid,
      page.lastusername,
    );
    const firstrequestpk = firstrequestinfo ? firstrequestinfo.requestpk : 0;
    const lastrequestpk = lastrequestinfo ? lastrequestinfo.requestpk : 0;
    if (movePage !== 0 && (!firstrequestpk || !lastrequestpk)) {
      return 'There is no user in friend request';
    }

    const skip = 1;
    const take = movePage >= 0 ? 5 : -5;
    const cursor =
      movePage === 0 ? null : movePage > 0 ? lastrequestpk : firstrequestpk;
    if (cursor === null) {
      return this.prisma.friendRequest.findMany({
        take: take,
        where: { myid: userid },
        orderBy: {
          friendname: 'asc',
        },
      });
    }
    return this.prisma.friendRequest.findMany({
      where: { myid: userid },
      skip: skip + (Math.abs(movePage) - 1) * Math.abs(take),
      take: take,
      cursor: { requestpk: cursor },
      orderBy: {
        friendname: 'asc',
      },
    });
  }

  async getAllFriend(userid: number) {
    const allFriend = await this.prisma.user.findMany({
      where: { id: userid },
      select: {
        friends: {
          select: {
            email: true,
            username: true,
            nickname: true,
            avatar: true,
            status: true,
            ladderrating: true,
            ladderscore: true,
          },
        },
      },
    });
    return allFriend[0].friends;
  }

  async queryUser(
    UI: Prisma.UserWhereUniqueInput,
    Q: Prisma.UserSelect,
  ): Promise<any> {
    return this.prisma.user.findUnique({
      where: UI,
      select: Q,
    });
  }

  async getEmail(
    userWhereUniqueInput: Prisma.UserWhereUniqueInput,
  ): Promise<{ email: string } | null> {
    return await this.prisma.user.findUnique({
      where: userWhereUniqueInput,
      select: {
        email: true,
      },
    });
  }

  async createUser(datar: Prisma.UserCreateInput): Promise<User> {
    return this.prisma.user.create({
      data: {
        id: datar.id,
        email: datar.email,
        username: datar.username,
        nickname: datar.nickname,
        status: 'offline',
      },
    });
  }

  async addFriend(userid: number, friendid: number) {
    return this.prisma.user.update({
      where: { id: userid },
      data: {
        friends: {
          connect: {
            id: friendid,
          },
        },
      },
    });
  }

  async acceptFriend(userinfo: User, friendinfo: User) {
    const user = this.prisma.user.findUnique({
      where: { id: userinfo.id },
    });
    const userRequest = (await user.friendsrequests()).find(
      ({ friendname }) => friendname === friendinfo.username,
    );
    if (!userRequest) {
      return 'There is no friend request matching friend name';
    }

    await this.prisma.user.update({
      where: { id: friendinfo.id },
      data: {
        friends: {
          connect: {
            id: userinfo.id,
          },
        },
      },
    });
    return this.prisma.user.update({
      where: { id: userinfo.id },
      data: {
        friends: {
          connect: {
            id: userRequest.friendid,
          },
        },
      },
    });
  }

  async declineFriend(userid: number, friendName: string) {
    const user = this.prisma.user.findUnique({
      where: { id: userid },
    });
    const userRequest = (await user.friendsrequests()).find(
      ({ friendname }) => friendname === friendName,
    );
    if (!userRequest) {
      return 'There is no friend request matching friend name';
    }

    return this.prisma.friendRequest.delete({
      where: { requestpk: userRequest.requestpk },
    });
  }

  async sendFriendRequest(
    friend: Prisma.UserCreateInput,
    myself: Prisma.UserCreateInput,
  ) {
    const friendInfo = this.prisma.user.findUnique({
      where: { id: friend.id },
    });
    const friendRequest = (await friendInfo.friendsrequests()).find(
      ({ friendname }) => friendname === myself.username,
    );
    const userInfo = this.prisma.user.findUnique({
      where: { id: myself.id },
    });
    const userRequest = (await userInfo.friendsrequests()).find(
      ({ friendname }) => friendname === friend.username,
    );
    if (friendRequest || userRequest) {
      return 'Friend request already exists';
    }
    return this.prisma.user.update({
      where: { id: friend.id },
      data: {
        friendsrequests: {
          create: {
            friendname: myself.username,
            friendid: myself.id,
            myid: friend.id,
          },
        },
      },
    });
  }

  async updateUser(params: {
    // where은 조건문
    // UserWhereUniqueInput은 prisma에서 unique인 value를 확인한다.
    where: Prisma.UserWhereUniqueInput;
    // data에는 새로 업데이트할 column명을 넣는다.
    data: Prisma.UserUpdateInput;
  }) {
    const { where, data } = params;
    await this.prisma.user.update({
      data,
      where,
    });
    return this.getUserProfile(where);
  }

  async deleteUser(where: Prisma.UserWhereUniqueInput): Promise<User> {
    return this.prisma.user.delete({
      where,
    });
  }

  async deleteAllUser() {
    return this.prisma.user.deleteMany({});
  }

  async deleteFriend(userinfo: User, friendinfo: User) {
    await this.prisma.user.update({
      where: { id: userinfo.id },
      data: {
        friends: {
          disconnect: {
            id: friendinfo.id,
          },
        },
      },
    });
    await this.prisma.user.update({
      where: { id: friendinfo.id },
      data: {
        friends: {
          disconnect: {
            id: userinfo.id,
          },
        },
      },
    });
  }

  async generateOTP(
    userWhereUniqueInput: Prisma.UserWhereUniqueInput,
  ): Promise<string> {
    const code = crypto.randomBytes(3).toString('hex');
    // const hash = await bcrypt.hash(code, 10);
    const ecode = this.encrypt(code);
    const time = new Date();

    await this.prisma.user.update({
      where: userWhereUniqueInput,
      data: {
        tfacode: ecode,
        tfatime: time,
      },
    });
    return code;
  }

  encrypt(text: string) {
    let iv = crypto.randomBytes(16);
    let cipher = crypto.createCipheriv(
      'aes-256-cbc',
      Buffer.from(this.config.get<string>('PWEKEY')),
      iv,
    );
    let encrypted = cipher.update(text);

    encrypted = Buffer.concat([encrypted, cipher.final()]);

    return iv.toString('hex') + ':' + encrypted.toString('hex');
  }

  decrypt(text: string) {
    let textParts = text.split(':');
    let iv = Buffer.from(textParts.shift(), 'hex');
    let encryptedText = Buffer.from(textParts.join(':'), 'hex');
    let decipher = crypto.createDecipheriv(
      'aes-256-cbc',
      Buffer.from(this.config.get<string>('PWEKEY')),
      iv,
    );
    let decrypted = decipher.update(encryptedText);

    decrypted = Buffer.concat([decrypted, decipher.final()]);

    return decrypted.toString();
  }

  async checkOTP(
    userWhereUniqueInput: Prisma.UserWhereUniqueInput,
    otp: string,
  ): Promise<boolean> {
    const query = await this.prisma.user.findUnique({
      where: userWhereUniqueInput,
      select: {
        tfacode: true,
        tfatime: true,
      },
    });

    if (!query.tfacode || !query.tfatime)
      throw new HttpException('cannot retrieve otp from DB', 500);

    const ctime = new Date();
    const vtime = new Date(
      query.tfatime.getTime() + this.config.get<number>('TFA_VTIME') * 1000,
    );
    if (ctime > vtime) throw new HttpException('OTP timed out', 403);

    const match = this.decrypt(query.tfacode) === otp;
    if (match) {
      await this.prisma.user.update({
        where: userWhereUniqueInput,
        data: {
          tfacode: null,
          tfatime: null,
        },
      });
      return true;
    }
    return false;
  }

  async checkRefreshToken(uid: number, rtok: string): Promise<Boolean> {
    const query = await this.prisma.user.findUnique({
      where: {
        id: uid,
      },
      select: {
        rtoken: true,
      },
    });
    // return await bcrypt.compare(rtok, query.rtoken);
    return this.decrypt(query.rtoken) === rtok;
  }

  async saveRefreshToken(uid: number, rtok: string): Promise<void> {
    await this.prisma.user.update({
      where: {
        id: uid,
      },
      data: {
        rtoken: rtok,
      },
    });
  }

  async delRefreshToken(uid: number): Promise<void> {
    await this.prisma.user.update({
      where: {
        id: uid,
      },
      data: {
        rtoken: null,
      },
    });
  }

  async updateLTT(uid: number): Promise<void> {
    await this.prisma.user.update({
      where: {
        id: uid,
      },
      data: {
        lasttokentime: new Date(),
      },
    });
  }

  async updateStatus(uid: number, sstr: string): Promise<void> {
    await this.prisma.user.update({
      where: {
        id: uid,
      },
      data: {
        status: sstr,
      },
    });
  }

  async blockUser(id: number, btid: number): Promise<boolean> {
    return Boolean(
      await this.prisma.block.create({
        data: {
          uid: id,
          tid: btid,
        },
      }),
    );
  }

  async getBlockList(id: number): Promise<Block[]> {
    return await this.prisma.block.findMany({
      where: {
        uid: id,
      },
    });
  }

  async getBlockSet(id: number): Promise<Set<number>> {
    const bl = await this.getBlockList(id);
    let ret: Set<number> = new Set();
    bl.forEach((value, idx) => {
      ret.add(value.tid);
    });
    return ret;
  }

  async setStatus(uid: number, newstat: string) {
    await this.prisma.user.update({
      where: {
        id: uid,
      },
      data: {
        status: newstat,
      },
    });
  }
}
