import React, { useEffect, useRef, useState, useContext, useCallback} from 'react';
import styled, { css } from 'styled-components';
import SvgButton from '../other/SvgButton';
import {SocketContext, RoomInfo} from '../../lib/socketContext';
import { useNavigate } from 'react-router-dom';

const ModalBaseDiv = styled.div`
    width: 500px;
    height: 300px;
    display: grid;
    grid-template-rows: 40px 220px;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
`;

const ModalBaseHeader = styled.header`
    background-color: #CFD8DC;
    text-align: right;
`;

const ModalForm = styled.form`
    grid-row: 2 / 5;
    algin-self: center;
    display: grid;
    align-items: center;
    grid-template-rows: 1fr 1fr 1fr;
    width: 100%
`;

const ModalFromContainer = styled.div<{ isOrder?: number }>`
    justify-self: start;
    display: flex;
    align-items: center;
    margin-left: 50px;
    margin-bottom: 7px;
    width: auto;
    margin-right: 50px;
    ${(props) => (props.isOrder === 1 ? css`grid-row: 1 / 2;` : null)};
    ${(props) => (props.isOrder === 2 ? css`grid-row: 2 / 3;` : null)};
    ${(props) => (props.isOrder === 3 ? css`grid-row: 3 / 4;` : null)};
`;

const ModalFormTitle = styled.div<{ isOrder?: number }>`
    ${(props) => (props.isOrder === 1 ? css`margin-right: 60px;` : css`margin-right: 20px;`)};
`;

const ModalBaseInput = styled.input.attrs((props) => ({
    type: props.type,
}))`
    ${(props) => (props.type === "text" ? css`width: 312px;` : null)}; 
    ${(props) => (props.type === "password" ? css`width: 280px;` : null)}; 
    margin-top: 5px;
    font-size: 1rem;
`;

const ModalBaseMain = styled.div`
    display: grid;
    align-items: center;
    width: 100%;
    grid-template-rows: 1fr 1fr 1fr 1fr;
    background-color: #90A4AE;
`;

const ModalBtnContainer = styled.div`
    justify-self: center;
    grid-row: 5 / 6; 
`

const ModalBaseBtn = styled.button`
    border: 0;
    font-size: 1rem;
    border-radius: 10px;
    width: 100px;
    height: 35px;
    margin: 10px;
    background-color: #2979FF;
    &:active {
        background-color: #2962FF
    }
`;

const ModalBaseP = styled.p<{ isError?: number }>`
    justify-self: center;
    align-self: center;
    algin-text: center;
    ${(props) => (props.isError === 1 ? null : css`grid-row: 1 / 2;`)};
    ${(props) => (props.isError === 1 ? css`margin-left: 20px;` : null)};
    ${(props) => (props.isError === 1 ? css`font-size: 1rem;` : css`font-size: 1rem;`)};
    // ${(props) => (props.isError === 1 ? css`margin-top: 3px;` : css`margin-top: 20px;`)};
    ${(props) => (props.isError === 1 ? css`color: #DD2C00;` : css`color: black;`)};
`;

interface ChatModelType {
    setIsModal: React.Dispatch<React.SetStateAction<boolean>>;
}

const BoxForRadio = styled.button<{ num: string, isSelect: string }>`
    padding: 5px;
    position: relative;
    border-radius: 1em;
    margin-right: 20px;
    max-width: 250px;
    ${(props) => (props.num === props.isSelect ? css`background-color: #2979FF;` : css`background-color: #A2D1E8;`)};
    word-wrap: break-word;
    word-break: break-all;
    &:hover {
        background-color: #2979FF;
    }
`;

export default function ChatCreateModal({ setIsModal }: ChatModelType) {
    const [isPassWord, setIsPassWord] = useState("");
    const [isTitle, setTitle] = useState("");
    const [errorMsg, setErrorMsg] = useState("");
    const [isSelect, setSelect] = useState<string>("public");
    const inputRef = useRef<HTMLInputElement | null>(null);
    const inputRefTitle = useRef<HTMLInputElement | null>(null);
    const divRef = useRef<HTMLDivElement | null>(null);
    const socket = useContext(SocketContext);
    const roomInfo = useContext(RoomInfo);
    
    const navigator = useNavigate();

    const inputOnChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        setIsPassWord(e.target.value);
        roomInfo?.setPassword(e.target.value);
    }

    const titleOnChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        e.target.value = e.target.value.replace(/[^A-Za-z0-9 ]/ig, '');
        setTitle(e.target.value);
        roomInfo?.setName(e.target.value);
    }

    const closeClick = () => {
        setIsModal(false);
    }

    const modalSubmit = (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
    }

    const checkFormInfo = () => {
        if ((isPassWord === "" && isSelect === "protected" )|| isTitle === "") {
            setErrorMsg("Fill the blank.")
            return true;
        }
        return false;
    }

    const checkClick = () => {
        if (checkFormInfo())
            return ;
        socket?.disconnect();
        navigator("/chatroom", {state: JSON.stringify(roomInfo)});
    }

    const radioClick = (e: React.MouseEvent<HTMLButtonElement>) => {
        setSelect((e.target as HTMLTableElement).id);
        roomInfo?.setType((e.target as HTMLTableElement).id);
        setIsPassWord("");
        roomInfo?.setPassword("");
    }

    const emitNewChannelId = useCallback(() => {
        if (!roomInfo?.type)
        {
            roomInfo?.setType("public");
            if (socket)
                socket?.emit("newChannelID", (nid: number) => {
                    roomInfo?.setID(nid.toString());
                });
        }
    }, [socket, roomInfo])

    useEffect(() => {
        emitNewChannelId();
    }, [emitNewChannelId])

    return (
        <ModalBaseDiv ref={divRef}>
            <ModalBaseHeader>
                <SvgButton svgName='XmarkSvg' onClick={closeClick}></SvgButton>
            </ModalBaseHeader>
            <ModalBaseMain>
                <ModalBaseP>Room Create</ModalBaseP>
                <ModalForm onSubmit={modalSubmit}>
                    <ModalFromContainer isOrder={1}>
                        <ModalFormTitle isOrder={1}>Type:</ModalFormTitle>
                        <BoxForRadio id="public" num={"public"} isSelect={isSelect} onClick={radioClick}>Public</BoxForRadio>
                        <BoxForRadio id="protected" num={"protected"} isSelect={isSelect} onClick={radioClick}>Protect</BoxForRadio>
                        <BoxForRadio id="private" num={"private"} isSelect={isSelect} onClick={radioClick}>Private</BoxForRadio>
                    </ModalFromContainer>
                    <ModalFromContainer isOrder={2}>
                        <ModalFormTitle>Title:</ModalFormTitle>
                        <ModalBaseInput type="text" maxLength={20} placeholder="Title" onChange={titleOnChange} value={isTitle} ref={inputRefTitle} />
                    </ModalFromContainer>
                    <ModalFromContainer isOrder={3}>
                        <ModalFormTitle>Password:</ModalFormTitle>
                        <ModalBaseInput type="password" maxLength={15} placeholder="Password" autoComplete="off" disabled={isSelect !== "protected"} onChange={inputOnChange} value={isPassWord} ref={inputRef} />
                    </ModalFromContainer>
                </ModalForm>
                <ModalBtnContainer>
                    {errorMsg !== "" && <ModalBaseP isError={1}>{errorMsg}</ModalBaseP>}
                    <ModalBaseBtn onClick={checkClick}>생성</ModalBaseBtn>
                </ModalBtnContainer>
            </ModalBaseMain>
        </ModalBaseDiv>
    );
}