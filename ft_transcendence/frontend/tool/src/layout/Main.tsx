import { useState, useEffect } from 'react';
import { Link, useSearchParams, useNavigate } from 'react-router-dom';
import * as MainStyled from '../style/MainStyle'
import * as PublicStyled from '../style/PublicStyle'
import DropDown from '../component/other/DropDown';
import SvgButton from '../component/other/SvgButton';
import PublicModal from '../component/modal/PublicModal';
import { Socket, io } from "socket.io-client";

export default function Main() {
    const [isModal, setIsModal] = useState(false);
    const [modalNum, setModalNum] = useState(0);
    const [searchParams] = useSearchParams();
    const nabi = useNavigate();

    const handelFriendClick = () => {
        setModalNum(1);
        setIsModal(!isModal);
    }

    useEffect(() => {
        const token = searchParams.get('token');
        const rtoken = searchParams.get('rtoken');
        if (token !== null && rtoken !== null) {
            sessionStorage.removeItem('token');
            sessionStorage.removeItem('rtoken');
            sessionStorage.setItem('token', token);
            sessionStorage.setItem('rtoken', rtoken)
            window.history.pushState("", "", '/main');
        } else {
            const token = sessionStorage.getItem("token") || null;
            const rtoken = sessionStorage.getItem("rtoken") || null;
            if (!token || !rtoken)
                nabi("/");
        }
    }, [searchParams, nabi])

    useEffect(() => {
        const token = sessionStorage.getItem('rtoken') || null;
        if (token) {
            const socketOption = {
                path: '/main',
                closeOnBeforeunload: true,
                extraHeaders: {
                    Authorization: `Bearer ${token}`,
                },
            }
            let mainSocket: Socket | null = io(process.env.REACT_APP_API_URL || "", socketOption);
            mainSocket.on("connect", () => {
            })
            mainSocket.on("disconnect", () => {
            })
            mainSocket.on("goHome", () => {
                mainSocket?.off();
                nabi("/");
            })
            return () => {
                if (mainSocket)
                    mainSocket.disconnect();
                mainSocket = null;
            }
        }
    }, [nabi])

    return (
        <PublicStyled.PublicContainer>
            <PublicStyled.PublicCenter>
                <PublicStyled.PublicHeader>
                    <DropDown setIsModal={setIsModal} setModalNum={setModalNum} />
                </PublicStyled.PublicHeader>
                <PublicStyled.PublicMiddle isLayout='Main'>
                    <MainStyled.MainMiddleFirst>
                        <Link to="/chat"><SvgButton svgName='ChatingSvg' /></Link>
                        <Link to="/game"><SvgButton svgName='GameSvg' /></Link>
                    </MainStyled.MainMiddleFirst>
                    <MainStyled.MainMiddleLast>
                        <SvgButton svgName='FriendSvg' onClick={handelFriendClick} />
                    </MainStyled.MainMiddleLast>
                </PublicStyled.PublicMiddle>
            </PublicStyled.PublicCenter>
            {isModal && <PublicModal isModal={isModal} isModalNum={modalNum} setIsModal={setIsModal} />}
        </PublicStyled.PublicContainer>
    );
}