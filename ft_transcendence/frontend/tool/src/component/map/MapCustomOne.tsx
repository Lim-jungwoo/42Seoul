import style from './MapCustomOne.module.css';
import { useEffect, useState, useRef, useCallback } from 'react';
import { useParams, useSearchParams, useNavigate } from 'react-router-dom';
import StateModal from '../modal/StateModal';
import { MapInfoType, DisplayType, BallType, TrayType, ScoreType, GameOutType, WatchOnePropsType, WatchTwoPropsType } from './MapInterfaces';


const BallOneDiv = (ballOneData: BallType) => {
    return (
        <div className={style.mapBallOne} style={{ top: `${ballOneData.positionY}px`, left: `${ballOneData.positionX}px`, width: `${ballOneData.radius * 2}px`, height: `${ballOneData.radius * 2}px` }}></div>
    )
}

const BallTwoDiv = (ballTwoData: BallType) => {
    return (
        <div className={style.mapBallTwo} style={{ top: `${ballTwoData.positionY}px`, left: `${ballTwoData.positionX}px`, width: `${ballTwoData.radius * 2}px`, height: `${ballTwoData.radius * 2}px` }}></div>
    )
}

const CrowdDiv = ({ spectators }: { spectators: number }) => {
    return (
        <div className={style.mapBallTwoCrowd}>watch {spectators}</div>
    )
}

const LeaveBtn = () => {
    const nabi = useNavigate();
    const leaveMap = () => {
        nabi('/game');
    }

    return (
        <button className={style.mapBallTwoLeave} onClick={leaveMap}>관전 떠나기</button>
    )
}

const PlayOneScore = ({ playerNickName, score }: WatchOnePropsType) => {
    return (
        <div>{playerNickName} {score}</div>
    )
}

const PlayTwoScore = ({ playerNickName, score, spectators, userType }: WatchTwoPropsType) => {
    return (
        <div>{score} {playerNickName}
            {userType === process.env.REACT_APP_USER_TYPE as string ? <CrowdDiv spectators={spectators}></CrowdDiv>
                : (userType === process.env.REACT_APP_USER_SELECT as string ? <LeaveBtn /> : null)}
        </div>
    )
}

const PlayOneDiv = (trayOneData: TrayType) => {
    return (
        <div className={style.mapBallTwoTrayPlayOne}
            style={{
                width: `${trayOneData.width}px`,
                height: `${trayOneData.height}px`,
                left: `${trayOneData.positionX}px`,
                top: `${trayOneData.positionY}px`
            }}></div>
    )
}

const PlayTwoDiv = (trayTwoData: TrayType) => {
    return (
        <div className={style.mapBallTwoTrayPlayTwo}
            style={{
                width: `${trayTwoData.width}px`,
                height: `${trayTwoData.height}px`,
                left: `${trayTwoData.positionX}px`,
                top: `${trayTwoData.positionY}px`
            }}></div>
    )
}

interface stateType {
    stateImg: string;
    msg: string;
}


