import { Socket } from 'socket.io-client';

export interface ScoreType {
    player1: string;
    player2: string;
    score1: number;
    score2: number;
}

export interface BallType {
    radius: number;
    positionX: number;
    positionY: number;
}

export interface DisplayType {
    width: number;
    height: number;
}

export interface TrayType {
    height: number;
    positionX: number;
    positionY: number;
    width: number;
}

export interface GameOutType {
    scoreresult: string;
    winner: string;
}

export interface WatchOnePropsType {
    playerNickName: string;
    score: number;
}

export interface WatchTwoPropsType extends WatchOnePropsType {
    spectators: number;
    userType: string;
}

export interface BrickType {
    positionX: number;
    positionY: number;
    width: number;
    height: number;
}

export interface MapInfoType {
    socket: Socket | null;
    brick: BrickType[];
    ballOne: BallType;
    ballTwo: BallType;
    displays: DisplayType;
    traysOne: TrayType;
    traysTwo: TrayType;
    scores: ScoreType;
}

