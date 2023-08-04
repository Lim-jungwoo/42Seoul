import { Socket } from "socket.io-client";
import { createContext } from 'react';

export interface roomInterface {
    type?: string,
    setType: React.Dispatch<React.SetStateAction<string | undefined>>,
    id: string,
    setID: React.Dispatch<React.SetStateAction<string>>,
    password: string,
    setPassword: React.Dispatch<React.SetStateAction<string>>,
    name?: string,
    setName: React.Dispatch<React.SetStateAction<string | undefined>>,
    isIn?: string,
    setIsIn: React.Dispatch<React.SetStateAction<string | undefined>>,
}

export interface roomInfoChatInterface{
    id: string,
    name: string,
    password: string,
    type: string,
}

export interface ChatRoomEvent{
    event: string,
    setEvent: React.Dispatch<React.SetStateAction<string>>,
    target: string
    setTarget: React.Dispatch<React.SetStateAction<string>>,
}

export interface ModalController{
    isOpen: boolean,
    setOpen: React.Dispatch<React.SetStateAction<boolean>>,
    modalNum: number,
    setModalNum: React.Dispatch<React.SetStateAction<number>>
}

interface stateType {
    stateImg: string;
    msg: string;
}

export interface StateModalController {
    isOpen: boolean,
    setOpen: React.Dispatch<React.SetStateAction<boolean>>,
    stateType: stateType,
    setStateType: React.Dispatch<React.SetStateAction<stateType>>, 
}

export const SocketContext = createContext<Socket | null>(null);
export const SocketValidate = createContext<boolean>(false);
export const RoomInfo = createContext<roomInterface | null>(null);
export const RoomInfoChat = createContext<roomInfoChatInterface | null>(null);
export const EventInfo = createContext<ChatRoomEvent | null>(null);
export const ModalControllerContext = createContext<ModalController | null>(null);
export const StateModalControllerContext = createContext<StateModalController | null>(null);