export default function MapCustomOne({ mapInfo }: { mapInfo: MapInfoType }) {
    const nabi = useNavigate();
    const params = useParams();
    const roomnumber = params.roomnums || "";
    const [searchUserType] = useSearchParams();
    const userType = searchUserType.get("usertype") || "";
    const timeRef = useRef<NodeJS.Timer | null>();
    const outRef = useRef<NodeJS.Timeout | null>();
    const [counters, setCounters] = useState(5);
    const [loding, setLoding] = useState(true);
    const [results, setResults] = useState(false);
    const [ballOneData, setBallOneData] = useState<BallType>(mapInfo.ballOne);
    const [ballTwoData, setBallTwoData] = useState<BallType>(mapInfo.ballTwo);
    const [disPlaysData] = useState<DisplayType>(mapInfo.displays);
    const [scoreData, setScoreData] = useState<ScoreType>(mapInfo.scores);
    const [spectators, setSpectators] = useState<number>(0);
    const [trayOneData, setTrayOneDate] = useState<TrayType>(mapInfo.traysOne)
    const [trayTwoData, setTrayTwoDate] = useState<TrayType>(mapInfo.traysTwo)
    const [gameOutData, setGameOutData] = useState<GameOutType>({
        scoreresult: "",
        winner: "",
    });
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })

    const inputSocket = useCallback((leftPress: boolean, rightPress: boolean) => {
        if (mapInfo.socket) {
            mapInfo.socket.emit("input", {
                roomnumber: roomnumber,
                up: leftPress,
                down: rightPress,
            }, (res: any) => {
                if (res.status) {
                    setModalOpen(true);
                    setStateData({ stateImg: "Error", msg: res.message });
                    const timeCheck = setTimeout(() => {
                        clearTimeout(timeCheck);
                        nabi('/game');
                    }, 1800);
                }
            });
        }
    }, [nabi, mapInfo.socket, roomnumber]);

    const keyDownPress = useCallback((e: KeyboardEvent) => {
        if (e.key === 'Up' || e.key === 'ArrowUp') {
            inputSocket(false, true);
        }
        else if (e.key === 'Down' || e.key === 'ArrowDown') {
            inputSocket(true, false);
        }
    }, [inputSocket]);

    const keyUpPress = useCallback((e: KeyboardEvent) => {
        if (e.key === 'Up' || e.key === 'ArrowUp') {
            inputSocket(false, false);
        }
        else if (e.key === 'Down' || e.key === 'ArrowDown') {
            inputSocket(false, false);
        }
    }, [inputSocket]);

    const gameOutNabi = useCallback(() => {
        nabi('/game');
    }, [nabi]);

    const render = useCallback(() => {
        if (userType === process.env.REACT_APP_USER_TYPE || "") {
            document.addEventListener("keydown", keyDownPress, false);
            document.addEventListener("keyup", keyUpPress, false);
        }

        if (timeRef.current) {
            clearInterval(timeRef.current);
            timeRef.current = null;
        }

        if (outRef.current) {
            clearTimeout(outRef.current)
            outRef.current = null;
        }

        setLoding(false);

        if (mapInfo.socket) {
            if (userType === process.env.REACT_APP_USER_TYPE as string) {
                mapInfo.socket.emit('gamestart', { roomnumber: roomnumber }, (res: any) => {
                    if (res.status) {
                        setModalOpen(true);
                        setStateData({ stateImg: "Error", msg: res.message });
                        const timeCheck = setTimeout(() => {
                            clearTimeout(timeCheck);
                            nabi('/game');
                        }, 1800);
                    }
                });

                mapInfo.socket.off('spectators').on('spectators', (spectatorsNumber) => {
                    setSpectators(spectatorsNumber);
                })
            }

            mapInfo.socket.on("ball", (data) => {
                setBallOneData({
                    radius: data[0].radius,
                    positionX: data[0].positionX,
                    positionY: data[0].positionY,
                });
                setBallTwoData({
                    radius: data[1].radius,
                    positionX: data[1].positionX,
                    positionY: data[1].positionY,
                });
            });

            mapInfo.socket.on("score", (data) => {
                if (!(data.score1 > 10 || data.score2 > 10)) {
                    setScoreData({
                        player1: data.player1,
                        player2: data.player2,
                        score1: data.score1,
                        score2: data.score2,
                    });
                }
            });

            mapInfo.socket.on("playing", (tray1, tray2) => {
                setTrayOneDate({
                    height: tray1.height,
                    positionX: tray1.positionX,
                    positionY: tray1.positionY,
                    width: tray1.width,
                })
                setTrayTwoDate({
                    height: tray2.height,
                    positionX: tray2.positionX,
                    positionY: tray2.positionY,
                    width: tray2.width,
                })
            });

            mapInfo.socket.on("history", (sendHistory) => {
                document.removeEventListener("keydown", keyDownPress);
                document.removeEventListener("keyup", keyUpPress);
                setGameOutData({
                    scoreresult: sendHistory.scoreresult,
                    winner: sendHistory.winner,
                })
                setResults(true);
                timeRef.current = setTimeout(gameOutNabi, 4000);
            })
        }
    }, [gameOutNabi, keyDownPress, keyUpPress, mapInfo.socket, nabi, roomnumber, userType]);

    useEffect(() => {
        if (userType === process.env.REACT_APP_USER_TYPE || "") {
            if (mapInfo.socket) {
                mapInfo.socket.on('spectators', (spectatorsNumber) => {
                    setSpectators(spectatorsNumber);
                })

                mapInfo.socket.once("history", (sendHistory) => {
                    document.removeEventListener("keydown", keyDownPress);
                    document.removeEventListener("keyup", keyUpPress);
                    setGameOutData({
                        scoreresult: sendHistory.scoreresult,
                        winner: sendHistory.winner,
                    })
                    setResults(true);
                    if (outRef.current && timeRef.current) {
                        setLoding(false);
                        clearInterval(timeRef.current);
                        timeRef.current = null;
                        clearTimeout(outRef.current);
                        outRef.current = null;
                        outRef.current = setTimeout(gameOutNabi, 4000);
                    }
                })

            }

            timeRef.current = setInterval(() => setCounters((prev) => prev - 1), 1000);
            outRef.current = setTimeout(render, 5000);
        } else if (userType === process.env.REACT_APP_USER_SELECT || "") {
            render();
        }
        return () => {
            document.removeEventListener("keydown", keyDownPress);
            document.removeEventListener("keyup", keyUpPress);
            if (outRef.current) {
                clearTimeout(outRef.current);
                outRef.current = null;
            }
            if (timeRef.current) {
                clearInterval(timeRef.current);
                timeRef.current = null;
            }
        }
    }, [gameOutNabi, keyDownPress, keyUpPress, mapInfo.socket, render, userType])

    return (
        <>
            <div className={style.mapBallTwoBase}>
                <div className={style.mapBallTwoCenter} style={{ width: `${disPlaysData.width}px`, height: `${disPlaysData.height}px` }}>
                    <div className={style.mapBallTwoScore}>
                        <PlayOneScore playerNickName={scoreData.player1} score={scoreData.score1}></PlayOneScore>
                        <PlayTwoScore playerNickName={scoreData.player2} score={scoreData.score2} spectators={spectators} userType={userType}></PlayTwoScore>
                    </div>
                    <BallOneDiv {...ballOneData} />
                    <BallTwoDiv {...ballTwoData} />
                    <PlayOneDiv {...trayOneData} />
                    <PlayTwoDiv {...trayTwoData} />
                </div>
            </div>
            {loding ?
                <div className={style.mapBallTwoLodings}>
                    <div className={style.mapBallTwoLodingsDiv}>Ready {counters}</div>
                </div> : null}
            {results ?
                <div className={style.mapBallTwoLodings}>
                    <div className={`${style.mapBallTwoLodingsDiv} ${style.mapBallTwoWinDiv}`}>Winner</div>
                    <div className={style.mapBallTwoLodingsDiv}>{gameOutData.winner}</div>
                    <div className={style.mapBallTwoLodingsDiv}>{gameOutData.scoreresult}</div>
                </div> : null}
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </>
    )
}