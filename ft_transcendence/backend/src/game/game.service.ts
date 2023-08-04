import {
  Inject,
  forwardRef,
  Injectable,
  SerializeOptions,
} from '@nestjs/common';
import { UserService } from 'src/user/user.service';
import { HistoryService } from 'src/history/history.service';
import { Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';
import { WebSocketServer, WsException } from '@nestjs/websockets';
import { Server } from 'http';
import { Ball, Game, GameRoom, RoomList } from './game.interface';
import { SchedulerRegistry } from '@nestjs/schedule';

@Injectable()
export class GameService {
  constructor(
    private userService: UserService,
    private historyService: HistoryService,
    @Inject(forwardRef(() => AuthService))
    private authService: AuthService,
    private schedulerRegistry: SchedulerRegistry,
  ) {}

  @WebSocketServer()
  server: Server;

  private sockets: Map<number, Socket> = new Map();
  private gamePlaySockets: Map<number, Socket> = new Map();
  public players: Map<string, string> = new Map();
  public gameRoomList: Map<string, GameRoom> = new Map();
  public simpleGameRoomList: Map<string, RoomList> = new Map();

  addNewInterval(
    intervalName: string,
    intervalTime: number,
    gameRoomNumber: string,
    username: string,
  ) {
    const callback = () => {
      this.updateGame(gameRoomNumber, username);
    };

    const interval = setInterval(callback, intervalTime);
    if (!this.schedulerRegistry.doesExist('interval', intervalName))
      this.schedulerRegistry.addInterval(intervalName, interval);
  }

  deleteInterval(intervalName: string) {
    // console.log('delete Interval: ', intervalName);
    this.schedulerRegistry.deleteInterval(intervalName);
  }

  checkInterval(intervalName: string) {
    return this.schedulerRegistry.doesExist('interval', intervalName);
  }

  listAllIntervals() {
    const intervals = this.schedulerRegistry.getIntervals();

    intervals.forEach((key) => console.log(`Interval: ${key}`));
  }

  async userConnect(socket: Socket): Promise<boolean> {
    const ok = await this.authService.verifySocket(socket);
    if (!ok) return false;
    this.sockets.set(socket.data.user.id, socket);
    // console.log("setting socket", socket.id);
    return true;
  }

  async userGamePlayConnect(socket: Socket): Promise<boolean> {
    const ok = await this.authService.verifySocket(socket);
    if (!ok) return false;
    this.gamePlaySockets.set(socket.data.user.id, socket);
    if (this.sockets.get(socket.data.user.id)) {
      // console.log("delete socket", socket.id);
      this.sockets.delete(socket.data.user.id);
    }
    return true;
  }

  getSocket(uid: number) {
    return this.sockets.get(uid);
  }

  getGamePlaySocket(uid: number) {
    return this.gamePlaySockets.get(uid);
  }

  getGameSocketsFirst() {
    let socket: Socket;
    for (let i of this.sockets.values()) {
      socket = i; break;
    }
    return socket;
  }

  deleteRoom(playerName: string) {
    if (this.simpleGameRoomList.size !== 0) {
      for (let i of this.simpleGameRoomList.values()) {
        if (
          i.player1UserName === playerName ||
          i.player2UserName === playerName
        ) {
          this.gameRoomList.delete(i.roomNumber);
          this.simpleGameRoomList.delete(i.roomNumber);
          break;
        }
      }
    }
  }

  // player1 username, nickname, player2 username, nickname을 받고, gameRoomNumber를 리턴
  makeRoom(data: {
    player1UserName: string;
    player1NickName: string;
    player2UserName: string;
    player2NickName: string;
  }) {
    const today = Date.now();
    const gameRoomNumber = today + data.player1UserName;
    const gameType = 'normal';
    const mapType = 'map_0';
    const gameRoomInfo: GameRoom = {
      player1: {
        username: data.player1UserName,
        nickname: data.player1NickName,
      },
      player2: {
        username: data.player2UserName,
        nickname: data.player2NickName,
      },
      roomnumber: gameRoomNumber,
      gametype: gameType,
      maptype: mapType,
      gamemap: JSON.parse(JSON.stringify(Game.gameMapInfo[0])),
      status: 'waiting',
    };
    const gameRoomList: RoomList = {
      player1UserName: data.player1UserName,
      player1NickName: data.player1NickName,
      player2UserName: data.player2UserName,
      player2NickName: data.player2NickName,
      roomNumber: gameRoomNumber,
      gameType: gameType,
      mapType: mapType,
    };
    this.gameRoomList.set(gameRoomNumber, gameRoomInfo);
    this.simpleGameRoomList.set(gameRoomNumber, gameRoomList);
    return gameRoomNumber;
  }

  resetBall(gameRoomNumber: string) {
    // console.log("reset ball event occured", gameRoom.gamemap.ball);
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    const randomX = Math.random();
    const intX =
      randomX * 2 >= 1
        ? randomX
        : randomX >= 0.3
        ? randomX * 2
        : (randomX + 0.1) * 3;
    const random2X = Math.random();
    const int2X =
      random2X * 2 >= 1
        ? random2X
        : random2X >= 0.3
        ? random2X * 2
        : (random2X + 0.1) * 3;
    const randomY = Math.random();
    const intY =
      randomY * 2 >= 1
        ? randomY
        : randomY >= 0.3
        ? randomY * 2
        : (randomY + 0.1) * 3;
    const random2Y = Math.random();
    const int2Y =
      random2Y * 2 >= 1
        ? random2Y
        : random2Y >= 0.3
        ? random2Y * 2
        : (random2Y + 0.1) * 3;

    if (gameRoom.maptype === 'map_0') {
      gameRoom.gamemap.ball = JSON.parse(
        JSON.stringify(Game.gameMapInfo[0].ball),
      );
      gameRoom.gamemap.ball[0].velocityX *=
        randomX * 2 - 1 >= 0 ? intX : intX * -1;
      gameRoom.gamemap.ball[0].velocityY *=
        randomY * 2 - 1 >= 0 ? intY : intY * -1;
    } else if (gameRoom.maptype === 'map_1') {
      gameRoom.gamemap.ball = JSON.parse(
        JSON.stringify(Game.gameMapInfo[1].ball),
      );
      gameRoom.gamemap.ball[0].velocityX *=
        randomX * 2 - 1 >= 0 ? intX : intX * -1;
      gameRoom.gamemap.ball[0].velocityY *=
        randomY * 2 - 1 >= 0 ? intY : intY * -1;
      gameRoom.gamemap.ball[1].velocityX *=
        random2X * 2 - 1 >= 0 ? int2X : int2X * -1;
      gameRoom.gamemap.ball[1].velocityY *=
        random2Y * 2 - 1 >= 0 ? int2Y : int2Y * -1;
    } else if (gameRoom.maptype === 'map_2') {
      gameRoom.gamemap.ball = JSON.parse(
        JSON.stringify(Game.gameMapInfo[2].ball),
      );
      gameRoom.gamemap.ball[0].velocityX *=
        randomX * 2 - 1 >= 0 ? intX : intX * -1;
      gameRoom.gamemap.ball[0].velocityY *=
        randomY * 2 - 1 >= 0 ? intY : intY * -1;
    }
  }

  async stopGame(gameRoomNumber: string, userName: string, loser?: string) {
    // console.log('game is finish, so stop the game');
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }

    const counterName =
      gameRoom.player1.username === userName
        ? gameRoom.player2.username
        : gameRoom.player1.username;
    const myScore =
      gameRoom.player1.username === userName
        ? gameRoom.gamemap.score1
        : gameRoom.gamemap.score2;
    const yourScore =
      gameRoom.player2.username === userName
        ? gameRoom.gamemap.score1
        : gameRoom.gamemap.score2;
    const historyInfo1 = {
      username: userName,
      countername: counterName,
      myscore: myScore,
      yourscore: yourScore,
      gametype: gameRoom.gametype,
      maptype: gameRoom.maptype,
      loser: loser ? loser : null,
    };
    const historyInfo2 = {
      username: counterName,
      countername: userName,
      myscore: yourScore,
      yourscore: myScore,
      gametype: gameRoom.gametype,
      maptype: gameRoom.maptype,
      loser: loser ? loser : null,
    };
    const result1 = await this.addHistory(historyInfo1);
    const result2 = await this.addHistory(historyInfo2);
    // console.log('my ladder result', result1);
    // console.log('counter ladder result', result2);
    const scoreResult = +myScore + ' VS ' + +yourScore;
    const winner = loser
      ? userName === loser
        ? counterName
        : userName
      : myScore > yourScore
      ? userName
      : counterName;
    const winnerNickName = (
      await this.userService.getUser({ username: winner })
    ).nickname;
    const sendHistory = {
      winner: winnerNickName,
      scoreresult: scoreResult,
    };
    // console.log('sending history message ', sendHistory);

    const user = await this.userService.getUser({ username: userName });
    const counter = await this.userService.getUser({ username: counterName });
    user.status = 'online';
    counter.status = 'online';

    gameRoom.player1.socket.nsp
      .to(gameRoom.roomnumber)
      .emit('history', sendHistory);
    this.gameRoomList.delete(gameRoomNumber);
    this.simpleGameRoomList.delete(gameRoomNumber);
  }

  touchWall(
    x: number,
    radius: number,
    width: number,
    gameRoomNumber: string,
    userName: string,
  ) {
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    if (x <= 0 || x + radius * 2 > width) {
      // if (x <= 0) gameRoom.gamemap.ball[0].positionX = 0;
      // else gameRoom.gamemap.ball[0].positionX = gameRoom.gamemap.display.width - radius * 2;
      // gameRoom.gamemap.ball[0].velocityX *= -1;
      // return true;
      if (x <= 0) {
        if (gameRoom.gamemap.score2 < 10) gameRoom.gamemap.score2++;
      } else {
        if (gameRoom.gamemap.score1 < 10) gameRoom.gamemap.score1++;
      }
      gameRoom.player1.socket.nsp.to(gameRoomNumber).emit('score', {
        player1: gameRoom.player1.nickname,
        player2: gameRoom.player2.nickname,
        score1: gameRoom.gamemap.score1,
        score2: gameRoom.gamemap.score2,
      });
      // score가 다 되어 게임이 끝났을 때
      if (
        gameRoom.gamemap.score1 === gameRoom.gamemap.maxscore ||
        gameRoom.gamemap.score2 === gameRoom.gamemap.maxscore
      ) {
        if (this.checkInterval(gameRoomNumber))
          this.deleteInterval(gameRoomNumber);
        return this.stopGame(gameRoomNumber, userName);
      }
      this.resetBall(gameRoomNumber);
    }
  }

  tray(
    ball: { x: number; y: number; radius: number; ballnumber: number },
    tray: { x: number; y: number; w: number; h: number },
    gameroomnumber: string,
    trayDirection: number,
  ) {
    const gameRoom = this.gameRoomList.get(gameroomnumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    return this.touchSide(
      ball.x,
      ball.y,
      ball.radius,
      gameroomnumber,
      ball.ballnumber,
      {
        trayX: tray.x,
        trayY: tray.y,
        trayW: tray.w,
        trayH: tray.h,
      },
      trayDirection,
    );
  }

  touchFloor(
    y: number,
    radius: number,
    height: number,
    gameRoomNumber: string,
    ballnumber: number,
  ) {
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    // 바닥이나 천장에 부딪혔을 때
    if (y <= 0 || y + radius * 2 >= height) {
      if (y <= 0) gameRoom.gamemap.ball[ballnumber].positionY = 0;
      else gameRoom.gamemap.ball[ballnumber].positionY = height - radius * 2;
      gameRoom.gamemap.ball[ballnumber].velocityY *= -1;
      return true;
    }
  }

  touchUpDownSide(
    x: number,
    y: number,
    radius: number,
    gameRoomNumber: string,
    ballnumber: number,
    data: { trayX: number; trayY: number; trayW: number; trayH: number },
  ) {
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }

    if (y + radius > data.trayY + data.trayH) {
      if (
        (x + radius < data.trayX && Math.abs(x + radius - data.trayX) < Math.abs(y + radius - data.trayY -data.trayH) &&
          Math.pow(x + radius - data.trayX, 2) +
            Math.pow(y + radius - data.trayY - data.trayH, 2) <
            Math.pow(radius, 2)) ||
        (data.trayX <= x + radius &&
          x + radius <= data.trayX + data.trayW &&
          Math.abs(y + radius - data.trayY - data.trayH) < Math.abs(radius)) ||
        (data.trayX + data.trayW < x + radius && Math.abs(x + radius - data.trayX - data.trayW) < Math.abs(y + radius - data.trayY -data.trayH) &&
          Math.pow(x + radius - data.trayX - data.trayW, 2) +
            Math.pow(y + radius - data.trayY - data.trayH, 2) <
            Math.pow(radius, 2))
      ) {
        // console.log('touch down side');
        gameRoom.gamemap.ball[ballnumber].velocityY *= -1;
        gameRoom.gamemap.ball[ballnumber].positionY = data.trayY + data.trayH;
        if (
          Math.abs(gameRoom.gamemap.ball[ballnumber].velocityX) < 10 &&
          Math.abs(gameRoom.gamemap.ball[ballnumber].velocityY) < 10
        ) {
          gameRoom.gamemap.ball[ballnumber].velocityX *=
            gameRoom.gamemap.ball[ballnumber].speed;
          gameRoom.gamemap.ball[ballnumber].velocityY *=
            gameRoom.gamemap.ball[ballnumber].speed;
        }
        return true;
      }
    }
    if (y + radius < data.trayY) {
      if (
        (x + radius < data.trayX && Math.abs(x + radius - data.trayX) < Math.abs(y + radius - data.trayY) &&
          Math.pow(x + radius - data.trayX, 2) +
            Math.pow(y + radius - data.trayY, 2) <
            Math.pow(radius, 2)) ||
        (data.trayX <= x + radius &&
          x + radius <= data.trayX + data.trayW &&
          Math.abs(y + radius - data.trayY) < Math.abs(radius)) ||
        (data.trayX + data.trayW < x + radius && Math.abs(x + radius - data.trayX - data.trayW) < Math.abs(y + radius - data.trayY) &&
          Math.pow(x + radius - data.trayX - data.trayW, 2) +
            Math.pow(y + radius - data.trayY, 2) <
            Math.pow(radius, 2))
      ) {
        // console.log('touch up side');
        gameRoom.gamemap.ball[ballnumber].velocityY *= -1;
        gameRoom.gamemap.ball[ballnumber].positionY = data.trayY - radius * 2;
        if (
          Math.abs(gameRoom.gamemap.ball[ballnumber].velocityX) < 10 &&
          Math.abs(gameRoom.gamemap.ball[ballnumber].velocityY) < 10
        ) {
          gameRoom.gamemap.ball[ballnumber].velocityX *=
            gameRoom.gamemap.ball[ballnumber].speed;
          gameRoom.gamemap.ball[ballnumber].velocityY *=
            gameRoom.gamemap.ball[ballnumber].speed;
        }
        return true;
      }
    }
    return false;
  }

  touchLeftSide(
    x: number,
    y: number,
    radius: number,
    gameRoomNumber: string,
    ballnumber: number,
    data: { trayX: number; trayY: number; trayW: number; trayH: number },
  ) {
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    if (
      (y + radius < data.trayY &&
        Math.pow(x + radius - data.trayX, 2) +
          Math.pow(y + radius - data.trayY, 2) <
          Math.pow(radius, 2)) ||
      (data.trayY <= y + radius &&
        y + radius <= data.trayY + data.trayH &&
        Math.abs(x + radius - data.trayX) < Math.abs(radius)) ||
      (data.trayY + data.trayH < y + radius &&
        Math.pow(x + radius - data.trayX, 2) +
          Math.pow(y + radius - data.trayY - data.trayH, 2) <
          Math.pow(radius, 2))
    ) {
      gameRoom.gamemap.ball[ballnumber].velocityX *= -1;
      gameRoom.gamemap.ball[ballnumber].positionX = data.trayX - radius * 2;
      // console.log('touch left side');
      if (
        Math.abs(gameRoom.gamemap.ball[ballnumber].velocityX) < 10 &&
        Math.abs(gameRoom.gamemap.ball[ballnumber].velocityY) < 10
      ) {
        gameRoom.gamemap.ball[ballnumber].velocityX *=
          gameRoom.gamemap.ball[ballnumber].speed;
        gameRoom.gamemap.ball[ballnumber].velocityY *=
          gameRoom.gamemap.ball[ballnumber].speed;
      }
      return true;
    }
    return false;
  }

  touchRightSide(
    x: number,
    y: number,
    radius: number,
    gameRoomNumber: string,
    ballnumber: number,
    data: { trayX: number; trayY: number; trayW: number; trayH: number },
  ) {
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    if (
      (y + radius < data.trayY &&
        Math.pow(x + radius - data.trayX - data.trayW, 2) +
          Math.pow(y + radius - data.trayY, 2) <
          Math.pow(radius, 2)) ||
      (data.trayY <= y + radius &&
        y + radius <= data.trayY + data.trayH &&
        Math.abs(x + radius - data.trayX - data.trayW) < Math.abs(radius)) ||
      (data.trayY + data.trayH < y + radius &&
        Math.pow(x + radius - data.trayX - data.trayW, 2) +
          Math.pow(y + radius - data.trayY - data.trayH, 2) <
          Math.pow(radius, 2))
    ) {
      gameRoom.gamemap.ball[ballnumber].velocityX *= -1;
      gameRoom.gamemap.ball[ballnumber].positionX = data.trayX + data.trayW;
      // console.log('touch right side');
      if (
        Math.abs(gameRoom.gamemap.ball[ballnumber].velocityX) < 10 &&
        Math.abs(gameRoom.gamemap.ball[ballnumber].velocityY) < 10
      ) {
        gameRoom.gamemap.ball[ballnumber].velocityX *=
          gameRoom.gamemap.ball[ballnumber].speed;
        gameRoom.gamemap.ball[ballnumber].velocityY *=
          gameRoom.gamemap.ball[ballnumber].speed;
      }
      return true;
    }
    return false;
  }

  touchSide(
    x: number,
    y: number,
    radius: number,
    gameRoomNumber: string,
    ballnumber: number,
    data: { trayX: number; trayY: number; trayW: number; trayH: number },
    trayDirection: number,
  ) {
    if (!(trayDirection === 1 || trayDirection === 2)) {
      if (this.touchUpDownSide(x, y, radius, gameRoomNumber, ballnumber, {
        trayX: data.trayX,
        trayY: data.trayY,
        trayW: data.trayW,
        trayH: data.trayH,
      }) === true)
        return true;
    }
    const LeftSide: boolean = this.touchLeftSide(
      x,
      y,
      radius,
      gameRoomNumber,
      ballnumber,
      {
        trayX: data.trayX,
        trayY: data.trayY,
        trayW: data.trayW,
        trayH: data.trayH,
      },
    );
    if (LeftSide === true) return true;
    const RightSide: boolean = this.touchRightSide(
      x,
      y,
      radius,
      gameRoomNumber,
      ballnumber,
      {
        trayX: data.trayX,
        trayY: data.trayY,
        trayW: data.trayW,
        trayH: data.trayH,
      },
    );
    if (RightSide === true) return true;
    
  }

  touchBrick(
    x: number,
    y: number,
    radius: number,
    gameRoomNumber: string,
    ballnumber: number,
  ) {
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    const brick1 = gameRoom.gamemap.brick ? gameRoom.gamemap.brick[0] : null;
    const brick2 = gameRoom.gamemap.brick ? gameRoom.gamemap.brick[1] : null;
    if (!brick1 || !brick2) {
      return;
    }
    const brick1X = brick1.positionX;
    const brick1Y = brick1.positionY;
    const brick1W = brick1.width;
    const brick1H = brick1.height;
    const brick2X = brick2.positionX;
    const brick2Y = brick2.positionY;
    const brick2W = brick2.width;
    const brick2H = brick2.height;

    this.touchSide(
      x,
      y,
      radius,
      gameRoomNumber,
      ballnumber,
      {
        trayX: brick1X,
        trayY: brick1Y,
        trayW: brick1W,
        trayH: brick1H,
      },
      0,
    );

    this.touchSide(
      x,
      y,
      radius,
      gameRoomNumber,
      ballnumber,
      {
        trayX: brick2X,
        trayY: brick2Y,
        trayW: brick2W,
        trayH: brick2H,
      },
      0,
    );
  }

  updateGame(gameRoomNumber: string, username: string) {
    const gameRoom = this.gameRoomList.get(gameRoomNumber);
    if (!gameRoom) {
      throw new WsException(
        'There is no gameRoom matching gameRoomNumber',
      );
    }
    if (Game.updateGamePause === true) {
      Game.updateGamePause = false;
      return;
    }
    let nextBallPosition = { x: 0, y: 0 };
    let radius: number;
    let ball: Ball;
    const tray1NextPosition = {
      x: gameRoom.gamemap.tray1.positionX,
      y: gameRoom.gamemap.tray1.positionY,
    };
    const tray2NextPosition = {
      x: gameRoom.gamemap.tray2.positionX,
      y: gameRoom.gamemap.tray2.positionY,
    };
    for (let ballNumber in gameRoom.gamemap.ball) {
      ball = gameRoom.gamemap.ball[ballNumber];
      nextBallPosition = {
        x: ball.positionX + ball.velocityX,
        y: ball.positionY + ball.velocityY,
      };
      radius = ball.radius;
      this.touchWall(
        nextBallPosition.x,
        radius,
        gameRoom.gamemap.display.width,
        gameRoomNumber,
        username,
      );
      if (gameRoom.maptype === 'map_2') {
        this.touchBrick(
          nextBallPosition.x,
          nextBallPosition.y,
          radius,
          gameRoomNumber,
          +ballNumber,
        );
      }
      this.tray(
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
        gameRoomNumber,
        1,
      );
      this.tray(
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
        gameRoomNumber,
        2,
      );
      this.touchFloor(
        nextBallPosition.y,
        radius,
        gameRoom.gamemap.display.height,
        gameRoomNumber,
        +ballNumber,
      );
      gameRoom.gamemap.ball[ballNumber].positionX +=
        gameRoom.gamemap.ball[ballNumber].velocityX;
      gameRoom.gamemap.ball[ballNumber].positionY +=
        gameRoom.gamemap.ball[ballNumber].velocityY;
    }
    gameRoom.player1.socket.nsp
      .to(gameRoomNumber)
      .volatile.emit('ball', gameRoom.gamemap.ball);
  }

  async addHistory(data: {
    username: string;
    countername: string;
    myscore: number;
    yourscore: number;
    gametype: string;
    maptype: string;
    loser: string;
  }) {
    const counterpart = await this.userService.getUser({
      username: data.countername,
    });
    if (!counterpart) {
      return 'There is no user mathcing username';
    }

    const myself = await this.userService.getUser({ username: data.username });
    if (!myself) {
      return 'There is no user matching token';
    }

    const result = data.loser
      ? data.loser === myself.username
        ? 'lose'
        : 'win'
      : data.myscore > data.yourscore
      ? 'win'
      : 'lose';

    let resultLadderScore: number;
    if (data.gametype === 'ladder') {
      if (result === 'win' && myself.ladderscore < 9990) {
        resultLadderScore = myself.ladderscore + 10;
        await this.userService.updateUser({
          where: { username: data.username },
          data: { ladderscore: resultLadderScore },
        });
      } else if (result === 'lose' && myself.ladderscore >= 10) {
        resultLadderScore = myself.ladderscore - 10;
        await this.userService.updateUser({
          where: { username: data.username },
          data: { ladderscore: resultLadderScore },
        });
      }
    }

    if (myself.ladderrating === 'Bronze' && resultLadderScore >= 100) {
      await this.userService.updateUser({
        where: { username: data.username },
        data: { ladderrating: 'Silver' },
      });
    } else if (myself.ladderrating === 'Silver' && resultLadderScore >= 200) {
      await this.userService.updateUser({
        where: { username: data.username },
        data: { ladderrating: 'Gold' },
      });
    } else if (myself.ladderrating === 'Gold' && resultLadderScore < 200) {
      await this.userService.updateUser({
        where: { username: data.username },
        data: { ladderrating: 'Silver' },
      });
    } else if (myself.ladderrating === 'Silver' && resultLadderScore < 100) {
      await this.userService.updateUser({
        where: { username: data.username },
        data: { ladderrating: 'Bronze' },
      });
    }

    const historyResult = await this.historyService.createHistory({
      yourid: counterpart.id,
      yournickname: counterpart.nickname,
      result: result,
      myscore: data.myscore,
      yourscore: data.yourscore,
      scoreresult: data.myscore.toString() + ' VS ' + data.yourscore.toString(),
      type: data.gametype,
      maptype: data.maptype,
      user: {
        connect: { id: myself.id },
      },
    });
    return historyResult;
  }
}
