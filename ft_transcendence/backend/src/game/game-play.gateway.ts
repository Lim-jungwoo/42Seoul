import {
  SubscribeMessage,
  WebSocketGateway,
  WsException,
} from '@nestjs/websockets';
import { UserService } from 'src/user/user.service';
import { GameService } from './game.service';
import { Socket } from 'socket.io';
import { Ball, Game, GameRoom, Player, RoomList } from './game.interface';
import { UseFilters, UseGuards } from '@nestjs/common';
import { WsGuard } from 'src/auth/guards/ws.guard';
import { InputDto } from './dto/input.dto';
import { MyWsExceptionFilter } from 'src/MyWsExceptionFilter';

@UseGuards(WsGuard)
@WebSocketGateway({
  cors: true,
  path: '/gameplay',
})
@UseFilters(MyWsExceptionFilter)
export class GamePlayGateway {
  constructor(
    private userService: UserService,
    private gameService: GameService,
  ) {}

  // key: socket id, value: roomnumber
  private spectators: Map<string, string> = new Map();

  async handleConnection(client: Socket): Promise<any> {
    if (!(await this.gameService.userGamePlayConnect(client))) {
      console.log('socket has error so game play gateway disconnect');
      client.disconnect();
      return ;
    }
    const roomList = Array.from(this.gameService.simpleGameRoomList.values());
    await this.userService.updateUser({
      where: { username: client.data.user.username },
      data: { status: 'playing' },
    });
    const socket = this.gameService.getGameSocketsFirst();
    if (socket)
      socket.nsp.emit('gameroomlist', roomList);
    // console.log('game play gateway connect');
    client.emit('connect_complete');
  }

  async handleDisconnect(client: Socket): Promise<any> {
    // console.log('game play gateway disconnect');

    let username: string;
    if (client.data.user) {
      username = client.data.user.username;
    } else {
      console.log('There is no user data in socket');
      return;
    }
    let stopRoom: GameRoom = null;
    let findRoom: GameRoom = null;
    let roomNumber: string = null;
    if (this.gameService.gameRoomList.size !== 0) {
      for (let gameRoom of this.gameService.gameRoomList.values()) {
        if (
          (gameRoom.player1 &&
            gameRoom.player1.socket &&
            gameRoom.player1.socket.id === client.id) ||
          (gameRoom.player2 &&
            gameRoom.player2.socket &&
            gameRoom.player2.socket.id === client.id)
        ) {
          stopRoom = gameRoom;
          break;
        }
      }
      roomNumber = this.spectators.get(client.id);
      if (roomNumber) {
        findRoom = this.gameService.gameRoomList.get(roomNumber);
        this.spectators.delete(client.id);
      }
    }
    let spectator: Player = null;
    let spectatorsNumber: Number = 0;
    if (findRoom && findRoom.spectators) {
      spectator = findRoom.spectators.find(
        (spec) => spec.socket.id === client.id,
      );

      if (spectator) {
        findRoom.spectators = findRoom.spectators.filter(
          (spec) => spec.socket.id !== spectator.socket.id,
        );
      }
      spectatorsNumber =
        findRoom.spectators.length >= 1 ? findRoom.spectators.length : 0;
      client.to(findRoom.roomnumber).emit('spectators', spectatorsNumber);
      client.leave(findRoom.roomnumber);
    }

    if (stopRoom) {
      // console.log(stopRoom.roomnumber);
      if (this.gameService.checkInterval(stopRoom.roomnumber)) {
        this.gameService.deleteInterval(stopRoom.roomnumber);
      }
      this.gameService.stopGame(stopRoom.roomnumber, username, username);
    }
    await this.userService.updateUser({
      where: { username: client.data.user.username },
      data: { status: 'offline' },
    });
  }

