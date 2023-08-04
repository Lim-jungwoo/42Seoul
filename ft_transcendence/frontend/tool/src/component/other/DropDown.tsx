import { useState, useEffect, useRef } from 'react';
import * as DropStyle from '../../style/DropStyle';
import SvgButton from './SvgButton';
import { logOutAPi } from '../../lib/getAxios';
import StateModal from '../modal/StateModal';

interface stateType {
    stateImg: string;
    msg: string;
}
interface ProfileType {
    setIsModal: React.Dispatch<React.SetStateAction<boolean>>;
    setModalNum: React.Dispatch<React.SetStateAction<number>>;
}

export default function DropDown({ setIsModal, setModalNum }: ProfileType) {
    const [dropOpen, setDropOpen] = useState(false);
    const dropRef = useRef<HTMLDivElement | null>(null);
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })

    const openDropMenu = () => {
        setDropOpen(!dropOpen);
    };

    const logOutMenu = async () => {
        try {
            const res = await logOutAPi.getLogOut();
            if (res.status === 200) {
                sessionStorage.removeItem("token");
                sessionStorage.removeItem("rtoken");
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    const onProfile = () => {
        setIsModal(true);
        setModalNum(8);
    }

    useEffect(() => {
        const outClickClose = (e: MouseEvent) => {
            if (dropOpen && dropRef.current && !dropRef.current.contains(e.target as HTMLElement)) {
                setDropOpen(false);
            }
        }
        if (dropOpen)
            window.addEventListener("click", outClickClose);
        return () => {
            window.removeEventListener("click", outClickClose);
        }
    }, [dropOpen])

    return (
        <DropStyle.DropMain ref={dropRef}>
            <SvgButton svgName='MenuSvg' onClick={openDropMenu}></SvgButton>
            <div>
                <DropStyle.ShowHiddenDropMenu dropOpen={dropOpen}>
                    <DropStyle.ListDropMenu onClick={onProfile}>프로필</DropStyle.ListDropMenu>
                    <DropStyle.LinkDrop to="/">
                        <DropStyle.ListDropMenu onClick={logOutMenu}>로그아웃</DropStyle.ListDropMenu>
                    </DropStyle.LinkDrop>
                </DropStyle.ShowHiddenDropMenu>
            </div>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </DropStyle.DropMain>
    );
}