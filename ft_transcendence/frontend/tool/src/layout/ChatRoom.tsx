import { useNavigate } from 'react-router-dom';
import { useState, useEffect, useCallback } from 'react';
import {io, Socket } from "socket.io-client";
import { useLocation } from "react-router-dom";
import * as PublicStyled from '../style/PublicStyle'
import SvgButton from '../component/other/SvgButton';
import ChatBox from '../component/chat/ChatBox'
import ChatProfile from '../component/chat/ChatProfile';
import ChatInput from '../component/chat/ChatInput';
import ChatInvite from '../component/chat/ChatInvite';
import PublicModal from '../component/modal/PublicModal';
import StateModal from '../component/modal/StateModal';
import {SocketContext, RoomInfoChat, roomInfoChatInterface,
        ChatRoomEvent, EventInfo, ModalController, ModalControllerContext,
        SocketValidate, StateModalControllerContext, StateModalController
        } from '../lib/socketContext';
import { tokenCheck } from '../component/other/tokenCheck';

const accessCheck = (info:roomInfoChatInterface) => {
    if (!info)
        window.location.href = process.env.REACT_APP_HOME || "";
}

interface stateType {
    stateImg: string;
    msg: string;
  }

export default function ChatRoom() {
    tokenCheck();
    const location = useLocation();
    const [isWhisper, setWhisper] = useState<boolean>(false);
    const [whisperTarget, setWhisperTarget] = useState<string>("");
    const [socketVal, setSocketVal] = useState<boolean>(false);
    const navigator = useNavigate();
	const infoBefroeParse = location.state;
    const info = JSON.parse(infoBefroeParse);
    accessCheck(info);
    const roomInfo: roomInfoChatInterface = {
        id: info.id,
        name: info.name,
        password: info.password,
        type: info.type,
    }
    const [event, setEvent] = useState<string>("");
    const [target, setTarget] = useState<string>("");
    const chatRoomEvent: ChatRoomEvent = {
        event: event,
        setEvent: setEvent,
        target: target,
        setTarget: setTarget,
    }

    const [stateModal, setStateModal] = useState<boolean>(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    });
    const stateModalController: StateModalController = {
        isOpen: stateModal,
        setOpen: setStateModal,
        stateType: stateData,
        setStateType: setStateData,
    }

    const [isModal, setModal] = useState<boolean>(false);
    const [modalNum, setModalNum] = useState<number>(0);
    const modalController: ModalController = {
        isOpen: isModal,
        setOpen: setModal,
        modalNum: modalNum,
        setModalNum: setModalNum
    }

    const [chatSocket, setChatSocket] = useState<Socket | null>(null);

    const socketConnect = useCallback(()=>{
        if (roomInfo.id)
        {
            const token = sessionStorage.getItem('rtoken');
            const socketOption = {
                path: '/chat',
                closeOnBeforeunload: true,
                extraHeaders: {
                    Authorization: `Bearer ${token}`,
                },
                query: {
                    id: roomInfo.id,
                    name: roomInfo.name,
                    password: roomInfo.password,
                    type: roomInfo.type,
                }
            }
            const socket = io((process.env.REACT_APP_API_URL || ""), socketOption);
            setChatSocket(socket);
        }
    }, [roomInfo.id, roomInfo.name, roomInfo.password, roomInfo.type])

    useEffect(() => {
        if (!chatSocket)
            socketConnect();
        return () => {
            if (chatSocket) {
                chatSocket.off();
                chatSocket.disconnect();
            }
        }
    }, [chatSocket, socketConnect])

    useEffect(() => {
        if (chatSocket)
        {
            chatSocket.off("connectionCompleted");
            chatSocket.off("disconnect");
            chatSocket.off("error");
            chatSocket.off("goHome");
            chatSocket.on("connectionCompleted", () => {
                setSocketVal(true);
            })
            chatSocket.on("disconnect", () => {
                navigator("/chat");
            })
            chatSocket.on("error", () => {
                navigator("/chat");   
            })
            chatSocket.on("goHome", () => {
                chatSocket?.off();
                navigator("/");
            })
        }
    }, [chatSocket, navigator])

    const onClick = () => {
        chatSocket?.disconnect();
    }

    return (
        <SocketContext.Provider value={chatSocket}>
        <RoomInfoChat.Provider value={roomInfo}>
        <EventInfo.Provider value={chatRoomEvent}>
        <ModalControllerContext.Provider value={modalController}>
        <SocketValidate.Provider value={socketVal}>
        <StateModalControllerContext.Provider value={stateModalController}>
            <PublicStyled.PublicContainer>
                <PublicStyled.PublicCenter>
                    <PublicStyled.PublicHeader>
                        <SvgButton svgName='ReturnSvg' onClick={onClick}></SvgButton>
                    </PublicStyled.PublicHeader>
                    <PublicStyled.PublicMiddle isLayout='ChatRoom'>
                        <ChatBox/>
                        <ChatProfile isWhisper={isWhisper} setWhisper={setWhisper} setWhisperTarget={setWhisperTarget} isModal={isModal} setModal={setModal}/>
                        <ChatInvite/>
                        <ChatInput isWhisper={isWhisper} whisperTarget={whisperTarget}/>
                    </PublicStyled.PublicMiddle>
                </PublicStyled.PublicCenter>
                {isModal && <PublicModal isModal={isModal} isModalNum={modalNum} setIsModal={setModal} />}
                {stateModal && <StateModal modalOpen={stateModal} setModalOpen={setStateModal} stateImg={stateData.stateImg} msg={stateData.msg} />}
            </PublicStyled.PublicContainer>
        </StateModalControllerContext.Provider>
        </SocketValidate.Provider>
        </ModalControllerContext.Provider>
        </EventInfo.Provider>
        </RoomInfoChat.Provider>
        </SocketContext.Provider>
    )
}