import { useCallback, useEffect, useState } from 'react';
import { useParams, useSearchParams, useNavigate } from 'react-router-dom';
import { io } from 'socket.io-client';
import MapDeafult from '../component/map/MapDefault';
import MapCustomOne from '../component/map/MapCustomOne';
import MapCustomTwo from '../component/map/MapCustomTwo';
import { MapInfoType } from '../component/map/MapInterfaces';
import StateModal from '../component/modal/StateModal';
import { tokenCheck } from '../component/other/tokenCheck';

interface stateType {
  stateImg: string;
  msg: string;
}

export default function GameRoom() {
  tokenCheck();
  const nabi = useNavigate();
  const params = useParams();
  const [searchParams] = useSearchParams();
  const mapSelect = searchParams.get("maptype");
  const userSelect = searchParams.get("usertype");
  const [mapInfo, setMapInfo] = useState<MapInfoType | null>(null)
  const [modalOpen, setModalOpen] = useState(false);
  const [stateData, setStateData] = useState<stateType>({
    stateImg: "",
    msg: "",
  });

  const checkUrlQuery = useCallback(() => {
    if (!(process.env.REACT_APP_MAP_BLOCK === mapSelect ||
      process.env.REACT_APP_MAP_DEFAULT === mapSelect ||
      process.env.REACT_APP_MAP_DOUBLE === mapSelect)) {
      setModalOpen(true);
      setStateData({ stateImg: "Error", msg: "존재 하지 않는 맵입니다." });
      const timeCheck = setTimeout(() => {
        clearTimeout(timeCheck);
        nabi('/game');
      }, 1600);
      return false;
    }
    else if (!(process.env.REACT_APP_USER_SELECT === userSelect ||
      process.env.REACT_APP_USER_TYPE === userSelect)) {
      setModalOpen(true);
      setStateData({ stateImg: "Error", msg: "잘못된 유저 타입 입니다." });
      const timeCheck = setTimeout(() => {
        clearTimeout(timeCheck);
        nabi('/game');
      }, 1600);
      return false;
    }
    return true;
  }, [mapSelect, userSelect, nabi]);

  useEffect(() => {
    if (checkUrlQuery()) {
      const token = sessionStorage.getItem('rtoken');
      const socketOption = {
        path: "/gameplay",
        closeOnBeforeunload: true,
        extraHeaders: {
          Authorization: `Bearer ${token}`,
        }
      };
      const gameSocket = io((process.env.REACT_APP_API_URL || ""), socketOption);
      if (gameSocket) {
        gameSocket.on("disconnect", () => {
          gameSocket.off();
          nabi('/main');
        });
        gameSocket.on("goHome", () => {
          gameSocket?.off();
          nabi("/");
        });

        gameSocket.on("connect_complete", () => {
          if (userSelect === process.env.REACT_APP_USER_TYPE || "") {
            gameSocket.emit("roomnumber", { roomnumber: params.roomnums }, (res: any) => {
              if (res.status) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: res.message });
                const timeCheck = setTimeout(() => {
                  clearTimeout(timeCheck);
                  nabi('/game');
                }, 1600);
              }
            });

            gameSocket.on("roominfo", (gameMap, one, two) => {
              setMapInfo({
                socket: gameSocket,
                brick: (mapSelect === (process.env.REACT_APP_MAP_BLOCK || "") ? gameMap.brick : null),
                ballOne: { radius: gameMap.ball[0].radius, positionX: gameMap.ball[0].positionX, positionY: gameMap.ball[0].positionY },
                ballTwo: {
                  radius: (mapSelect === (process.env.REACT_APP_MAP_DOUBLE || "") ? gameMap.ball[1].radius : 0),
                  positionX: (mapSelect === (process.env.REACT_APP_MAP_DOUBLE || "") ? gameMap.ball[1].positionX : 0),
                  positionY: (mapSelect === (process.env.REACT_APP_MAP_DOUBLE || "") ? gameMap.ball[1].positionY : 0)
                },
                displays: { width: gameMap.display.width, height: gameMap.display.height },
                traysOne: { height: gameMap.tray1.height, positionX: gameMap.tray1.positionX, positionY: gameMap.tray1.positionY, width: gameMap.tray1.width },
                traysTwo: { height: gameMap.tray2.height, positionX: gameMap.tray2.positionX, positionY: gameMap.tray2.positionY, width: gameMap.tray2.width },
                scores: { player1: one, player2: two, score1: gameMap.score1, score2: gameMap.score2 },
              })
            });
          }
          if (userSelect === process.env.REACT_APP_USER_SELECT || "") {
            gameSocket.emit("watch", params.roomnums, (res: any) => {
              if (res.status) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: res.message });
                const timeCheck = setTimeout(() => {
                  clearTimeout(timeCheck);
                  nabi('/game');
                }, 1600);
              }
            });

            gameSocket.once("watch_display", (gameMap, one, two) => {
              setMapInfo({
                socket: gameSocket,
                brick: (mapSelect === (process.env.REACT_APP_MAP_BLOCK || "") ? gameMap.brick : null),
                ballOne: { radius: gameMap.ball[0].radius, positionX: gameMap.ball[0].positionX, positionY: gameMap.ball[0].positionY },
                ballTwo: {
                  radius: (mapSelect === (process.env.REACT_APP_MAP_DOUBLE || "") ? gameMap.ball[1].radius : 0),
                  positionX: (mapSelect === (process.env.REACT_APP_MAP_DOUBLE || "") ? gameMap.ball[1].positionX : 0),
                  positionY: (mapSelect === (process.env.REACT_APP_MAP_DOUBLE || "") ? gameMap.ball[1].positionY : 0)
                },
                displays: { width: gameMap.display.width, height: gameMap.display.height },
                traysOne: { height: gameMap.tray1.height, positionX: gameMap.tray1.positionX, positionY: gameMap.tray1.positionY, width: gameMap.tray1.width },
                traysTwo: { height: gameMap.tray2.height, positionX: gameMap.tray2.positionX, positionY: gameMap.tray2.positionY, width: gameMap.tray2.width },
                scores: { player1: one, player2: two, score1: gameMap.score1, score2: gameMap.score2 },
              })
            })
          }
        })
      }
      return () => {
        if (gameSocket) {
          gameSocket.off();
          gameSocket.disconnect();
        }
      }
    }
  }, [checkUrlQuery, nabi, mapSelect, userSelect, params.roomnums])

  return (
    <>
      {(mapSelect === 'map_0' && mapInfo) ? <MapDeafult mapInfo={mapInfo}></MapDeafult> : null}
      {(mapSelect === 'map_1' && mapInfo) ? <MapCustomOne mapInfo={mapInfo}></MapCustomOne> : null}
      {(mapSelect === 'map_2' && mapInfo) ? <MapCustomTwo mapInfo={mapInfo}></MapCustomTwo> : null}
      {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
    </>
  );
}