  @SubscribeMessage('getspectators')
  getSpectators(client: Socket, roomnumber: string) {
    if (!roomnumber)
      throw new WsException('In getspectators, roomnumber cannot be null');
    const gameRoom = this.gameService.gameRoomList.get(roomnumber);

    if (!gameRoom) {
      throw new WsException('There is no game room matching roomnumber');
    }

    const spectatorsNumber =
      gameRoom.spectators.length >= 1 ? gameRoom.spectators.length : 0;
    client.nsp.to(gameRoom.roomnumber).emit('spectators', spectatorsNumber);
  }

  @SubscribeMessage('roomnumber')
  async getRoomNumber(client: Socket, data: { roomnumber: string }) {
    if (!data?.roomnumber)
      throw new WsException('In roomnumber, data.roomnumber cannot be null');
    const playerName = client.data.user.username;
    let findRoom: GameRoom = null;
    if (this.gameService.gameRoomList.size !== 0) {
      findRoom = this.gameService.gameRoomList.get(data.roomnumber);
    }
    if (!findRoom) {
      this.gameService.deleteRoom(playerName);
      throw new WsException('there is no roomnumber matching data roomnumber');
    }

    if (findRoom.player1.username === playerName) {
      findRoom.player1.socket = client;
    } else if (findRoom.player2.username === playerName) {
      findRoom.player2.socket = client;
    }

    // room으로 player들을 넣어준다.
    client.join(findRoom.roomnumber);
    // gamemap의 정보를 넣어준다.
    if (findRoom.maptype === 'map_0')
      findRoom.gamemap = JSON.parse(JSON.stringify(Game.gameMapInfo[0]));
    else if (findRoom.maptype === 'map_1')
      findRoom.gamemap = JSON.parse(JSON.stringify(Game.gameMapInfo[1]));
    else if (findRoom.maptype === 'map_2')
      findRoom.gamemap = JSON.parse(JSON.stringify(Game.gameMapInfo[2]));

    for (let ball of findRoom.gamemap.ball) {
      ball.velocityX *= Math.random() * 2 >= 1 ? -1 : 1;
      ball.velocityY *= Math.random() * 2 >= 1 ? -1 : 1;
    }

    // 처음 game map 정보를 뿌려준다.
    client.emit(
      'roominfo',
      findRoom.gamemap,
      findRoom.player1.nickname,
      findRoom.player2.nickname,
    );
  }

  @SubscribeMessage('watch')
  async watch(client: Socket, roomnumber: string) {
    if (!roomnumber) throw new WsException('roomnumber cannot be null');
    const { username, nickname } = client.data.user;
    const user: Player = {
      username: username,
      nickname: nickname,
      socket: client,
    };
    const findRoom = this.gameService.gameRoomList.get(roomnumber);
    if (!findRoom || (findRoom && findRoom.player2 === null)) {
      throw new WsException('user is not playing a game');
    }

    client.join(findRoom.roomnumber);
    if (!findRoom.spectators) {
      findRoom.spectators = [user];
    } else {
      findRoom.spectators.push(user);
    }
    this.spectators.set(client.id, findRoom.roomnumber);
    const spectatorsNumber = findRoom.spectators.length || 0;
    client.nsp.to(findRoom.roomnumber).emit('spectators', spectatorsNumber);
    await this.userService.updateUser({
      where: { username: client.data.user.username },
      data: { status: 'watching' },
    });
    client.emit(
      'watch_display',
      findRoom.gamemap,
      findRoom.player1.nickname,
      findRoom.player2.nickname,
    );
  }

  GameLoop(gameRoomNumber: string, username: string) {
    if (!gameRoomNumber || !username)
      throw new WsException(
        'In GameLoop, gameRoomNumber or username cannot be null',
      );
    if (!this.gameService.checkInterval(gameRoomNumber))
      this.gameService.addNewInterval(
        gameRoomNumber,
        16,
        gameRoomNumber,
        username,
      );
  }

