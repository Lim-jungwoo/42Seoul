import { UseFilters, UseGuards } from '@nestjs/common';
import {
  OnGatewayConnection,
  OnGatewayDisconnect,
  WebSocketGateway,
  WsException,
} from '@nestjs/websockets';
import { AuthService } from 'src/auth/auth.service';
import { WsGuard } from 'src/auth/guards/ws.guard';
import { MyWsExceptionFilter } from 'src/MyWsExceptionFilter';
import { UserService } from './user.service';
import { Socket } from 'socket.io';

@WebSocketGateway({ path: '/main', cors: true })
@UseFilters(MyWsExceptionFilter)
export class UserGateway implements OnGatewayConnection, OnGatewayDisconnect {
  constructor(
    private readonly userService: UserService,
    private readonly authService: AuthService,
  ) {}

  handleDisconnect(socket: Socket) {
    if (socket.data?.user?.id)
    {
      this.userService.setStatus(socket.data.user.id, 'offline');
      this.userService.sockets.delete(socket.data.user.id);
    }
  }

  async handleConnection(socket: Socket) {
    try {
      if (!(await this.authService.verifySocket(socket)))
        throw new WsException('connection-authorization failed');
      this.userService.setStatus(socket.data.user.id, 'online');
      this.userService.sockets.set(socket.data.user.id, socket);
    } catch (e) {
      socket.disconnect();
      console.log('exception caught', e.error);
    }
  }
}
