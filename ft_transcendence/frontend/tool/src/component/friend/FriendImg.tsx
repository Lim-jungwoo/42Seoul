import styled, { css } from 'styled-components';
import mainImage from '../../images/mainImage.png';


const FriendImgDiv = styled.div`
    &:before {
        width: 100%;
        height: 100%;
        box-sizing: border-box;
    }
`

const FriendImage = styled.img`
    width: 38px;
    height: 38px;
    margin: 0;
    border: 1px solid white;
    border-radius: 50%;
    overflow: hidden;
    object-fit: cover;
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-user-drag: none;
    user-drag: none;
    -webkit-touch-callout: none;
    display: inline-block;
`;

const FriendState = styled.div <{ isUserState: string }>`
    display: inline-block;
    width: 10px;
    height: 10px;
    border-radius: 50%;
    transform: translateX(-10px);
    overflow: hidden;

    ${(props) => props.isUserState === 'online' ? css`
        background-color: #76FF03;
    ` : (props.isUserState === 'offline' ? css`
        background-color: #37474F;
    ` : (props.isUserState === 'playing' || props.isUserState === 'waiting' || props.isUserState === 'gamelobby' ? css`
        background-color: #ffeb3b;
    ` : css`
        background-color: #ff5722;
    `))};
`

interface FriendImgType {
    imgData: string
    friendState: string
}

export default function FriendImg({ imgData, friendState }: FriendImgType) {
    return (
        <FriendImgDiv>
            <FriendImage src={imgData === "" ? mainImage : imgData} alt='friend img'></FriendImage>
            <FriendState isUserState={friendState}></FriendState>
        </FriendImgDiv>

    );
}