import { forwardRef, Inject, Injectable } from '@nestjs/common';
import { WsException } from '@nestjs/websockets';
import { AuthService } from 'src/auth/auth.service';
import { Channel } from './channel/channel';
import { Socket } from 'socket.io';
import { UserService } from 'src/user/user.service';
import { User } from '@prisma/client';
import { Server } from 'ws';
import { isAlphanumeric } from 'class-validator';
import { GameService } from 'src/game/game.service';

@Injectable()
export class ChatService {
  private channels: Map<number, Channel> = new Map();
  private sockets: Map<number, Socket> = new Map();
  private counter: number = 1;
  server: Server;

  constructor(
    @Inject(forwardRef(() => AuthService))
    private authService: AuthService,
    @Inject(forwardRef(() => GameService))
    private gameService: GameService,
    @Inject(forwardRef(() => UserService))
    private userService: UserService,
  ) {}

  broadcast(ename: string, data: any = null) {
    if (!this.server) return;
    this.server.emit(ename, data);
  }

  broadcastIn(uid: number, ename: string, data: any = null) {
    if (!this.server) return;
    this.userCurrentChannel(uid)?.broadcast(ename, data);
  }

  async userConnect(socket: Socket): Promise<boolean> {
    const ok = await this.authService.verifySocket(socket);
    if (!ok) return false;
    this.sockets.set(socket.data.user.id, socket);
    return true;
  }

  checkEmptyChannel(cid: number) {
    let chan = this.channels.get(cid);
    if (!chan) return; // maybe throw exception?
    if (!chan.size()) {
      this.delChannel(cid);
    }
  }

  async userDisconnect(socket: Socket): Promise<void> {
    const user = await this.authService.getUserFromSocket(socket);
    if (!user) return;

    if (socket.data.roomInfo) {
      const chan = this.channels.get(socket.data.roomInfo.id);
      if (chan && socket.data.games) {
        for (let [room, tid] of socket.data.games) {
          chan.broadcast('battleUpdated', {
            roomId: room,
            state: 'cancelled',
          });
        }
      }
    }
    this.sockets.delete(user.id);
    this.userService.setStatus(user.id, 'offline');
  }

  checkChannelName(cname: string): boolean {
    let ret: boolean = true;
    const split = cname.split(' ');
    for (let str of split) {
      if (str === '') continue;
      if (!isAlphanumeric(str)) {
        ret = false;
        break;
      }
    }
    return ret;
  }

  createChannel(
    uid: number,
    rid: number,
    cname: string,
    ctype: string,
    pw: string = '',
  ) {
    if (!this.checkChannelName(cname))
      throw new WsException('forbidden char in channel name');
    if (cname.length > 42) throw new WsException('channel name too long');
    if (pw.length > 15) throw new WsException('password too long');
    // if (this.counter < rid) this.counter = rid;
    let chan = new Channel(rid, cname, ctype, new Set([uid]), pw, this);
    this.channels.set(rid, chan);
    if (ctype !== 'private') this.broadcast('channelUpdated');
    // this.counter++;
    return rid;
  }

  newChannelID() {
    return this.counter++;
  }

  listChannels(uid: number) {
    const chans = this.channels;
    let ret = new Array();
    for (let [cid, chan] of chans) {
      if (chan.getType() === 'private' && !chan.hasUser(uid)) continue;
      let data = {
        id: cid,
        type: chan.getType(),
        name: chan.getName(),
        isIn: chan.hasUser(uid),
      };
      ret.push(data);
    }
    ret.sort((a, b) => {
      return b.isIn - a.isIn;
    });
    return ret;
  }

  delChannel(cid: number) {
    this.channels.delete(cid);
    this.server.emit('channelUpdated');
  }

  joinChannel(user: User, cnum: number, password?: string): boolean {
    let chan = this.getChannel(cnum);
    if (!chan) throw new WsException('channel does not exist');
    if (chan.isBanned(user.id)) throw new WsException('banned');
    if (chan.hasUser(user.id)) return true;
    if (chan.isProtected() && !chan.checkPassword(password))
      throw new WsException('wrong password');
    else if (chan.isPrivate() && !chan.isInvited(user.id))
      throw new WsException('not invited');
    const r = chan.addUser(user.id);
    chan.omit(user.id, 'userJoin', {
      nick: user.nickname,
      avatar: user.avatar,
      isAdmin: chan.isAdmin(user.id),
    });
    if (chan.isInvited(user.id)) chan.removeInvite(user.id);
    return r;
  }