  @SubscribeMessage('gamestart')
  async gameStart(client: Socket, data: { roomnumber: string }) {
    const playerName = client.data.user.username;
    if (!data?.roomnumber) {
      this.gameService.deleteRoom(playerName);
      throw new WsException('data.roomnumber cannot be null');
    }
    const findRoom = this.gameService.gameRoomList.get(data.roomnumber);
    if (!findRoom) {
      this.gameService.deleteRoom(playerName);
      throw new WsException('There is no room matching gameroom number');
    }
    if (findRoom.status === 'playing') {
      this.GameLoop(findRoom.roomnumber, findRoom.player1.username);
    }
    findRoom.status = 'playing';
  }

  @SubscribeMessage('input')
  input(client: Socket, data: InputDto) {
    const gameRoom = this.gameService.gameRoomList.get(data.roomnumber);
    if (!gameRoom) {
      // console.log('There is no game room mathcing roomnumber');
      return;
    }

    const tray1NextPosition = {
      x: gameRoom.gamemap.tray1.positionX,
      y: gameRoom.gamemap.tray1.positionY,
    };
    const tray2NextPosition = {
      x: gameRoom.gamemap.tray2.positionX,
      y: gameRoom.gamemap.tray2.positionY,
    };

    if (gameRoom.player1.socket === client) {
      if (
        data.up === true &&
        gameRoom.gamemap.tray1.positionY +
          gameRoom.gamemap.tray1.height +
          gameRoom.gamemap.tray1.speed <=
          gameRoom.gamemap.display.height
      ) {
        tray1NextPosition.y += gameRoom.gamemap.tray1.speed;
      } else if (
        data.down === true &&
        gameRoom.gamemap.tray1.positionY - gameRoom.gamemap.tray1.speed >= 0
      ) {
        tray1NextPosition.y -= gameRoom.gamemap.tray1.speed;
      }
    }
    if (gameRoom.player2.socket === client) {
      if (
        data.up === true &&
        gameRoom.gamemap.tray2.positionY +
          +gameRoom.gamemap.tray2.height +
          gameRoom.gamemap.tray2.speed <=
          gameRoom.gamemap.display.height
      ) {
        tray2NextPosition.y += gameRoom.gamemap.tray2.speed;
      } else if (
        data.down === true &&
        gameRoom.gamemap.tray2.positionY - gameRoom.gamemap.tray2.speed >= 0
      ) {
        tray2NextPosition.y -= gameRoom.gamemap.tray2.speed;
      }
    }
    let nextBallPosition = { x: 0, y: 0 };
    let radius: number;
    let ball: Ball;
    let tray1Conflict: boolean;
    let tray2Conflict: boolean;
    for (let ballNumber in gameRoom.gamemap.ball) {
      ball = gameRoom.gamemap.ball[ballNumber];
      nextBallPosition = {
        x: ball.positionX + ball.velocityX,
        y: ball.positionY + ball.velocityY,
      };
      radius = ball.radius;
      tray1Conflict = this.gameService.tray(
        {
          x: nextBallPosition.x,
          y: nextBallPosition.y,
          radius: radius,
          ballnumber: +ballNumber,
        },
        {
          x: tray1NextPosition.x,
          y: tray1NextPosition.y,
          w: gameRoom.gamemap.tray1.width,
          h: gameRoom.gamemap.tray1.height,
        },
        data.roomnumber,
        1,
      );
      tray2Conflict = this.gameService.tray(
        {
          x: nextBallPosition.x,
          y: nextBallPosition.y,
          radius: radius,
          ballnumber: +ballNumber,
        },
        {
          x: tray2NextPosition.x,
          y: tray2NextPosition.y,
          w: gameRoom.gamemap.tray2.width,
          h: gameRoom.gamemap.tray2.height,
        },
        data.roomnumber,
        2,
      );
      if (tray1Conflict === true || tray2Conflict) {
        Game.updateGamePause = true;
      } else {
        gameRoom.gamemap.tray1.positionY = tray1NextPosition.y;
        gameRoom.gamemap.tray2.positionY = tray2NextPosition.y;
      }
    }
    gameRoom.player1.socket.nsp
      .to(data.roomnumber)
      .emit('playing', gameRoom.gamemap.tray1, gameRoom.gamemap.tray2);
  }
}
