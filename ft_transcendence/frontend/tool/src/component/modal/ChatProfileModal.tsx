import React, { useRef } from 'react';
import styled from 'styled-components';
import SvgButton from '../other/SvgButton';
import * as PublicStyle from '../../style/PublicStyle';
import ProfileRight from '../chat/ChatProfileRight';
import ProfileLeft from '../chat/ChatProfileLeft';

const ModalBaseDiv = styled.div`
    width: 800px;
    height: 760px;
    display: grid;
    grid-template-rows: 40px auto;
    background-color: #1b1d25;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
    border-radius: 0.4em;
`;

interface ChatProfileType {
    setIsModal: React.Dispatch<React.SetStateAction<boolean>>;
}

export default function ChatBaseModal({ setIsModal }: ChatProfileType) {
    const divRef = useRef<HTMLDivElement | null>(null);

    const closeClick = () => {
        setIsModal(false);
    }

    return (
        <ModalBaseDiv ref={divRef}>
            <PublicStyle.PublicCenter>
                <PublicStyle.PublicHeader>
                        <SvgButton svgName='ReturnSvg' onClick={closeClick}></SvgButton>
                </PublicStyle.PublicHeader>
                <PublicStyle.PublicMiddle isLayout='Profile'>
                    <ProfileLeft />
                    <ProfileRight />
                </PublicStyle.PublicMiddle>
            </PublicStyle.PublicCenter>
        </ModalBaseDiv>
    );
}