  leaveChannel(uid: number, cid: number): boolean {
    // console.log("leaveChannel",uid,typeof cid);
    let chan = this.channels.get(cid);
    if (!chan) throw new WsException('no such channel');
    if (!chan.hasUser(uid)) throw new WsException('user not in channel');
    const r = chan.delUser(uid);
    if (!r) throw new WsException('Failed to leave channel');
    const sock = this.getSocket(uid);
    if (!sock) throw new WsException('critical error in server');
    this.getSocket(uid)?.emit('channelUpdated');
    this.checkEmptyChannel(chan.getID());
    return true;
  }

  userInChannels(uid: number) {
    let ret = [];
    for (const [cid, chan] of this.channels) {
      if (chan.hasUser(uid)) ret[cid] = chan;
    }
    return ret;
  }

  userCurrentChannelID(uid: number) {
    return this.getSocket(uid)?.data?.roomInfo?.id;
  }

  userCurrentChannel(uid: number) {
    return this.channels.get(this.userCurrentChannelID(uid));
  }

  getChannels() {
    let ret = [];
    for (const [cname, chan] of this.channels) {
      ret.push(chan);
    }
    return ret;
  }

  invitedChannels(uid: number) {
    let ret = new Array();
    this.channels.forEach((chan, idx) => {
      if (chan.isInvited(uid))
        ret.push({
          id: idx,
          type: chan.getType(),
          name: chan.getName(),
          isIn: chan.hasUser(uid),
        });
    });
    return ret;
  }

  getChannel(cnum: number) {
    return this.channels.get(cnum);
  }

  getSocket(uid: number) {
    return this.sockets.get(uid);
  }

  async inviteChannel(uid: number, tname: string): Promise<boolean> {
    let chan = this.userCurrentChannel(uid);
    if (!chan) throw new WsException('User not in channel');
    let targ = await this.userService.getUser({ nickname: tname });
    if (!targ) throw new WsException('Tried to invite a ghost (Channel)');
    if (chan.hasUser(targ.id))
      throw new WsException('User is already in the channel');
    chan.inviteUser(targ.id);
    this.getSocket(targ.id)?.emit('channelUpdated');
    return true;
  }

  async inviteGame(user: User, tname: string) {
    if (tname === user.nickname) throw new WsException('Cannot invite self');
    const tuser = await this.userService.getUser({ nickname: tname });
    if (!tuser) throw new WsException('Tried to invite a ghost (Game)');
    const RID = Date.now() + user.username;
    if (
      this.userCurrentChannelID(user.id) !== this.userCurrentChannelID(tuser.id)
    )
      throw new WsException('target is currently not in the same channel');
    const chan = this.userCurrentChannel(user.id);
    if (!chan) throw new WsException('user not in channel');
    const cusers = chan.getActiveUsers();
    cusers.forEach((cuid: number) => {
      const sock = this.getSocket(cuid);
      sock?.emit('battleAlert', {
        user1: {
          avatar: user.avatar,
          nick: user.nickname,
          isMe: user.nickname === sock.data.user.nickname,
        },
        user2: {
          avatar: tuser.avatar,
          nick: tuser.nickname,
          isMe: tuser.nickname === sock.data.user.nickname,
        },
        roomId: RID,
        state: 'pending',
      });
    });

    const usock = this.getSocket(user.id);
    const tsock = this.getSocket(tuser.id);
    if (!usock.data.games) usock.data.games = new Map<string, number>();
    if (!tsock.data.games) tsock.data.games = new Map<string, number>();
    usock.data.games.set(RID, tuser.id);
    tsock.data.games.set(RID, user.id);
    return true;
  }

