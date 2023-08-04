import * as PublicStyled from '../style/PublicStyle'
import SvgButton from '../component/other/SvgButton';
import { Link, useNavigate } from 'react-router-dom';
import { useState, useEffect } from 'react';
import ChatChannel from '../component/chat/ChatChannel';
import ChatChannelInvite from '../component/chat/ChatChannelInvite';
import NabigationBar from '../component/other/NabigationBar';
import { io, Socket } from "socket.io-client";
import {SocketContext, RoomInfo, SocketValidate} from '../lib/socketContext';
import { tokenCheck } from '../component/other/tokenCheck';

export default function Chat() {
    tokenCheck();
    const [nabiNum, setNabiNum] = useState(0);
    const navigator = useNavigate();
    const [id, setID] = useState("");
    const [password, setPassword] = useState("");
    const [roomName, setRoomName] = useState<string | undefined>("");
    const [type, setType] = useState<string | undefined>("");
    const [isIn, setIsIn] = useState<string | undefined>("");

    const [chatSocket, setChatSocket] = useState<Socket | null>(null);
    const [connect, setConnect] = useState<boolean>(false);


    useEffect(() => {
        const token = sessionStorage.getItem('rtoken');
        const socketOption = {
            // 연결 주소
            path: '/chat',
            //beforeunload브라우저에서 이벤트가 발생할 때 연결을 (자동으로) 닫을지 여부 입니다
            closeOnBeforeunload: true,
            //추가 해더
            extraHeaders: {
                Authorization: `Bearer ${token}`,
            },
        }
        const socket = io((process.env.REACT_APP_API_URL || ""), socketOption);
        setChatSocket(socket);
        return () => {
            if (socket) {
                socket.off();
                socket.disconnect();
            }
        }
    }, [])

    useEffect(() => {
        if (chatSocket !== null)
        {
            chatSocket.off("connectionCompleted");
            chatSocket.off("disconnect");
            chatSocket.off("goHome");
            chatSocket.on("connectionCompleted", () => {
                setConnect(true);
            })
            chatSocket.on("disconnect", () => {
                navigator("/main");
            })
            chatSocket.on("goHome", () => {
                chatSocket?.off();
                navigator("/");
            })
        }
    }, [chatSocket, navigator])

    const disconnectClick = () => {
        chatSocket?.disconnect();
    }

    return (
        <SocketContext.Provider value={chatSocket}>
        <SocketValidate.Provider value={connect}>
        <RoomInfo.Provider value={{
                type: type,
                setType: setType,
                id: id,
                setID: setID,
                password: password,
                setPassword: setPassword,
                name: roomName,
                setName: setRoomName,
                isIn: isIn,
                setIsIn: setIsIn,
            }}>
            <PublicStyled.PublicContainer>
                <PublicStyled.PublicCenter>
                    <PublicStyled.PublicHeader>
                        <Link to="/main">
                            <SvgButton onClick={disconnectClick} svgName='ReturnSvg'/>
                        </Link>
                    </PublicStyled.PublicHeader>
                    <PublicStyled.PublicMiddle isLayout='Chat'>
                        <NabigationBar
                            isListHeader='전체,초대'
                            setBeforeNabiNum={null}
                            setNabiNum={setNabiNum} />
                        {
                            nabiNum === 0 ?
                            <ChatChannel/>
                            : <ChatChannelInvite/>
                        }
                    </PublicStyled.PublicMiddle>
                </PublicStyled.PublicCenter>
            </PublicStyled.PublicContainer>
        </RoomInfo.Provider>
        </SocketValidate.Provider>
        </SocketContext.Provider>
    )
}