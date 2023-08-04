import React, { useState, useContext, useEffect } from 'react';
import styled, { css } from 'styled-components';
import SvgButton from '../other/SvgButton';
import PublicModal from '../modal/PublicModal';
import {RoomInfo, SocketContext, SocketValidate} from '../../lib/socketContext';

const LobbyContainer = styled.div`
    width: 800px;
    height: 642px; 
    grid-row: 2 / 3;
    cursor: default;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
`;

const LobbyHead = styled.div`
    display: grid;
    grid-template-columns: 72px 102px 400px 113px 113px;
    width: 100%;
`;

const LobbyBody = styled.div`
    overflow-y: scroll;
    scroll-behavior: smooth;
    max-height: 642px;
    width: 100%;
    -ms-overflow-style: none;
    scrollbar-width: none;
    &::-webkit-scrollbar{
        display: none;
    }
`;

const LobbyBodys = styled.div`
    display: grid;
    grid-template-columns: 72px 102px 400px 113px 113px;
    border: solid black;
    border-width: 1px 1px 0px 0px;
`;

const LobbyElements = styled.div<{ isHeader?: string, isList: number }>`
    justify-content: center;
    text-align: center;
    padding: 10px;
    color: ${(props) => (props.isHeader === 'header' ? '#6200EA' : '#909099')};
    background-color: ${(props) => (props.isHeader === 'header' ? '#B388FF' : '#455A64')};
    ${(props) => props.isList === 1 ? css`
    grid-column: 1 / 2;
    ` : (props.isList === 2 ? css`
    grid-column: 2 / 3;
    ` : (props.isList === 3 ? css`
    grid-column: 3 / 4;
    ` : (props.isList === 4 ? css`
    grid-column: 4 / 6;
    ` : (props.isHeader === 'header' && props.isList === 5 ? css`
    grid-column: 4 / 6;
    ` : (props.isList === 5 ? css`
    grid-column: 5 / 6;
    ` : css`
    grid-column: 6 / 7;
    `)))))}
`;

const ChatButton = styled.button.attrs((props) => ({
    type: 'button',
    disabled: props.disabled
})) <{ isHeader?: string }>`
    border: 0;
    border-radius: 25px;
    width: 80px;
    height: 20px;
    background-color: ${(props) => (props.isHeader === 'header' ? '#343434' : '#B388FF')};
    color: ${(props) => (props.isHeader === 'header' ? '#aa00ff' : '#000000')}; ;
    &:active {
        background-color: ${(props) => (props.isHeader === 'header' ? '#aa00ff' : '#343434')};
        color: ${(props) => (props.isHeader === 'header' ? '#000000' : '#aa00ff')};
    }
`;

interface tableBody {
    id: number,
    type: string,
    name: string,
    isIn: boolean,
}

export default function ChatChannel() {
    const [isType, setType] = useState<string | undefined>("");
    const [isModal, setModal] = useState<boolean>(false);
    const [isModalNum, setModalNum] = useState<number>(0);
    const roomInfo = useContext(RoomInfo);
    const chatSocket = useContext(SocketContext);
    const channelRoomIN = (e: React.MouseEvent<HTMLButtonElement>) => {
        setModalNum(2);
        roomInfo?.setID((e.target as HTMLTableElement).id);
        roomInfo?.setName((e.target as HTMLTableElement).dataset.name);
        roomInfo?.setType((e.target as HTMLTableElement).dataset.type);
        roomInfo?.setIsIn((e.target as HTMLTableElement).dataset.isin);
        setType((e.target as HTMLTableElement).dataset.type);
        setModal(!isModal);
    }
    const channelRoomOut = (e: React.MouseEvent<HTMLButtonElement>) => {
        setModalNum(9);
        roomInfo?.setID((e.target as HTMLTableElement).id);
        roomInfo?.setName((e.target as HTMLTableElement).dataset.name);
        roomInfo?.setType((e.target as HTMLTableElement).dataset.type);
        roomInfo?.setIsIn((e.target as HTMLTableElement).dataset.isin);
        setType((e.target as HTMLTableElement).dataset.type);
        setModal(!isModal);
    }
    const channelCreate = (e: React.MouseEvent<HTMLButtonElement>) => {
        setModalNum(3);
        setModal(!isModal);
    }
    const [chatBodyAll, setChatBodyAll] = useState<tableBody[]>([]);
    const socketVal = useContext(SocketValidate);
    
    useEffect(() => {
        if(socketVal && chatSocket)
            chatSocket?.emit("channelList", (resp: any ) => {
                    setChatBodyAll(resp);
            });
    }, [socketVal, chatSocket])

    useEffect(() => {
        if (chatSocket)
        {
            chatSocket.on("channelUpdated", () => {
                chatSocket?.emit("channelList", (resp: any ) => {
                    setChatBodyAll(resp);
                });
            });
        }
    }, [chatSocket])

    return (
        <LobbyContainer>
            <LobbyHead>
                <LobbyElements isList={1} isHeader="header">타 입 </LobbyElements>
                <LobbyElements isList={2} isHeader="header">채 널 번 호 </LobbyElements>
                <LobbyElements isList={3} isHeader="header">채 널 명</LobbyElements>
                <LobbyElements isList={5} isHeader="header">
                    <ChatButton disabled={false} isHeader='header' onClick={channelCreate}>방생성+</ChatButton>
                </LobbyElements>
            </LobbyHead>
            <LobbyBody>
                {chatBodyAll.map((item, index) => (
                    <LobbyBodys key={index}>
                        <LobbyElements isList={1}>
                            {item.type === 'public' && <SvgButton svgName='PublicSvg' />}
                            {item.type === 'protected' && <SvgButton svgName='ProtectSvg' />}
                            {item.type === 'private' && <SvgButton svgName='QueSvg' />}
                        </LobbyElements>
                        <LobbyElements isList={2}>{item.id}</LobbyElements>
                        <LobbyElements isList={3}>{item.name}</LobbyElements>
                        <LobbyElements isList={4}>
                            <ChatButton id={item.id + ""} data-isin={item.isIn + ""} data-type={item.type} data-name={item.name} onClick={channelRoomIN}>참가</ChatButton>
                            {
                                item.isIn ? 
                                    <ChatButton id={item.id + ""} data-isin={item.isIn + ""} data-type={item.type} data-name={item.name} onClick={channelRoomOut}>나가기</ChatButton>
                                    : null
                            }
                        </LobbyElements>
                    </LobbyBodys>
                ))}
            </LobbyBody>
            {isModal && <PublicModal isType={isType} isModal={isModal} isModalNum={isModalNum} setIsModal={setModal} />}
        </LobbyContainer>
    );
}