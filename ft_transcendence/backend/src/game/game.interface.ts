import { Socket } from 'socket.io';

export interface Player {
  username: string;
  nickname: string;
  socket?: Socket;
}

export interface GameRoom {
  player1: Player;
  player2: Player;
  spectators?: Array<Player>;
  roomnumber: string;
  gametype: string;
  maptype: string;
  gamemap?: GameMapInfo;
  status: string;
}

export interface Display {
  width: number;
  height: number;
}

export interface Ball {
  radius: number;
  positionX: number;
  positionY: number;
  velocityX: number;
  velocityY: number;
  speed: number;
}

export interface Tray {
  width: number;
  height: number;
  positionX: number;
  positionY: number;
  speed: number;
}

export interface Input {
  up: boolean;
  down: boolean;
}

export interface Brick {
  positionX: number;
  positionY: number;
  width: number;
  height: number;
}

export interface GameMapInfo {
  display: Display;
  ball: Ball[];
  tray1: Tray;
  tray2: Tray;
  score1: number;
  score2: number;
  brick: Brick[];
  maxscore: number;
  input: Input;
}

export interface RoomList {
  player1UserName: string;
  player1NickName: string;
  player2UserName: string;
  player2NickName: string;
  roomNumber: string;
  gameType: string;
  mapType: string;
}

export namespace Game {
  export const sleep = (ms: number) => new Promise((r) => setTimeout(r, ms));
  export let updateGamePause = false;
  export const gameMapInfo: GameMapInfo[] = [
    {
      tray1: {
        width: 20,
        height: 200,
        positionX: 0,
        positionY: 280,
        speed: 20,
      },
      tray2: {
        width: 20,
        height: 200,
        positionX: 980,
        positionY: 280,
        speed: 20,
      },
      display: { width: 1000, height: 700 },
      ball: [
        {
          radius: 10,
          positionX: 480,
          positionY: 330,
          velocityX: 3,
          velocityY: 3,
          speed: 1.1,
        },
      ],
      brick: null,
      score1: 0,
      score2: 0,
      maxscore: 10,
      input: { up: false, down: false },
    },
    {
      tray1: {
        width: 20,
        height: 200,
        positionX: 0,
        positionY: 280,
        speed: 20,
      },
      tray2: {
        width: 20,
        height: 200,
        positionX: 980,
        positionY: 280,
        speed: 20,
      },
      display: { width: 1000, height: 700 },
      ball: [
        {
          radius: 10,
          positionX: 400,
          positionY: 340,
          velocityX: 3,
          velocityY: 3,
          speed: 1.1,
        },
        {
          radius: 10,
          positionX: 600,
          positionY: 340,
          velocityX: 3,
          velocityY: 3,
          speed: 1.1,
        },
      ],
      score1: 0,
      score2: 0,
      brick: null,
      maxscore: 10,
      input: { up: false, down: false },
    },
    {
      tray1: {
        width: 20,
        height: 200,
        positionX: 0,
        positionY: 280,
        speed: 20,
      },
      tray2: {
        width: 20,
        height: 200,
        positionX: 980,
        positionY: 280,
        speed: 20,
      },
      display: { width: 1000, height: 700 },
      ball: [
        {
          radius: 10,
          positionX: 480,
          positionY: 330,
          velocityX: 3,
          velocityY: 3,
          speed: 1.1,
        },
      ],
      score1: 0,
      score2: 0,
      brick: [
        { positionX: 480, positionY: 100, width: 40, height: 150 },
        { positionX: 480, positionY: 450, width: 40, height: 150 },
      ],
      maxscore: 10,
      input: { up: false, down: false },
    },
  ];
}
