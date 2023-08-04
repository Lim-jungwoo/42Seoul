import {
  UseFilters,
  UseGuards,
  UsePipes,
  ValidationPipe,
} from '@nestjs/common';
import {
  MessageBody,
  OnGatewayConnection,
  OnGatewayDisconnect,
  OnGatewayInit,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
  WsException,
} from '@nestjs/websockets';
import { Socket } from 'socket.io';
import { WsGuard } from 'src/auth/guards/ws.guard';
import { ChatService } from './chat.service';
import { MyWsExceptionFilter } from 'src/MyWsExceptionFilter';
import { Server } from 'ws';
import { msgDataDTO } from './dto/msgData.dto';
import { msgNickDTO } from './dto/msgNick.dto';
import { msgDataNickDTO } from './dto/msgDataNick.dto';
import { msgBattleAlertDTO } from './dto/msgBattleAlert.dto';
import { msgPasswordDTO } from './dto/msgPassword.dto';
import { validate } from 'class-validator';
import { UserService } from 'src/user/user.service';
import { msgCIDDTO } from './dto/msgCID.dto';

@WebSocketGateway({ path: '/chat', cors: true })
@UseGuards(WsGuard)
@UseFilters(MyWsExceptionFilter)
export class ChatGateway
  implements OnGatewayConnection, OnGatewayDisconnect, OnGatewayInit
{
  @WebSocketServer() server: Server;
  constructor(
    private readonly chatService: ChatService,
    private readonly userService: UserService,
  ) {}

  afterInit(server: Server) {
    this.chatService.server = server;
  }

  async handleConnection(socket: Socket): Promise<void> {
    try {
      socket.data = {};
      if (!(await this.chatService.userConnect(socket)))
        throw new WsException('connection-authorization failed');

      // query에 room info가 있다면 방 생성, 참가 처리, socket.data.room에 저장
      // 없다면 아무것도 하지 않음.
      const query: any = socket.handshake?.query;

      const rid: number = +query?.id;
      const name = query?.name as string;
      const pass = query?.password as string;
      const type: 'public' | 'private' | 'protected' = query?.type;
      if (rid) {
        if (this.chatService.getChannel(rid)) {
          if (!this.chatService.joinChannel(socket.data.user, rid, pass))
            throw new WsException('failed to join channel');
        } else {
          if (
            !name ||
            !type ||
            (type === 'protected' && (!pass || pass === ''))
          ) {
            throw new WsException('protected room and no password provided');
          }
          if (
            !this.chatService.createChannel(
              socket.data.user.id,
              rid,
              name,
              type,
              pass,
            )
          ) {
            throw new WsException('failed to create channel');
          }
        }

        socket.data.roomInfo = {
          id: rid,
        };
        this.userService.setStatus(socket.data.user.id, 'chatting');
      } else this.userService.setStatus(socket.data.user.id, 'chat lobby');

      socket.emit('connectionCompleted');
    } catch (err) {
      socket.disconnect();
      console.log('exception caught', err.error);
    }
  }

  handleDisconnect(socket: Socket): void {
    // console.log('disconnect', socket.data?.user?.id, socket.id);
    this.chatService.userDisconnect(socket);
  }

  @SubscribeMessage('newChannelID')
  newChannelID(client: Socket) {
    return this.chatService.newChannelID();
  }

  @SubscribeMessage('channelList')
  channelList(client: Socket) {
    return this.chatService.listChannels(client.data.user.id);
  }

  @SubscribeMessage('channelLeave')
  channelLeave(client: Socket, data: msgCIDDTO) {
    // transform not working
    if (!this.chatService.leaveChannel(client.data.user.id, +data.id))
      throw new WsException('failed to leave channel');
    return true;
  }

  @SubscribeMessage('invitedList')
  invitedList(client: Socket) {
    return this.chatService.invitedChannels(client.data.user.id);
  }

  // IN-CHANNEL

  @SubscribeMessage('userList')
  async userList(client: Socket) {
    return this.chatService.listUsers(client.data.user.id);
  }

  @SubscribeMessage('chatList')
  async chatList(client: Socket) {
    return this.chatService.listChat(client.data.user.id);
  }

  @SubscribeMessage('mute')
  async muteUser(client: Socket, data: msgNickDTO) {
    return this.chatService.muteUser(client.data.user.id, data.nick);
  }

  @SubscribeMessage('kick')
  async kickUser(client: Socket, data: msgNickDTO) {
    return this.chatService.kickUser(client.data.user.id, data.nick);
  }

  @SubscribeMessage('ban')
  async banUser(client: Socket, data: msgNickDTO) {
    return this.chatService.banUser(client.data.user.id, data.nick);
  }

  @SubscribeMessage('chat')
  async userChat(client: Socket, data: msgDataDTO) {
    return await this.chatService.userChat(client.data.user, data.msg);
  }

  @SubscribeMessage('directChat')
  async userDM(client: Socket, data: msgDataNickDTO) {
    return await this.chatService.userDM(client.data.user, data.nick, data.msg);
  }

  @SubscribeMessage('roomInvite')
  inviteUser(client: Socket, data: msgNickDTO) {
    return this.chatService.inviteChannel(client.data.user.id, data.nick);
  }

  @SubscribeMessage('setAdmin')
  async setAdmin(client: Socket, data: msgNickDTO) {
    return this.chatService.setAdmin(client.data.user.id, data.nick);
  }

  @SubscribeMessage('block')
  async blockUser(client: Socket, data: msgNickDTO) {
    return this.chatService.blockUser(client.data.user.id, data.nick);
  }

  @SubscribeMessage('setPassword')
  setPassword(client: Socket, data: msgPasswordDTO) {
    return this.chatService.setPassword(client.data.user.id, data.password);
  }

  @SubscribeMessage('gameInvite')
  async gameInvite(client: Socket, data: msgNickDTO) {
    return await this.chatService.inviteGame(client.data.user, data.nick);
  }

  @SubscribeMessage('battleAccept')
  gameAccept(client: Socket, data: msgBattleAlertDTO) {
    return this.chatService.confirmGame(
      client.data.user,
      data.roomId,
      data.accept,
    );
  }
}
