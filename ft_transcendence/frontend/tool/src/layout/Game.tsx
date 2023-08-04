import * as PublicStyled from '../style/PublicStyle'
import { useEffect, useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { pfGetApi } from '../lib/getAxios';
import { io, Socket } from 'socket.io-client';
import { GameLadderType } from '../component/game/GameInterface';
import SvgButton from '../component/other/SvgButton';
import NabigationBar from '../component/other/NabigationBar';
import GameMapList from '../component/game/GameMapList';
import GamMapBig from '../component/game/GameMapBig';
import GameStartButton from '../component/game/GameStartButton';
import GameWatch from '../component/game/GameWatch';
import LadderScore from '../component/profile/LadderScore';
import StateModal from '../component/modal/StateModal';
import { tokenCheck } from '../component/other/tokenCheck';

interface stateType {
    stateImg: string;
    msg: string;
}

export default function Game() {
    tokenCheck();
    const nabi = useNavigate();
    const [nabiNum, setNabiNum] = useState(0);
    const [mapCounter, setMapCounter] = useState(0);
    const [ladderInfo, setLadderInfo] = useState<GameLadderType>();
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })
    const [gameMainSocket, setGameMainScoket] = useState<Socket | null>(null);


    const getLadderInfo = async () => {
        try {
            const res = await pfGetApi.getLeftInput();
            setLadderInfo(res.data);
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    useEffect(() => {
        const token = sessionStorage.getItem('rtoken');
        const socketOption = {
            path: "/game",
            closeOnBeforeunload: true,
            extraHeaders: {
                Authorization: `Bearer ${token}`,
            }
        }

        const gameSockets = io(process.env.REACT_APP_API_URL as string, socketOption);
        if (gameSockets) {
            gameSockets.on("disconnect", () => {
                gameSockets.off();
                nabi('/main');
            })
            gameSockets.on("goHome", () => {
                gameSockets?.off();
                nabi("/");
            })
        }
        setGameMainScoket(gameSockets);
        return () => {
            gameSockets.off();
            gameSockets.disconnect();
            setGameMainScoket(null);
        }
    }, [nabi])

    useEffect(() => {
        setMapCounter(0);
        if (nabiNum !== 2 && gameMainSocket) {
            gameMainSocket.off("gameroomlist");
        }

        if (nabiNum === 1) {
            getLadderInfo();
        }
    }, [nabiNum, gameMainSocket])

    return (
        <PublicStyled.PublicContainer>
            <PublicStyled.PublicCenter>
                <PublicStyled.PublicHeader>
                    <Link to="/main">
                        <SvgButton svgName='ReturnSvg'></SvgButton>
                    </Link>
                </PublicStyled.PublicHeader>
                <PublicStyled.PublicMiddle isLayout='Game'>
                    <NabigationBar isListHeader='일반전,경쟁전,관전' setBeforeNabiNum={null} setNabiNum={setNabiNum}></NabigationBar>
                    {nabiNum === 0 ? <GameMapList setMapCounter={setMapCounter}></GameMapList> : null}
                    {nabiNum === 1 ? <LadderScore isgames="ok" ladders={ladderInfo?.ladderrating || "Bronze"} scores={ladderInfo?.ladderscore.toString() || "0"}></LadderScore> : null}
                    {nabiNum === 2 && gameMainSocket ? <GameWatch gameMainSocket={gameMainSocket} nabiNum={nabiNum}></GameWatch> : null}
                    {nabiNum !== 2 ? <GamMapBig nabiNum={nabiNum} mapCounter={mapCounter}></GamMapBig> : null}
                    {nabiNum !== 2 && gameMainSocket ? <GameStartButton gameMainSocket={gameMainSocket} mapCounter={mapCounter} ladderCheck={nabiNum}></GameStartButton> : null}
                </PublicStyled.PublicMiddle>
            </PublicStyled.PublicCenter>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </PublicStyled.PublicContainer>
    )
}