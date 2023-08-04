import React, { useState, useEffect, useRef, useCallback } from 'react';
import styled, { css } from 'styled-components';
import NabigationBar from '../other/NabigationBar';
import SvgButton from '../other/SvgButton';
import FriendImg from './FriendImg';
import Paginnation from '../other/Pagination';
import { friendPostApi } from '../../lib/postAxios';
import StateModal from '../modal/StateModal';

const FriendDiv = styled.div`
    width: 400px;
    height: 450px;
    display: grid;
    grid-template-rows: 40px 370px 40px;
`;
const FriendHeader = styled.header`
    background-color: #CFD8DC;
    text-align: right;
`;
const FriendMain = styled.main`
    background-color: #90A4AE;
`;
const FriendFooter = styled.footer`
    background-color: #90A4AE;
`;
const FriendTable = styled.table< { trSum: string } >`
    width: 100%;
    margin: 0;
    max-height: ${(props) => props.trSum};
    padding: 0;
    cursor: default;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
    text-align: center;
`;
const FriendTr = styled.tr`
    border: 1px solid black;
`;
const FriendTd = styled.td<{ isWidth: number, isVisble?: boolean }>`
    padding: 10px 5px 10px 5px;
    color: #909099;
    background-color: #455A64;
    vertical-align: middle;
    ${(props) => props.isVisble === true ? css`
        display: none;
    ` : css``}
    ${(props) => props.isWidth === 0 ? css`
        width: 43px;
    ` : (props.isWidth === 1 ? css`
        width: 40px;
    ` : (props.isWidth === 2 ? css`
        width: 100px;
    ` : css`
        padding: 0;
        width: 80px;
    `))};
`;
const FriendButton = styled.button`
    width: 40px;
    height: 40px;
    border: 0;
    margin: 0 3px 0 3px;
    border-radius: 25px;
    border: 0px;
    background-color: #B388FF;
    color: #000000;
    &:active {
        background-color: #343434;
        color: #aa00ff;
    }
`;

interface FriendModelType {
    setIsModal: React.Dispatch<React.SetStateAction<boolean>>;
}

interface FrinedData {
    email: string,
    username: string,
    nickname: string,
    avatar: string,
    status: string,
    ladderrating: string,
    ladderscore: number,
    tfa: boolean,
    isfriend: boolean,
}

interface stateType {
    stateImg: string;
    msg: string;
}

