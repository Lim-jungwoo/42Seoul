import { useNavigate } from 'react-router-dom';
import styled from 'styled-components';
import SvgButton from '../other/SvgButton';
import { GameModalPropsType } from './GameInterface';

const BaseOutDiv = styled.div`
    position: absolute;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    background-color: rgba(255, 255, 255, 0.1);
    z-index: 11;
    display: flex;
    justify-content: center;
    align-items: center;
`;

const ModalBaseDiv = styled.div`
    width: 300px;
    height: 150px;
    display: grid;
    grid-template-rows: 40px 110px;
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

const ModalBaseMain = styled.main`
    background-color: #90A4AE;
    text-align: center;
`;

const ModalBaseBtn = styled.button`
    border: 0;
    font-size: 1rem;
    border-radius: 10px;
    width: 100px;
    height: 35px;
    margin: 20px 10px 10px 10px;
    background-color: #2979FF;
    &:active {
        background-color: #2962FF
    }
`;

const ModalBaseP = styled.p`
    font-size: 1rem;
    margin-top: 20px;
    color: black;
`;

export default function GameModal({ gameMainSocket, roomData, setOpenGameModal }: GameModalPropsType) {
    const nabi = useNavigate();

    const closeClick = () => {
        setOpenGameModal(false);
    }

    const watchClick = () => {
        setOpenGameModal(false);
        if (gameMainSocket) {
            let mapString = roomData.split(',');
            nabi(`/game/gameroom/${mapString[0]}?maptype=${mapString[1]}&usertype=${process.env.REACT_APP_USER_SELECT}`);
        }
    }
    return (
        <BaseOutDiv>
            <ModalBaseDiv>
                <ModalBaseHeader>
                    <SvgButton svgName='XmarkSvg' onClick={closeClick}></SvgButton>
                </ModalBaseHeader>
                <ModalBaseMain>
                    <ModalBaseP>해당 게임을 관전하시겠습니까?</ModalBaseP>
                    <ModalBaseBtn onClick={watchClick}>관 전</ModalBaseBtn>
                    <ModalBaseBtn onClick={closeClick}>취 소</ModalBaseBtn>
                </ModalBaseMain>
            </ModalBaseDiv>
        </BaseOutDiv>
    );
}