import React, { useEffect, useState, useCallback } from 'react';
import styled, { css } from 'styled-components';
import GameModal from './GameModal';
import { GameWatchList, WatchPropsType } from './GameInterface';
import StateModal from '../modal/StateModal';

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
    grid-template-columns: 70px 200px 150px 280px 100px;
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
    grid-template-columns: 70px 200px 150px 280px 100px;
    border: solid black;
    border-width: 1px 1px 0px 0px;
`;

const LobbyElements = styled.div<{ isHeader?: string, isList: number }>`
    justify-content: center;
    text-align: center;
    ${(props) => props.isHeader === 'body' ? css`font-size: 1.1rem;` : css`font-size: 1rem;`}
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
    ` : (props.isList === 5 ? css`
    grid-column: 5 / 6;
    ` : (props.isList === 6 ? css`` : css` display: none`)))))}
`;

const WatchButton = styled.button.attrs(() => ({
    type: 'button',
}))`
    border: 0;
    border-radius: 25px;
    width: 80px;
    height: 20px;
    background-color: #B388FF;
    color: #000000;
    &:active {
        background-color: #343434;
        color: #aa00ff;
    }
`;

interface stateType {
    stateImg: string;
    msg: string;
}


export default function GameWatch({ gameMainSocket, nabiNum }: WatchPropsType) {
    let [isWatchBody, setISWatchBody] = useState<GameWatchList[]>([]);
    let [openGameModal, setOpenGameModal] = useState(false);
    let [roomData, setRoomDate] = useState("");
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })

    const watchModalOpen = (e: React.MouseEvent) => {
        setOpenGameModal(true);
        setRoomDate(`${(e.target as HTMLElement).parentElement?.parentElement?.children[1].textContent},${(e.target as HTMLElement).parentElement?.parentElement?.children[2].textContent}`)
    }

    const watchList = useCallback(() => {
        if (nabiNum === 2 && gameMainSocket) {
            try {
                gameMainSocket.emit("getgameroomlist");
                gameMainSocket.on("gameroomlist", (gameRoom) => {
                    setISWatchBody(gameRoom);
                })
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message });
            }
        }
    }, [gameMainSocket, nabiNum])

    useEffect(() => {
        watchList();
    }, [watchList])

    return (
        <LobbyContainer>
            <LobbyHead>
                <LobbyElements isList={1} isHeader="header">타 입</LobbyElements>
                <LobbyElements isList={2} isHeader="header">방 넘 버</LobbyElements>
                <LobbyElements isList={3} isHeader="header">맵 타 입</LobbyElements>
                <LobbyElements isList={4} isHeader="header">플 레 이 어</LobbyElements>
            </LobbyHead>
            <LobbyBody>
                {isWatchBody.map((item) => (
                    <LobbyBodys key={item.roomNumber}>
                        <LobbyElements isList={1}>{item.gameType === 'ladder' ? '레 더' : '일 반'} </LobbyElements>
                        <LobbyElements isList={2}>{item.roomNumber}</LobbyElements>
                        <LobbyElements isList={7}>{item.mapType}</LobbyElements>
                        <LobbyElements isList={3}>{item.mapType === 'map_0' ? "일 반" : (item.mapType === 'map_1' ? '공 갯 수 증 가' : '블 럭 생 성성')}</LobbyElements>
                        <LobbyElements isList={6} isHeader="body" >{item.player1NickName} VS {item.player2NickName}</LobbyElements>
                        <LobbyElements isList={6}>
                            <WatchButton onClick={watchModalOpen}>관 전</WatchButton>
                        </LobbyElements>
                    </LobbyBodys>
                ))}
            </LobbyBody>
            {openGameModal ? <GameModal gameMainSocket={gameMainSocket} roomData={roomData} setOpenGameModal={setOpenGameModal}></GameModal> : null}
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </LobbyContainer>
    );
}