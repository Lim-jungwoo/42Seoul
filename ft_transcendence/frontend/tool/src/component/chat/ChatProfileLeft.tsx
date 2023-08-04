import { useState, useEffect, useContext, useCallback } from 'react';
import styled from 'styled-components';
import ProfileImg from '../profile/ProfileImg';
import ProfileInput from '../profile/ProfileInput';
import ToggleCheck from '../profile/ToggleCheck';
import LadderScore from '../profile/LadderScore';
import { pfPostApi } from '../../lib/postAxios';
import { EventInfo } from '../../lib/socketContext';
import StateModal from '../modal/StateModal';

const ProfileFrom = styled.form`
     display: grid;
     grid-template-rows: 320px repeat(3, 68px) 50px 50px 1fr;
     align-content: center;
     justify-items: center;
`;

interface profileInputType {
    id: number;
    typeText: string;
    baseText: string;
    valueText: string;
}

interface userInfo {
    data: {
        nickname: string;
        username: string;
        email: string;
        avatar: string;
        status: string;
        ladderrating: string;
        ladderscore: number;
        tfa: boolean;
    }
}

interface stateType {
    stateImg: string;
    msg: string;
}

export default function ProfileLeft() {
    const eventInfo = useContext(EventInfo);
    const [userInfo, setUserInfo] = useState<userInfo>({
        data: {
            nickname: "",
            username: "",
            email: "",
            avatar: "",
            status: "",
            ladderrating: "",
            ladderscore: 0,
            tfa: false,
        }
    });
    const [avatar, setAvatar] = useState("");
    const [isTfa, setIsTfa] = useState(false);
    const [nickname, setNickname] = useState("");
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })

    const getUserInfo = useCallback(
        async () => {
        try {
            const res = await pfPostApi.postLeftInput(eventInfo?.target || "");
            setUserInfo({
                data: {
                    nickname: res.data.nickname,
                    username: res.data.username,
                    email: res.data.email,
                    avatar: res.data.avatar || "",
                    status: res.data.status,
                    ladderrating: res.data.ladderrating,
                    ladderscore: res.data.ladderscore,
                    tfa: res.data.tfa,
                }
            })
            setNickname(res.data.nickname);
            setAvatar(res.data.avatar || "");
            setIsTfa(res.data.tfa);
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    },[eventInfo])

    useEffect(() => {
        getUserInfo();
    }, [getUserInfo])

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


    const leftSubmit = (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
    };

    return (
        <ProfileFrom onSubmit={leftSubmit}>
            <ProfileImg isDisabled={true} avatar={avatar} setAvatar={setAvatar}></ProfileImg>
            {listInput.map((item) => {
                return (
                    <ProfileInput
                        key={item.id}
                        id={item.id}
                        baseText={item.baseText}
                        isDisabled={true}
                        typeText={item.typeText}
                        valueText={item.valueText}
                        setNick={setNickname}
                    />
                );
            })}
            <LadderScore ladders={userInfo.data.ladderrating} scores={userInfo.data.ladderscore.toString()}></LadderScore>
            <ToggleCheck isDisabled={true} isCheck={isTfa} setIsTfa={setIsTfa}></ToggleCheck>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </ProfileFrom>
    )
};