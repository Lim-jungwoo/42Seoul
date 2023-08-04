import { useCallback, useEffect, useState } from 'react';
import { useSearchParams, useNavigate } from 'react-router-dom';
import styled from 'styled-components';
import * as PublicStyle from '../style/PublicStyle';
import ProfileImg from '../component/profile/ProfileImg';
import StateModal from '../component/modal/StateModal';
import ToggleCheck from '../component/profile/ToggleCheck';
import ProfileInput from '../component/profile/ProfileInput';
import mainImage from '../images/mainImage.png';
import { pfGetApi } from '../lib/getAxios';
import { pfPostApi } from '../lib/postAxios';

export const UserProfileCenter = styled.div`
    margin: auto;
    border-radius: 10px;
    display: grid;
    grid-template-columns: 1fr;
    justify-items: center;
`;

export const UserProfileHeader = styled.div`
    min-width: 400px;
    min-height: 30px;
    border-radius: 10px;
    color: #ECEFF1;
    background-color: #37474F;
    text-align: right;
`;

export const UserProfileMiddle = styled.div`
    min-width: 400px;
    min-height: 680px;
    border-radius: 10px;
    background-color: #1b1d25;
`;

const UserProfileFrom = styled.form`
     display: grid;
     grid-template-rows: 320px repeat(3, 68px) 50px 50px 1fr;
     align-content: center;
     justify-items: center;
`;

const UserModifyButton = styled.button`
    width: 200px;
    height: 50px;
    margin-top: 20px;
    background-color: transparent;
    font-size: 1.5rem;
    border: 2px solid white;
    color: #fafafa;
    border-radius: 24px;

    &:hover {
        background-color: rgba(247, 242, 242, 0.2) 
    }
`;

interface profileInputType {
    id: number;
    typeText: string;
    baseText: string;
    valueText: string;
}

interface stateType {
    stateImg: string;
    msg: string;
}

interface userInfo {
    data: {
        nickname: string;
        username: string;
        email: string;
        avatar: string;
        tfa: boolean;
    }
}

export default function Profile() {
    const [avatar, setAvatar] = useState(mainImage);
    const [nickname, setNickname] = useState("");
    const [isTfa, setIsTfa] = useState(false);
    const [modalOpen, setModalOpen] = useState(false);
    const [userInfo, setUserInfo] = useState<userInfo>({
        data: {
            nickname: "",
            username: "",
            email: "",
            avatar: "",
            tfa: false,
        }
    });

    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })
    const [searchParams] = useSearchParams();
    const navi = useNavigate();

    const userSubmit = (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
    };

    const getUserIntra = useCallback(
        async () => {
            try {
                if (nickname !== "") return;
                const res = await pfGetApi.getLeftInput()
                if (res) {
                    setUserInfo({
                        data: {
                            nickname: res.data.nickname,
                            username: res.data.username,
                            email: res.data.email,
                            avatar: avatar,
                            tfa: false,
                        }
                    })
                    setNickname(res.data.nickname);
                }
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message || "" });
            }
        }, [avatar, setUserInfo, nickname]);

    const editUserInfo = async () => {
        try {
            const res = await pfPostApi.patchLeftUpdate(nickname, avatar, isTfa);
            if (res.status === 200) {
                navi('/main');
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    const listInput: profileInputType[] = [
        {
            id: 1,
            typeText: 'text',
            baseText: '닉네임',
            valueText: nickname
        },
        {
            id: 2,
            typeText: 'text',
            baseText: '인트라',
            valueText: userInfo.data.username
        },
        {
            id: 3,
            typeText: 'email',
            baseText: '이메일',
            valueText: userInfo.data.email
        }
    ];

    useEffect(() => {
        const token = searchParams.get('token') || null;
        const rtoken = searchParams.get('rtoken') || null;
        const stoken = sessionStorage.getItem("token") || null;
        const srtoken = sessionStorage.getItem("rtoken") || null;
        if (token !== null && rtoken !== null && stoken === null && srtoken === null) {
            sessionStorage.removeItem('token');
            sessionStorage.removeItem('rtoken');
            sessionStorage.setItem('token', token);
            sessionStorage.setItem('rtoken', rtoken);
            window.history.pushState("", "", '/profile');
            getUserIntra();
        }
        else {
            const token = sessionStorage.getItem("token") || null;
            const rtoken = sessionStorage.getItem("rtoken") || null;
            if (!token || !rtoken)
                navi("/");
        }
    }, [searchParams, navi, getUserIntra]);

    return (
        <PublicStyle.PublicContainer>
            <UserProfileCenter>
                <UserProfileMiddle>
                    <UserProfileFrom onSubmit={userSubmit}>
                        <ProfileImg isDisabled={false} avatar={avatar} setAvatar={setAvatar}></ProfileImg>
                        {listInput.map((item) => {
                            return (
                                <ProfileInput
                                    key={item.id}
                                    id={item.id}
                                    baseText={item.baseText}
                                    isDisabled={item.id === 1 ? false : true}
                                    typeText={item.typeText}
                                    valueText={item.valueText}
                                    setNick={setNickname}
                                />
                            );
                        })}
                        <ToggleCheck isDisabled={false} isCheck={isTfa} setIsTfa={setIsTfa}></ToggleCheck>
                        <UserModifyButton onClick={() => editUserInfo()}>등        록</UserModifyButton>
                    </UserProfileFrom>
                </UserProfileMiddle>
            </UserProfileCenter>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </PublicStyle.PublicContainer>
    );
}