  confirmGame(user: User, roomID: string, accept: boolean) {
    const usock = this.getSocket(user.id);
    if (!usock.data.games?.get(roomID))
      throw new WsException('not invited to such game');

    const tid = usock.data.games.get(roomID);
    const tsock = this.getSocket(tid);
    const tuser = tsock.data.user;
    if (!tsock) throw new WsException('Target user is a ghost!');
    if (!tuser) throw new WsException('Something went terribly wrong');

    let rid = roomID;

    if (accept) {
      rid = this.gameService.makeRoom({
        player1UserName: user.username,
        player1NickName: user.nickname,
        player2UserName: tuser.username,
        player2NickName: tuser.nickname,
      });
      usock.emit('gameStart', {
        roomId: rid,
      });
      tsock.emit('gameStart', {
        roomId: rid,
      });
    }

    usock.data.games?.delete(roomID);
    tsock.data.games?.delete(roomID);

    this.broadcastIn(tid, 'battleUpdated', {
      roomId: roomID,
      newRoomId: rid,
      state: accept ? 'playing' : 'cancelled',
    });
    return true;
  }

  async isBlocked(uid: number, tid: number): Promise<boolean> {
    const bl = await this.userService.getBlockList(uid);
    for (let block of bl) if (block.tid === uid) return true;
    return false;
  }

  async listUsers(ruid: number) {
    const chan = this.userCurrentChannel(ruid);
    if (!chan) throw new WsException('User not in channel');
    let ret = new Array();

    for await (let uid of chan.getUsers()) {
      const user = await this.userService.getUser({ id: uid });
      if (!user) continue;
      ret.push({
        avatar: user.avatar,
        nick: user.nickname,
        isAdmin: chan.isAdmin(uid),
        isMe: ruid === uid,
        isOwner: chan.isOwner(uid),
      });
    }
    ret.sort((a, b) => {
      return b.isMe - a.isMe;
    });
    return ret;
  }

  async listChat(ruid: number) {
    const chan = this.userCurrentChannel(ruid);
    if (!chan) throw new WsException('User not in channel');
    let ret = new Array();
    let ucache: Map<number, User> = new Map();
    const bs = await this.userService.getBlockSet(ruid);

    for await (let data of chan.getHistory()) {
      const uid = data.id;
      if (!ucache.has(uid))
        ucache.set(uid, await this.userService.getUser({ id: uid }));
      const user = ucache.get(uid);
      if (!user) continue;
      if (bs.has(user.id)) continue;
      ret.push({
        avatar: user.avatar,
        nick: user.nickname,
        msg: data.msg,
        isMe: ruid === uid,
      });
    }
    return ret;
  }

  async muteUser(uid: number, tname: string) {
    const chan = this.userCurrentChannel(uid);
    if (!chan) throw new WsException('User not in channel');
    if (!chan.isAdmin(uid)) throw new WsException('User not admin');
    const targ = await this.userService.getUser({ nickname: tname });
    if (!targ) throw new WsException('Target nickname not found');
    if (!chan.hasUser(targ.id))
      throw new WsException('Target is not in the channel user is in');
    if (chan.isOwner(targ.id)) throw new WsException('target is channel owner');
    return chan.muteUser(targ.id);
  }

  async blockUser(uid: number, tname: string) {
    const tuser = await this.userService.getUser({ nickname: tname });
    if (!tuser) throw new WsException('cannot find target');
    return this.userService.blockUser(uid, tuser.id);
  }

  async kickUser(uid: number, tname: string) {
    const chan = this.userCurrentChannel(uid);
    if (!chan) throw new WsException('User not in channel');
    if (!chan.isAdmin(uid)) throw new WsException('User not admin');
    const targ = await this.userService.getUser({ nickname: tname });
    if (!targ) throw new WsException('Target nickname not found');
    if (chan.isOwner(targ.id)) throw new WsException('target is channel owner');
    if (!chan.hasUser(targ.id))
      throw new WsException('Target is not in the channel user is in');
    if (this.userCurrentChannelID(targ.id) === chan.getID())
      this.getSocket(targ.id)?.disconnect();
    chan.delUser(targ.id);
    // this.leaveChannel(uid, chan.getID());
  }

