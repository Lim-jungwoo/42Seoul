import { useState, useEffect } from 'react';
import styled from 'styled-components';
import ProfileImg from './ProfileImg';
import ProfileInput from './ProfileInput';
import ToggleCheck from './ToggleCheck';
import LadderScore from './LadderScore';
import StateModal from '../modal/StateModal';
import { pfGetApi } from '../../lib/getAxios';
import { pfPostApi } from '../../lib/postAxios';

const ProfileFrom = styled.form`
     display: grid;
     grid-template-rows: 320px repeat(3, 68px) 50px 50px 1fr;
     align-content: center;
     justify-items: center;
`;

const ModifyButton = styled.button`
    width: 200px;
    height: 50px;
    margin-top: 4px;
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
    const [useModify, setUseModify] = useState(true);
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

    const getUserInfo = async () => {
        try {
            const res = await pfGetApi.getLeftInput();
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
    }

    const editUserInfo = async () => {
        try {
            const res = await pfPostApi.patchLeftUpdate(nickname, avatar, isTfa);
            if (res.status === 200) {
                setModalOpen(true);
                setStateData({ stateImg: "Success", msg: "프로필을 수정하였습니다." });
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
            getUserInfo();
        }
    }

    useEffect(() => {
        getUserInfo();
    }, [])

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

    const changeModify = () => {
        if (!useModify) {
            if (nickname === "" || nickname === null || nickname === undefined) {
                return;
            }
            editUserInfo();
        }
        setUseModify(!useModify);
    }
    return (
        <ProfileFrom onSubmit={leftSubmit}>
            <ProfileImg isDisabled={useModify} avatar={avatar} setAvatar={setAvatar}></ProfileImg>
            {listInput.map((item) => {
                return (
                    <ProfileInput
                        key={item.id}
                        id={item.id}
                        baseText={item.baseText}
                        isDisabled={useModify === false && item.id === 1 ? useModify : true}
                        typeText={item.typeText}
                        valueText={item.valueText}
                        setNick={setNickname}
                    />
                );
            })}
            <LadderScore ladders={userInfo.data.ladderrating} scores={userInfo.data.ladderscore.toString()}></LadderScore>
            <ToggleCheck isDisabled={useModify} isCheck={isTfa} setIsTfa={setIsTfa}></ToggleCheck>
            <ModifyButton onClick={changeModify}>{useModify ? '수정' : '등록'}</ModifyButton>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </ProfileFrom>

    )
};
