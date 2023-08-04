import { useEffect, useRef, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { GameQuePropsType } from './GameInterface';
import styled from 'styled-components'
import SvgButton from '../other/SvgButton';
import StateModal from '../modal/StateModal';

const GameQueDiv = styled.div`
    position: absolute;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    background-color: rgba(255, 255, 255, 0.3);
    z-index: 11;
    display: flex;
    justify-content: center;
    align-items: center;
`;
const GameBaseDiv = styled.div`
    width: 200px;
    height: 130px;
    display: grid;
    grid-template-rows: 30px 100px;
    background-color: #343434;
    border-radius: 10px;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
`;
const GameBaseHeader = styled.header`
    text-align: right;
`;
const GameBaseMain = styled.main`
    text-align: center;
`;
const GameBaseP = styled.div`
    font-size: 2rem;
    color: #ffffff
`;
const GAMEQUE_INTERVAL = 1000;

interface stateType {
    stateImg: string;
    msg: string;
}

export default function GameQueTime({ gameMainSocket, setIsClose }: GameQuePropsType) {
    const nabi = useNavigate();
    let [counters, setCounters] = useState(0);
    const timeRef = useRef<NodeJS.Timer | null>();
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })

    const closeClick = () => {
        if (gameMainSocket) {
            gameMainSocket.emit("queueout", {}, (res: any) => {
                if (res.status) {
                    setModalOpen(true);
                    setStateData({ stateImg: "Error", msg: res.message });
                    const timeCheck = setTimeout(() => {
                        clearTimeout(timeCheck);
                        nabi('/main');
                    }, 1800);
                }
            });
            gameMainSocket.off("ready");
        }
        if (timeRef.current) {
            clearInterval(timeRef.current);
            timeRef.current = null;
        }
        setIsClose(false);
    }

    useEffect(() => {
        timeRef.current = setInterval(() => setCounters((prev) => prev + 1), GAMEQUE_INTERVAL);
        return () => {
            if (timeRef.current) {
                clearInterval(timeRef.current)
                timeRef.current = null;
            }
        }
    }, [])

    return (
        <GameQueDiv>
            <GameBaseDiv>
                <GameBaseHeader>
                    <SvgButton svgName='XmarkSvg' ladders="que" onClick={closeClick}></SvgButton>
                </GameBaseHeader>
                <GameBaseMain>
                    <SvgButton svgName='LoadingSvg'></SvgButton>
                    <GameBaseP>{(Math.floor((counters / 60)).toString()).padStart(2, "0")}:{((counters % 60).toString()).padStart(2, "0")}</GameBaseP>
                </GameBaseMain>
            </GameBaseDiv>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </GameQueDiv>
    );
}