  updateUser(uid: number, oldnick: string, nick: string, avatar: string) {
    // console.log(oldnick, nick);
    const chans = this.userInChannels(uid);
    chans.forEach((chan, idx) => {
      for (let uid of chan.getActiveUsers()) {
        const sock = this.getSocket(uid);
        sock?.emit('userLeave', {
          nick: oldnick,
        });
        sock?.emit('userJoin', {
          avatar: avatar,
          nick: nick,
          isAdmin: chan.isAdmin(uid),
        });
      }
    });
  }

  async banUser(uid: number, tname: string): Promise<boolean> {
    const chan = this.userCurrentChannel(uid);
    if (!chan) throw new WsException('User not in channel');
    if (!chan.isAdmin(uid)) throw new WsException('User not admin');
    const targ = await this.userService.getUser({ nickname: tname });
    if (!targ) throw new WsException('Target nickname not found');
    if (!chan.hasUser(targ.id))
      throw new WsException('Target is not in the channel user is in');
    if (chan.isOwner(targ.id)) throw new WsException('target is channel owner');
    const r = chan.banUser(targ.id);
    if (!r) throw new WsException('failed to ban user');
    if (this.userCurrentChannelID(targ.id) === chan.getID())
      this.getSocket(targ.id)?.disconnect();
    chan.delUser(targ.id);
    return true;
  }

  async userChat(user: User, msg: string) {
    if (!msg || msg == '') return false;
    const chan = this.userCurrentChannel(user.id);
    if (!chan) throw new WsException('User not in channel');
    if (chan.isMuted(user.id)) throw new WsException('User is muted');
    const users = chan.getActiveUsers();

    chan.addHistory(user.id, msg);
    for await (let tid of users) {
      const bl = await this.userService.getBlockList(tid);
      let blocked = false;
      for (let block of bl) {
        if (block.tid === user.id) {
          blocked = true;
          break;
        }
      }

      if (blocked) continue;
      this.getSocket(tid)?.emit('chat', {
        avatar: user.avatar,
        nick: user.nickname,
        msg: msg,
        isMe: tid === user.id,
      });
    }
    return true;
  }

  async userDM(user: User, tname: string, msg: string): Promise<boolean> {
    if (user.nickname === tname) throw new WsException('self dm');
    const tuser = await this.userService.getUser({ nickname: tname });
    if (!tuser) throw new WsException('target user not found');
    if (
      this.userCurrentChannelID(user.id) !== this.userCurrentChannelID(tuser.id)
    )
      throw new WsException('target is currently not in same channel');
    const sock = this.getSocket(tuser.id);
    const osock = this.getSocket(user.id);
    const bl = await this.userService.getBlockList(tuser.id);
    let blocked = false;
    for (let block of bl) {
      if (block.tid === user.id) {
        blocked = true;
        break;
      }
    }

    if (!blocked) {
      sock?.emit('directChat', {
        avatar: user.avatar,
        nick: user.nickname,
        msg: msg,
      });
    }
    osock?.emit('directChat', {
      avatar: user.avatar,
      nick: user.nickname,
      msg: msg,
      isMe: true,
    });
    return true;
  }

  async setAdmin(uid: number, tname: string) {
    const chan = this.userCurrentChannel(uid);
    if (!chan) throw new WsException('User not in channel');
    if (!chan.isAdmin(uid)) throw new WsException('User not admin');
    const targ = await this.userService.getUser({ nickname: tname });
    if (!targ) throw new WsException('target is a ghost');
    if (!chan.hasUser(targ.id))
      throw new WsException('target is not in channel');
    const r = chan.addAdmin(targ.id);
    if (this.userCurrentChannelID(targ.id) === chan.getID())
      this.getSocket(targ.id)?.emit('setAdmin');
  }

  setPassword(uid: number, npass: string) {
    const chan = this.userCurrentChannel(uid);
    if (!chan) throw new WsException('User not in channel');
    if (!chan.isOwner(uid)) throw new WsException('User is not owener');
    if (chan.isPrivate()) throw new WsException('Channel is private channel');
    chan.setPassword(npass);
    const oldType = chan.getType();
    if (npass === '') chan.setType('public');
    else chan.setType('protected');
    if (oldType !== chan.getType()) this.broadcast('channelUpdated');
    return true;
  }
}
