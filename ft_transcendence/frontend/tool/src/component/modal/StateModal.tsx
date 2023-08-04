import React, { useCallback, useEffect, useRef } from 'react';
import styled, { css } from 'styled-components';
import SvgButton from '../other/SvgButton';

const StateOutDiv = styled.div`
    position: absolute;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    background-color: rgba(255, 255, 255, 0.1);
    z-index: 20;
    display: flex;
    justify-content: center;
    align-items: center;
`;

const ModalBaseDiv = styled.div`
    width: 450px;
    height: 110px;
    display: grid;
    grid-template-columns: 80px 370px;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
`;


const ModalBaseHeader = styled.header<{ isType?: string | React.Dispatch<React.SetStateAction<string>> }>`
    ${(props) => props.isType === "Success" ? css`
    background-color:  #c8e6c9
    ` : (props.isType === "Error" ? css`
    background-color:  #ffccbc
    ` : css`
    background-color:  #90A4AE
    `)};
    text-align: center;
    
`;

const ModalBaseMain = styled.main<{ isType?: string | React.Dispatch<React.SetStateAction<string>> }>`
    display: grid;
    grid-template-rows: 40px 70px;
    min-width: 370px;
    max-width: 370px;
    ${(props) => props.isType === "Success" ? css`
    background-color: #c8e6c9
    ` : (props.isType === "Error" ? css`
    background-color:  #ffccbc
    ` : css`
    background-color:  #90A4AE
    `)};
`;

const ModalBaseP = styled.p<{ isType?: string | React.Dispatch<React.SetStateAction<string>>, isCode?: number }>`
    min-width: 370px;
    max-width: 370px;
    ${(props) => props.isCode === 0 ? css`
        margin: 15px 0 0 0;
        height: 25px;
        font-size: 1.6rem;
        text-align: left;
        color: ${props.isType === "Success" ? '#004d40' : '#c62828'};
    `: css`
        margin: 10px 0 0 0;
        height: 60px;
        font-size: 1.3rem;
        color: black;
        color: ${props.isType === "Success" ? '#1b5e20' : '#dd2c00'};
    `}
    word-break: break-all;
`;

interface stateType {
    modalOpen: boolean;
    setModalOpen: React.Dispatch<React.SetStateAction<boolean>>;
    stateImg: string;
    msg: string;
}


export default function StateModal({ modalOpen, setModalOpen, stateImg, msg }: stateType) {
    const timeRef = useRef<NodeJS.Timeout | null>(null);
    const divRef = useRef<HTMLDivElement | null>(null);

    useEffect(() => {
        const outCliekClose = (e: MouseEvent) => {
            if (modalOpen && divRef.current && divRef.current.id === (e.target as HTMLDivElement).id)
                setModalOpen(false);
        }
        if (modalOpen)
            window.addEventListener("click", outCliekClose);
        return () => {
            window.removeEventListener("click", outCliekClose);
        }
    }, [modalOpen, setModalOpen]);

    const closeClick = useCallback(() => {
        setModalOpen(false);
    }, [setModalOpen])

    useEffect(() => {
        timeRef.current = setTimeout(closeClick, 1500);
        return () => {
            if (timeRef.current) {
                clearTimeout(timeRef.current);
                timeRef.current = null;
            }
        }
    }, [closeClick]);

    return (
        <StateOutDiv ref={divRef}>
            <ModalBaseDiv>
                <ModalBaseHeader isType={stateImg}>
                    {stateImg === 'Success' ? <SvgButton svgName="SuccessSvg" /> : <SvgButton svgName="ErrorSvg" />}
                </ModalBaseHeader>
                <ModalBaseMain isType={stateImg}>
                    <ModalBaseP isType={stateImg} isCode={0}>{stateImg}</ModalBaseP>
                    <ModalBaseP isType={stateImg} isCode={1}>{msg}</ModalBaseP>
                </ModalBaseMain>
            </ModalBaseDiv>
        </StateOutDiv>
    );
}