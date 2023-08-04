import styled, { css } from 'styled-components';

//ChatBox Area
export const ChatBox = styled.div`
    grid-column: 2 / 3;
    grid-row: 1 / 2;
    display: flex;
    flex-direction: column;
    background-color: #5D879C;
    padding: 5px;
    gap: 3px;
    overflow-y: scroll;
    scroll-behavior: smooth;
    max-height: 644px;
    -ms-overflow-style: none;
    scrollbar-width: none;
    &::-webkit-scrollbar{
        display: none;
    }
`;

export const Welcome = styled.div`
    display: flex;
    justify-content: center;
`;

export const ForOther = styled.div`
    display: flex;
    align-items: flex-start;
    flex-direction: row;
`;

export const ForMe = styled.div`
    display: flex;
    align-items: flex-start;
    flex-direction: reverse-row;
    justify-content: flex-end;
`;

export const ForBattle = styled.div`
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: center;
`;

export const MsgBoxForOther = styled.div`
    padding: 10px;
    margin-top: 10px;
    position: relative;
    display: inline-block;
    border-radius: .4em;
    max-width: 230px;
    background-color: #A2D1E8;
    word-wrap: break-word;
    word-break: break-all;
    &:after {
        content: '';
        position: absolute;
        left: 0;
        top: 15px;
        width: 0;
        display: block;
        height: 0;
        border: 0.656em solid transparent;
        border-right-color: #A2D1E8;
        border-left: 0;
        border-bottom: 0;
        margin-top: -0.328em;
        margin-left: -0.656em;
    }
`;

export const MsgBoxForMe = styled.div`
    padding: 10px;
    margin-top: 10px;
    position: relative;
    border-radius: .4em;
    max-width: 250px;
    background-color: #CCEEFF;
    word-wrap: break-word;
    word-break: break-all;
    &:after {
        content: '';
        position: absolute;
        right: 0;
        top: 15px;
        width: 0;
        height: 0;
        border: 0.656em solid transparent;
        border-left-color: #CCEEFF;
        border-right: 0;
        border-bottom: 0;
        margin-top: -0.328em;
        margin-right: -0.656em;
    }
`;

export const MsgBoxForWhisperOther = styled.div`
    padding: 10px;
    margin-top: 10px;
    position: relative;
    display: inline-block;
    border-radius: .4em;
    max-width: 230px;
    background-color: #9FF5E3;
    word-wrap: break-word;
    word-break: break-all;
    &:after {
        content: '';
        position: absolute;
        left: 0;
        top: 15px;
        width: 0;
        display: block;
        height: 0;
        border: 0.656em solid transparent;
        border-right-color: #9FF5E3;
        border-left: 0;
        border-bottom: 0;
        margin-top: -0.328em;
        margin-left: -0.656em;
    }
`;

export const MsgBoxForWhisperMe = styled.div`
    padding: 10px;
    margin-top: 10px;
    position: relative;
    border-radius: .4em;
    max-width: 250px;
    background-color: #9FF5E3;
    word-wrap: break-word;
    word-break: break-all;
    &:after {
        content: '';
        position: absolute;
        right: 0;
        top: 15px;
        width: 0;
        height: 0;
        border: 0.656em solid transparent;
        border-left-color: #9FF5E3;
        border-right: 0;
        border-bottom: 0;
        margin-top: -0.328em;
        margin-right: -0.656em;
    }
`;

export const BoxForWelcom = styled.div`
    padding: 10px;
    margin-top: 10px;
    position: relative;
    border-radius: 1em;
    max-width: 250px;
    background-color: #A2D1E8;
    word-wrap: break-word;
    word-break: break-all;
`;

export const ChatImage = styled.img`
    width: 35px;
    height: 35px;
    margin: 3%;
    border: 1px solid white;
    border-radius: 70%;
    position: relative;
    overflow: hidden;
    object-fit: cover;
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-user-drag: none;
    user-drag: none;
    -webkit-touch-callout: none;
`;

export const BoxForVersus = styled.div`
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: center;
    padding: 10px;
    margin-top: 10px;
    position: relative;
    border-radius: 1.5em;
    width: 370px;
    height: 50px;
    background-color: #FFD98C;
    word-wrap: break-word;
    word-break: break-all;
`;

