import { Socket } from 'socket.io-client';

export interface GameLadderType {
    nickname: string;
    username: string;
    ladderrating: string;
    ladderscore: number;
}

export interface GameWatchList {
    gameType: string;
    mapType: string;
    roomNumber: string;
    player1NickName: string;
    player1UserName: string;
    player2NickName: string;
    player2UserName: string;
}

export interface WatchPropsType {
    gameMainSocket: Socket;
    nabiNum: number;
}

export interface GameModalPropsType {
    gameMainSocket: Socket;
    roomData: string;
    setOpenGameModal: React.Dispatch<React.SetStateAction<boolean>>;
}

export interface StartBtnPropsType {
    gameMainSocket: Socket;
    mapCounter: number;
    ladderCheck: number;
}

export interface GameQuePropsType {
    gameMainSocket: Socket;
    setIsClose: React.Dispatch<React.SetStateAction<boolean>>,
}