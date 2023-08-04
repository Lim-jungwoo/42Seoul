import React, { useRef, useContext } from 'react';
import styled, { css } from 'styled-components';
import SvgButton from '../other/SvgButton';
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

export default function ChatOutModal({ isType, setIsModal }: ChatModelType) {
    const divRef = useRef<HTMLDivElement | null>(null);
    const socket = useContext(SocketContext);
    const roomInfo = useContext(RoomInfo);


    const closeClick = () => {
        setIsModal(false);
    }

    const checkClick = () => {
        setIsModal(false);
        socket?.emit("channelLeave", {
            id: roomInfo?.id,
        })
    }

    return (
        <ModalBaseDiv isType={isType} ref={divRef}>
            <ModalBaseHeader>
                <SvgButton svgName='XmarkSvg' onClick={closeClick}></SvgButton>
            </ModalBaseHeader>
            <ModalBaseMain>
                <ModalBaseP>해당 채널을 나가시겠습니까?</ModalBaseP>
                <ModalBtnContainer isType={isType}>
                    <ModalBaseBtn onClick={checkClick}>예</ModalBaseBtn>
                    <ModalBaseBtn onClick={closeClick}>아니요</ModalBaseBtn>
                </ModalBtnContainer>
            </ModalBaseMain>
        </ModalBaseDiv>
    );
}