export const BoxForGame = styled.div`
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: center;
    padding: 10px;
    margin-top: 10px;
    position: relative;
    border-radius: 1.5em;
    width: 110px;
    height: 50px;
    background-color: #FFD98C;
    word-wrap: break-word;
    word-break: break-all;
`;

export const NickForVersus = styled.div`
    margin: 2%;
    white-space:nowrap;
    max-width: 70px;
    overflow: hidden;
    text-overflow: ellipsis;
`;

export const ButtonForVersus = styled.button`
    width: 35px;
    height: 35px;
    margin: 3%;
    border: 1px solid white;
    border-radius: 70%;
    position: relative;
    overflow: hidden;
    object-fit: cover;
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-user-drag: none;
    user-drag: none;
    -webkit-touch-callout: none;
    &:hover {
        background-color: #FFD98C;
    }
`;

//Profile Area
export const ProfileBox = styled.div`
    border-radius: 10px;
    grid-column: 1 / 2;
    grid-row: 1 / 2;
    background-color: #455A64;
    gap: 3px;
    padding: 5px;
    display: flex;
    flex-direction: column;
    align-items: center;
    overflow-y: scroll;
    scroll-behavior: smooth;
    max-height: 644px;
    -ms-overflow-style: none;
    scrollbar-width: none;
    &::-webkit-scrollbar{
        display: none;
    }
`;

export const ProfileOne = styled.button`
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: start;
    width: 85%;
    padding: 10px;
    margin-top: 10px;
    position: relative;
    border-radius: 3em;
    background-color: #CCEEFF;
    word-wrap: break-word;
    word-break: break-all;
    border-style: solid;
    border-width: 1px;
    &:hover {
        background-color: #FFD98C;
    }
`;

export const NickForProfile = styled.div`
    margin: 2%;
    white-space:nowrap;
    max-width: 80px;
    overflow: hidden;
    text-overflow: ellipsis;
`;

export const ProfileDropBox = styled.button`
    align-items: center;
    justify-content: center;
    width: 65%;
    padding: 5px;
    position: relative;
    border-radius: 0.5em;
    background-color: #CCEEFF;
    word-wrap: break-word;
    word-break: break-all;
    border-style: solid;
    border-width: 1px;
    &:hover {
        background-color: #FFD98C;
    }
`;

//Input Area
export const InputBox = styled.div`
    border-radius: 10px;
    background-color: #CEFAFF;
    grid-column: 2 / 3;
    grid-row: 2 / 3;
    display: flex;
    flex-direction: reverse-row;
    justify-content: flex-end;
`;

export const Input = styled.input<{ isWhisper: boolean }>`
    border: 0px;
    width: 90%;
    border-radius: 10px;
    ${(props) => (props.isWhisper === true ?
        css`background-color: #C2FFE3;`
        : css`background-color: #CEFAFF;`
    )}; 
    font-size: 17px;
`;

export const SendBtn = styled.button`
    width: 10%;
    height: 100%;
    align-items: center;
    justify-content: center;
    position: relative;
    border-radius: 0.5em;
    background-color: #FFD98C;
    word-wrap: break-word;
    word-break: break-all;
    border-style: solid;
    border-width: 0px;
    &:hover {
        background-color: #FFD98C;
    }
`; 

//Invite Area
export const InviteBox = styled.div`
    display: flex;
    flex-direction: row;
    align-items: center;
    flex-direction: reverse-row;
    justify-content: flex-end;
    border-radius: 10px;
    grid-column: 1 / 2;
    grid-row: 2 / 3;
    background-color: #B388FF;
`;

export const InviteInput = styled.input`
    border: 0px;
    width: 70%;
    height: 30%;
    border-radius: 0.2em;
    margin-right: 2px;
    font-size: 15px;
    background-color: #CEFAFF; 
`;

export const InviteBtn = styled.button`
    width: 20%;
    height: 30%;
    align-items: center;
    justify-content: center;
    position: relative;
    border-radius: 0.2em;
    background-color: #FFD98C;
    word-wrap: break-word;
    word-break: break-all;
    border-style: solid;
    border-width: 0px;
    margin-right: 10px;
    font-size: 15px;
    &:hover {
        background-color: #FFD98C;
    }
`;