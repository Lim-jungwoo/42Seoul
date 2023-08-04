import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { StartBtnPropsType } from './GameInterface';
import StateModal from '../modal/StateModal';
import styled from 'styled-components';
import GameQueTime from './GameQueTime';

const GameButtondiv = styled.div`
    text-align: center;
`;

const GameButton = styled.button`
    width: 200px;
    height: 48px;
    margin: 5px;
    border-radius: 25px;
    border: 0px;
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

export default function GameStartButton({ gameMainSocket, mapCounter, ladderCheck }: StartBtnPropsType) {
    const nabi = useNavigate();
    const [isClose, setIsClose] = useState(false);
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })


    const changeMap = (mapCounter: number) => {
        if (mapCounter === 0) return process.env.REACT_APP_MAP_DEFAULT as string;
        else if (mapCounter === 1) return process.env.REACT_APP_MAP_DOUBLE as string;
        else if (mapCounter === 2) return process.env.REACT_APP_MAP_BLOCK as string;
        else return ""
    }

    const pingPongStart = () => {
        if (gameMainSocket) {
            let checkMap = changeMap(mapCounter);
            if (checkMap === "") {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: "map 정보가 맞지 않습니다." });
                return;
            }
            gameMainSocket.emit("queue", {
                gametype: (ladderCheck === 0 ? "normal" : "ladder"),
                maptype: (ladderCheck === 1 ? null : checkMap),
            }, (res: any) => {
                if (res.status) {
                    setIsClose(false);
                    setModalOpen(true);
                    setStateData({ stateImg: "Error", msg: res.message });
                    const timeCheck = setTimeout(() => {
                        clearTimeout(timeCheck);
                        nabi('/main');
                    }, 1500);
                    return;
                }
            })

            gameMainSocket.off("ready").on("ready", (data) => {
                setIsClose(false);
                nabi(`/game/gameroom/${data.roomnumber}?maptype=${data.maptype}&usertype=${process.env.REACT_APP_USER_TYPE}`);
                return;
            })
            setIsClose(!isClose);
        }
    }

    return (
        <GameButtondiv>
            <GameButton onClick={pingPongStart}>GAME START</GameButton>
            {isClose ? <GameQueTime gameMainSocket={gameMainSocket} setIsClose={setIsClose}></GameQueTime> : null}
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </GameButtondiv>
    );
}