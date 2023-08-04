import React, { useEffect, useRef, useState, useContext } from 'react';
import styled, { css } from 'styled-components';
import SvgButton from '../other/SvgButton';
import { useNavigate } from 'react-router-dom';
import {SocketContext, RoomInfo} from '../../lib/socketContext';

const ModalBaseDiv = styled.div<{ isType?: string }>`
    width: 300px;
    ${(props) => (props.isType === "protected" ? css`height: 180px;` : css`height: 150px`)};
    display: grid;
    ${(props) => (props.isType === "protected" ? css`grid-template-rows: 40px 150px;` : css`grid-template-rows: 40px 110px`)};
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

const ModalBaseInput = styled.input.attrs(() => ({
    type: 'password'
}))`
    grid-row: 2 / 3; 
    margin-top: 10px;
    font-size: 1rem;
`;

const ModalBaseMain = styled.main<{ isType?: string }>`
    display: grid;
    justify-content: center;
    align-items: center;
    text-align: center;
    ${(props) => (props.isType === "protected" ? css`grid-template-rows: 1fr 1fr 1fr;` : css`grid-template-rows: 1fr 1fr`)};
    background-color: #90A4AE;
`;

const ModalBtnContainer = styled.div<{ isType?: string }>`
    ${(props) => (props.isType === "protected" ? css`grid-template-rows: grid-row: 3 / 4;` : css`grid-row: 2 / 3;`)};
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
    grid-row: 1 / 2;
    ${(props) => (props.isError === 1 ? css`font-size: 0.5rem;` : css`font-size: 1rem;`)};
    ${(props) => (props.isError === 1 ? css`margin-top: 3px;` : css`margin-top: 20px;`)};
    ${(props) => (props.isError === 1 ? css`color: #DD2C00;` : css`color: black;`)};
`;

interface ChatModelType {
    isType?: string;
    setIsModal: React.Dispatch<React.SetStateAction<boolean>>;
}

export default function ChatBaseModal({ isType, setIsModal }: ChatModelType) {
    const [isPassWord, setIsPassWord] = useState("");
    const [errorMsg, setErrorMsg] = useState("");
    const inputRef = useRef<HTMLInputElement | null>(null);
    const divRef = useRef<HTMLDivElement | null>(null);
    const navigator = useNavigate();
    const socket = useContext(SocketContext);
    const roomInfo = useContext(RoomInfo);

    const inputOnChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        setIsPassWord(e.target.value);
        roomInfo?.setPassword(e.target.value);
    }

    const closeClick = () => {
        setIsModal(false);
    }

    const modalSubmit = (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
    }
    const checkClick = () => {

        if (isPassWord === "" && isType === 'protected' && roomInfo?.isIn === "false") {
            setErrorMsg("비번을 입력하지 않았습니다.")
            return;
        }
        setIsModal(false);
        socket?.disconnect();
        navigator("/chatroom", {state: JSON.stringify(roomInfo)});
    }

    useEffect(() => {
        if (isType === 'protected')
            inputRef.current?.focus();
    }, [isType])

    return (
        <ModalBaseDiv isType={isType} ref={divRef}>
            <ModalBaseHeader>
                <SvgButton svgName='XmarkSvg' onClick={closeClick}></SvgButton>
            </ModalBaseHeader>
            <ModalBaseMain>
                <ModalBaseP>해당 채널에 들어가시겠습니까?</ModalBaseP>
                {isType === 'protected' && roomInfo?.isIn === "false" ?
                    <form onSubmit={modalSubmit}>
                        <ModalBaseInput autoComplete="off" onChange={inputOnChange} value={isPassWord} ref={inputRef} />
                        {errorMsg !== "" && <ModalBaseP isError={1}>{errorMsg}</ModalBaseP>}
                    </form>
                    : null
                }
                <ModalBtnContainer isType={isType}>
                    <ModalBaseBtn onClick={checkClick}>확인</ModalBaseBtn>
                    <ModalBaseBtn onClick={closeClick}>종료</ModalBaseBtn>
                </ModalBtnContainer>
            </ModalBaseMain>
        </ModalBaseDiv>
    );
}