export default function FriendModal({ setIsModal }: FriendModelType) {
    const tableRef = useRef<HTMLTableSectionElement | null>(null)
    const [nabiNum, setNabiNum] = useState(0);
    const [beforeNabiNum, setBeforeNabiNum] = useState(0);
    const [selectNum, setSelectNum] = useState(1);
    const [beforeSelectNum, setBeforeSelectNum] = useState(1);
    const [allPageNum, setAllPageNum] = useState(1);
    const [friendInfo, setFriendInfo] = useState<Array<FrinedData>>([]);
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })

    const handelCloseModal = () => setIsModal(false);

    const getFiveUser = useCallback(
        async (beforeNums: number, nums: number, firstName: string, lastName: string) => {
            try {
                if (nabiNum !== 0) return;
                if (firstName === "" && lastName === "") {
                    setBeforeSelectNum(1);
                    setSelectNum(1);
                }
                const res = await friendPostApi.postFiveUser(beforeNums, nums, firstName, lastName);
                setFriendInfo(res.data[0]);
                const totals = (parseInt(res.data[1].total) % 5 !== 0 || Math.floor(parseInt(res.data[1].total) / 5) === 0 ? Math.floor(parseInt(res.data[1].total) / 5) + 1
                    : Math.floor(parseInt(res.data[1].total) / 5));
                setAllPageNum(totals);
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message });
            }
        }, [nabiNum]);

    const getFiveFriend = useCallback(
        async (beforeNums: number, nums: number, firstName: string, lastName: string) => {
            try {
                if (nabiNum !== 1) return;
                if (firstName === "" && lastName === "") {
                    setBeforeSelectNum(1);
                    setSelectNum(1);
                }
                const res = await friendPostApi.postFiveFriend(beforeNums, nums, firstName, lastName);
                setFriendInfo(res.data[0]);
                const totals = (parseInt(res.data[1].total) % 5 !== 0 || Math.floor(parseInt(res.data[1].total) / 5) === 0 ? Math.floor(parseInt(res.data[1].total) / 5) + 1
                    : Math.floor(parseInt(res.data[1].total) / 5));
                setAllPageNum(totals);
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message });
            }
        }, [nabiNum]);


    const getFiveReq = useCallback(
        async (beforeNums: number, nums: number, firstName: string, lastName: string) => {
            try {
                if (nabiNum !== 2) return;
                if (firstName === "" && lastName === "") {
                    setBeforeSelectNum(1);
                    setSelectNum(1);
                }
                const res = await friendPostApi.postFiveRequest(beforeNums, nums, firstName, lastName);
                setFriendInfo(res.data[0]);
                const totals = (parseInt(res.data[1].total) % 5 !== 0 || Math.floor(parseInt(res.data[1].total) / 5) === 0 ? Math.floor(parseInt(res.data[1].total) / 5) + 1
                    : Math.floor(parseInt(res.data[1].total) / 5));
                setAllPageNum(totals);
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message });
            }
        }, [nabiNum]);

    const friendReqSend = async (e: React.MouseEvent) => {
        try {
            let postUser = (e.target as HTMLElement).parentElement?.parentElement?.children[2].innerHTML || "";
            let res = await friendPostApi.postFriendSend(postUser);
            if (res.status === 200) {
                setModalOpen(true);
                setStateData({ stateImg: "Success", msg: "친구 요청을 보냈습니다." });
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    const friendDelete = async (e: React.MouseEvent) => {
        try {
            let postUser = (e.target as HTMLElement).parentElement?.parentElement?.children[2].innerHTML || "";
            let res = await friendPostApi.postFriendDel(postUser);
            if (res.status === 200) {
                if (nabiNum === 0) getFiveUser(1, 1, "", "");
                if (nabiNum === 1) getFiveFriend(1, 1, "", "");
                setModalOpen(true);
                setStateData({ stateImg: "Success", msg: "친구 삭제가 완료되었습니다." });
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    const friendAccept = async (e: React.MouseEvent) => {
        try {
            const postUser = (e.target as HTMLElement).parentElement?.parentElement?.children[2].innerHTML || "";
            const res = await friendPostApi.postFriendAccept(postUser);
            if (res.status === 200) {
                if (nabiNum === 2) getFiveReq(1, 1, "", "");
                setModalOpen(true);
                setStateData({ stateImg: "Success", msg: "친구 수락을 하셨습니다." });
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    const friendDecline = async (e: React.MouseEvent) => {
        try {
            const postUser = (e.target as HTMLElement).parentElement?.parentElement?.children[2].innerHTML || "";
            const res = await friendPostApi.postFriendDecline(postUser);
            if (res.status === 200) {
                if (nabiNum === 2) getFiveReq(1, 1, "", "");
                setModalOpen(true);
                setStateData({ stateImg: "Success", msg: "친구 수락을 거절하셨습니다." });
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    const userBlock = async (e: React.MouseEvent) => {
        try {
            const blockUser = (e.target as HTMLElement).parentElement?.parentElement?.children[2].innerHTML || "";
            const res = await friendPostApi.postUserBlock(blockUser);
            if (res.status === 200) {
                setModalOpen(true);
                setStateData({ stateImg: "Success", msg: "해당 유저를 BLOCK 처리 하였습니다." });
            }
        } catch (e: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: e.response.data.message });
        }
    }

    useEffect(() => {
        if (nabiNum === 0) getFiveUser(1, 1, "", "");
        if (nabiNum === 1) getFiveFriend(1, 1, "", "");
        if (nabiNum === 2) getFiveReq(1, 1, "", "");
    }, [nabiNum, getFiveUser, getFiveFriend, getFiveReq]);

    useEffect(() => {
        const firstName = tableRef.current?.firstChild?.childNodes[2]?.childNodes[0]?.textContent || "";
        const lastName = tableRef.current?.lastChild?.childNodes[2]?.childNodes[0]?.textContent || "";
        if (beforeNabiNum !== nabiNum) {
            setBeforeNabiNum(nabiNum);
            return;
        }
        if (beforeSelectNum !== selectNum) {
            if (nabiNum === 0 && beforeNabiNum === 0) getFiveUser(beforeSelectNum, selectNum, firstName, lastName);
            if (nabiNum === 1 && beforeNabiNum === 1) getFiveFriend(beforeSelectNum, selectNum, firstName, lastName);
            if (nabiNum === 2 && beforeNabiNum === 2) getFiveReq(beforeSelectNum, selectNum, firstName, lastName);
        }
    }, [selectNum, beforeSelectNum, beforeNabiNum, nabiNum, getFiveUser, getFiveFriend, getFiveReq])


    return (
        <FriendDiv>
            <FriendHeader>
                <SvgButton svgName='XmarkSvg' onClick={handelCloseModal}></SvgButton>
            </FriendHeader>
            <FriendMain>
                <NabigationBar isListHeader='전체,친구,초대' setBeforeNabiNum={setBeforeNabiNum} setNabiNum={setNabiNum}></NabigationBar>
                <FriendTable trSum='460px'>
                    <tbody ref={tableRef}>
                        {friendInfo.map((friend) => {
                            return (
                                <FriendTr key={"user_" + friend.username} id={"user_" + friend.username}>
                                    <FriendTd isWidth={0}>
                                        <FriendImg imgData={friend.avatar || ""} friendState={friend.status}></FriendImg>
                                    </FriendTd>
                                    <FriendTd isWidth={1}>{friend.status}</FriendTd>
                                    <FriendTd isWidth={1} isVisble={true}>{friend.username}</FriendTd>
                                    <FriendTd isWidth={2}>{friend.nickname}</FriendTd>
                                    <FriendTd isWidth={3}>
                                        {(nabiNum === 0) && <FriendButton onClick={userBlock}>유저차단</FriendButton>}
                                        {(nabiNum === 0 && !friend.isfriend) && <FriendButton onClick={friendReqSend}>친구추가</FriendButton>}
                                        {(nabiNum === 0 && friend.isfriend) && <FriendButton onClick={friendDelete}>친구삭제</FriendButton>}
                                        {nabiNum === 1 && <FriendButton onClick={friendDelete}>친구삭제</FriendButton>}
                                        {nabiNum === 2 && <FriendButton onClick={friendAccept}>친구수락</FriendButton>}
                                        {nabiNum === 2 && <FriendButton onClick={friendDecline}>친구거절</FriendButton>}
                                    </FriendTd>
                                </FriendTr>
                            );
                        })}
                    </tbody>
                </FriendTable>
            </FriendMain>
            <FriendFooter>
                <Paginnation allPageNum={allPageNum} selectNum={selectNum} setSelectNum={setSelectNum} setBeforeSelectNum={setBeforeSelectNum} />
            </FriendFooter>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </FriendDiv>
    );
}