import { ChatService } from '../chat.service';

export class Channel {
  private owner: number;
  private admins: Set<number> = new Set();
  private bans: Map<number, Date> = new Map();
  private mutes: Map<number, Date> = new Map();
  private invites: Set<number> = new Set();
  private history = new Array();

  constructor(
    private readonly id: number,
    private readonly name: string,
    private type: string,
    private users: Set<number>,
    private password: string = '',
    private readonly chatService: ChatService,
  ) {
    for (let user of users) {
      if (user) this.owner = user;
    }
    this.admins.add(this.owner);
  }

  addHistory(uid: number, msg: string) {
    this.history.push({ id: uid, msg: msg });
  }

  hasUser(uid: number): boolean {
    return this.users.has(uid);
  }

  addUser(uid: number): boolean {
    if (this.hasUser(uid)) return false;
    this.users.add(uid);
    return true;
  }

  muteUser(uid: number): boolean {
    if (!this.hasUser(uid)) return false;
    const btime: number = +process.env.CHANNEL_MUTE_TIME || 60;

    this.mutes.set(uid, new Date(Date.now() + btime * 1000));
    return true;
  }

  getID() {
    return this.id;
  }

  getActiveUsers() { // will only return "active" users
    let ret = new Set<number>();
    this.users.forEach((val, idx) => {
      const sock = this.chatService.getSocket(val);
      if (sock?.data?.roomInfo?.id === this.getID())
        ret.add(val);
    })

    return ret;
  }

  getUsers() {
    return this.users;
  }

  getHistory() {
    return this.history;
  }

  delUser(uid: number): boolean {
    if (!this.hasUser(uid)) return false;
    this.admins.delete(uid);
    this.users.delete(uid);
    if (this.isOwner(uid)) this.owner = null;
    
    const sock = this.chatService.getSocket(uid);
    if (!sock) return false;

    this.broadcast('userLeave', {
      nick: sock.data.user.nickname,
    })
    return true;
  }

  addAdmin(uid: number): boolean {
    if (!this.hasUser(uid)) return false;
    this.admins.add(uid);
    return true;
  }

  inviteUser(uid: number): void {
    this.invites.add(uid);
  }

  removeInvite(uid: number): boolean {
    if (!this.isInvited(uid)) return false;
    this.invites.delete(uid);
    return true;
  }

  banUser(uid: number) {
    if (!this.hasUser(uid)) return false;
    const btime: number = +process.env.CHANNEL_BAN_TIME || 3600;

    this.bans.set(uid, new Date(Date.now() + btime * 1000));
    return true;
  }

  size(): number {
    return this.users.size;
  }

  getName(): string {
    return this.name;
  }

  getType(): string {
    return this.type;
  }

  checkPassword(pw: string): boolean {
    return pw === this.password;
  }

  setPassword(pw: string) {
    this.password = pw;
  }

  setType(type: string) {
    this.type = type;
  }

  broadcast(event: string, data: any) {
    for (let uid of this.getActiveUsers()) {
      this.chatService.getSocket(uid)?.emit(event, data);
    }
  }

  omit(ouid: number, event: string, data: any) {
    for (let uid of this.getActiveUsers()) {
      if (uid === ouid) continue;
      this.chatService.getSocket(uid)?.emit(event, data);
    }
  }

  isOwner(uid: number): boolean {
    return this.owner === uid;
  }

  isBanned(uid: number): boolean {
    const bt = this.bans.get(uid);
    if (!bt) return false;
    return Date.now() < bt.getTime();
  }

  isProtected(): boolean {
    return this.type === 'protected';
  }

  isPrivate(): boolean {
    return this.type === 'private';
  }

  isInvited(uid: number): boolean {
    return this.invites.has(uid);
  }

  isAdmin(uid: number): boolean {
    return this.admins.has(uid);
  }

  isMuted(uid: number): boolean {
    return this.mutes.has(uid) && this.mutes.get(uid) > new Date();
  }
}
