import React, { useRef, useState, useContext} from 'react';
import styled, { css } from 'styled-components';
import SvgButton from '../other/SvgButton';
import { SocketContext, StateModalControllerContext } from '../../lib/socketContext';

const ModalBaseDiv = styled.div`
    width: 450px;
    height: 240px;
    display: grid;
    grid-template-rows: 40px 200px;
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
    justfiy-self: center;
    align-items: center;
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
    ${(props) => (props.isError === 1 ? css`color: #DD2C00;` : css`color: black;`)};
`;

interface ChatModelType {
    setIsModal: React.Dispatch<React.SetStateAction<boolean>>;
}

export default function ChatSetPassword({ setIsModal }: ChatModelType) {
    const inputRef = useRef<HTMLInputElement | null>(null);
    const divRef = useRef<HTMLDivElement | null>(null);

    const [isPassWord, setIsPassWord] = useState("");
    const [errorMsg, setErrorMsg] = useState("");
    const [isPublic, setIsPublic] = useState<boolean>(false);

    const socket = useContext(SocketContext);
    const stateModal = useContext(StateModalControllerContext);

    const inputOnChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        setIsPassWord(e.target.value);
    }

    const closeClick = () => {
        setIsModal(false);
    }

    const modalSubmit = (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
    }

    const checkClick = () => {
        if (isPassWord === "" && isPublic === false) {
            setErrorMsg("Blank password makes your Room Public. Is it okay?")
            setIsPublic(!isPublic);
            return;
        }
        socket?.emit("setPassword", {
            password: isPassWord,
        }, (resp: any) => {
            if (resp.status){
                stateModal?.setOpen(true);
                stateModal?.setStateType({
                    stateImg: "Error",
                    msg: resp.message,
                });
            }
        })
        setIsModal(false);
    }

    return (
        <ModalBaseDiv ref={divRef}>
            <ModalBaseHeader>
                <SvgButton svgName='XmarkSvg' onClick={closeClick}></SvgButton>
            </ModalBaseHeader>
            <ModalBaseMain>
                <ModalBaseP>New Password</ModalBaseP>
                <ModalForm onSubmit={modalSubmit}>
                    <ModalFromContainer isOrder={2}>
                        <ModalFormTitle>Password:</ModalFormTitle>
                        <ModalBaseInput type="password" maxLength={15} placeholder="NewPassword" autoComplete="off" onChange={inputOnChange} value={isPassWord} ref={inputRef} />
                    </ModalFromContainer>
                </ModalForm>
                {errorMsg !== "" && <ModalBaseP isError={1}>{errorMsg}</ModalBaseP>}
                <ModalBtnContainer>
                    <ModalBaseBtn onClick={checkClick}>변경</ModalBaseBtn>
                </ModalBtnContainer>
            </ModalBaseMain>
        </ModalBaseDiv>
    );
}