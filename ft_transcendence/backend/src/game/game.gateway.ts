import { UseFilters, UseGuards } from '@nestjs/common';
import {
  SubscribeMessage,
  WebSocketGateway,
  WsException,
} from '@nestjs/websockets';
import { Socket } from 'socket.io';
import { WsGuard } from 'src/auth/guards/ws.guard';
import { GameService } from './game.service';
import { GameRoom, Player, RoomList } from './game.interface';
import { QueueDto } from './dto/queue.dto';
import { MyWsExceptionFilter } from 'src/MyWsExceptionFilter';
import { UserService } from '../user/user.service';

@UseGuards(WsGuard)
@WebSocketGateway({
  cors: true,
  path: '/game',
})
@UseFilters(MyWsExceptionFilter)
export class GameGateway {
  constructor(private gameService: GameService,
    private userService: UserService) {}

  async handleConnection(client: Socket): Promise<any> {
    if (!(await this.gameService.userConnect(client))) {
      console.log('socket has error so game gateway disconnect');
      client.disconnect();
      return ;
    }
    // console.log('game gateway connect');
    const userId = client.data.user.id;
    await this.userService.updateUser({
      where: { id: userId},
      data: { status: 'gamelobby'},
    })
    const roomList = Array.from(this.gameService.simpleGameRoomList.values());
    client.nsp.emit('gameroomlist', roomList);
  }

  async handleDisconnect(client: Socket): Promise<any> {
    // console.log('game gateway disconnect');
    const userId = client.data?.user?.id;
    if (userId) {
      await this.userService.updateUser({
        where: { id: userId},
        data: { status: 'offline'},
      })
    }
  }

  @SubscribeMessage('getgameroomlist')
  getGameRoomList(client: Socket) {
    const roomList = Array.from(this.gameService.simpleGameRoomList.values());
    client.emit('gameroomlist', roomList);
  }

  @SubscribeMessage('queueout')
  async queueout(client: Socket) {
    const deleteRoomNumber = this.gameService.players.get(client.id);
    if (!deleteRoomNumber) {
      throw new WsException('There is no roomNumber setting in players');
    }
    const deleteRoom = this.gameService.gameRoomList.get(deleteRoomNumber);
    if (!deleteRoom) {
      throw new WsException('There is no roomNumber setting in game room list');
    }

    if (deleteRoom) {
      client.leave(deleteRoom.roomnumber);
      this.gameService.simpleGameRoomList.delete(deleteRoomNumber);
      this.gameService.gameRoomList.delete(deleteRoomNumber);
    }
  }

  @SubscribeMessage('queue')
  async queue(client: Socket, data: QueueDto) {
    const { username, nickname } = client.data.user;
    const user: Player = { username: username, nickname: nickname };
    const mapRandomSeed = Math.random() * 3;
    const mapType =
      mapRandomSeed >= 2 ? 'map_0' : mapRandomSeed >= 1 ? 'map_1' : 'map_2';
    const today = Date.now();
    const gameRoomNumber = today + user.username;
    let roomIndex = 0;
    let gameRoomInfo: GameRoom = null;
    let gameRoomList: RoomList = null;

    if (this.gameService.gameRoomList.size !== 0) {
      for (let gameRoom of this.gameService.gameRoomList.values()) {
        roomIndex++;
        if (
          gameRoom.player1 &&
          gameRoom.player2 &&
          roomIndex !== this.gameService.gameRoomList.size
        )
          continue;
        if (
          gameRoom.gametype !== data.gametype &&
          gameRoom.maptype !== data.maptype &&
          roomIndex === this.gameService.gameRoomList.size
        ) {
          gameRoomInfo = {
            player1: user,
            player2: null,
            roomnumber: gameRoomNumber,
            gametype: data.gametype,
            maptype: data.maptype,
            status: 'waiting',
          };
          this.gameService.gameRoomList.set(gameRoomNumber, gameRoomInfo);
          this.gameService.players.set(client.id, gameRoomNumber);
          client.join(gameRoomNumber);
          break;
        } else if (
          gameRoom.gametype === data.gametype &&
          gameRoom.gametype === 'ladder' &&
          gameRoom.player2 === null
        ) {
          gameRoom.player2 = user;
          gameRoom.maptype = mapType;
          gameRoomList = {
            player1UserName: gameRoom.player1.username,
            player1NickName: gameRoom.player1.nickname,
            player2UserName: gameRoom.player2.username,
            player2NickName: gameRoom.player2.nickname,
            roomNumber: gameRoom.roomnumber,
            gameType: gameRoom.gametype,
            mapType: gameRoom.maptype,
          };
          client.join(gameRoom.roomnumber);
          this.gameService.simpleGameRoomList.set(
            gameRoom.roomnumber,
            gameRoomList,
          );
          this.gameService.players.set(client.id, gameRoom.roomnumber);
          client.nsp.to(gameRoom.roomnumber).emit('ready', gameRoom);
          const roomList = Array.from(
            this.gameService.simpleGameRoomList.values(),
          );
          client.nsp.emit('gameroomlist', roomList);
          break;
        } else if (
          gameRoom.gametype === data.gametype &&
          gameRoom.gametype === 'normal' &&
          gameRoom.player2 === null &&
          gameRoom.maptype === data.maptype
        ) {
          gameRoom.player2 = user;
          gameRoomList = {
            player1UserName: gameRoom.player1.username,
            player1NickName: gameRoom.player1.nickname,
            player2UserName: gameRoom.player2.username,
            player2NickName: gameRoom.player2.nickname,
            roomNumber: gameRoom.roomnumber,
            gameType: gameRoom.gametype,
            mapType: gameRoom.maptype,
          };
          client.join(gameRoom.roomnumber);
          this.gameService.simpleGameRoomList.set(
            gameRoom.roomnumber,
            gameRoomList,
          );
          this.gameService.players.set(client.id, gameRoom.roomnumber);
          client.nsp.to(gameRoom.roomnumber).emit('ready', gameRoom);
          const roomList = Array.from(
            this.gameService.simpleGameRoomList.values(),
          );
          client.nsp.emit('gameroomlist', roomList);
          break;
        } else if (roomIndex === this.gameService.gameRoomList.size) {
          gameRoomInfo = {
            player1: user,
            player2: null,
            roomnumber: gameRoomNumber,
            gametype: data.gametype,
            maptype: data.maptype,
            status: 'waiting',
          };
          client.join(gameRoomNumber);
          this.gameService.gameRoomList.set(gameRoomNumber, gameRoomInfo);
          this.gameService.players.set(client.id, gameRoomNumber);
          break;
        }
      }
    } else {
      gameRoomInfo = {
        player1: user,
        player2: null,
        roomnumber: gameRoomNumber,
        gametype: data.gametype,
        maptype: data.maptype,
        status: 'waiting',
      };
      client.join(gameRoomNumber);
      this.gameService.players.set(client.id, gameRoomNumber);
      this.gameService.gameRoomList.set(gameRoomNumber, gameRoomInfo);
    }
  }
}
