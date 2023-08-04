import { ReactComponent as CameraSvg } from '../../svgs/camera.svg';
import { ReactComponent as MenuSvg } from '../../svgs/menu.svg';
import { ReactComponent as ChatingSvg } from "../../svgs/chating.svg";
import { ReactComponent as FriendSvg } from "../../svgs/friend.svg";
import { ReactComponent as GameSvg } from "../../svgs/gamepad.svg";
import { ReactComponent as ReturnSvg } from "../../svgs/return.svg";
import { ReactComponent as TrophySvg } from "../../svgs/trophy.svg";
import { ReactComponent as QuestionSvg } from "../../svgs/question.svg";
import { ReactComponent as PubllicSvg } from "../../svgs/public.svg";
import { ReactComponent as ProtectedSvg } from "../../svgs/protected.svg";
import { ReactComponent as XmarkSvg } from "../../svgs/xmark.svg";
import { ReactComponent as LoadingSvg } from "../../svgs/loading.svg";
import { ReactComponent as SuccessSvg } from "../../svgs/success.svg";
import { ReactComponent as ErrorSvg } from "../../svgs/error.svg";
import { ReactComponent as MapBaseSvg } from "../../svgs/mapbasic.svg";
import { ReactComponent as MapBallTwoSvg } from "../../svgs/mapballtwo.svg";
import { ReactComponent as MapBrickSvg } from "../../svgs/mapbrick.svg";
import { ReactComponent as MapLadderSvg } from "../../svgs/mapladder.svg";
import styled from 'styled-components';

const BaseSvgButton = styled.button.attrs((props) => ({
    type: 'button',
    disabled: props.disabled
}))`
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-user-drag: none;
    user-drag: none;
    -webkit-touch-callout: none;
    background-color: transparent;
    border: 0;
`;

const MapRandomSvg = styled(MapLadderSvg)`
    width:  450px;
    height: 360px;
    margin: 25px;
`;

const MapDefaultSvg = styled(MapBaseSvg) <{ isbigs?: number, isgames?: string }>`
    width: ${(props) => (props.isbigs === 0 ? '450px' : '180px')};
    height: ${(props) => (props.isbigs === 0 ? '360px' : '180px')};
    margin: ${(props) => (props.isbigs === 0 ? '25px' : '10px')};
    border-radius: 10%;
    border: ${(props) => (props.isgames === "0" ? '3px solid #aa00ff;' : '0')};
`;

const MapCustomOneSvg = styled(MapBallTwoSvg) <{ isbigs?: number, isgames?: string }>`
    width: ${(props) => (props.isbigs === 1 ? '450px' : '180px')};
    height: ${(props) => (props.isbigs === 1 ? '360px' : '180px')};
    margin: ${(props) => (props.isbigs === 1 ? '25px' : '10px')};
    border-radius: 10%;
    border: ${(props) => (props.isgames === "1" ? '3px solid #aa00ff;' : '0')};
    
`;

const MapCustomTwoSvg = styled(MapBrickSvg) <{ isbigs?: number, isgames?: string }>`
    width: ${(props) => (props.isbigs === 2 ? '450px' : '180px')};
    height: ${(props) => (props.isbigs === 2 ? '360px' : '180px')};
    margin: ${(props) => (props.isbigs === 2 ? '25px' : '10px')};
    border-radius: 10%;
    border: ${(props) => (props.isgames === "2" ? '3px solid #aa00ff;' : '0')};
`;


const BasaeSuccessSvg = styled(SuccessSvg)`
    fill: #1b5e20;
    width: 50px;
    height: 50px;
    margin: 25px 5px 5px 5px;
`;

const BasaeErrorSvg = styled(ErrorSvg)`
    fill: #dd2c00;
    width: 50px;
    height: 50px;
    margin: 25px 5px 5px 5px;
`;

const BasaeLoadingSvg = styled(LoadingSvg)`
    margin: auto;
    fill: #FFFFFF;
    width: 40px;
    height: 40px;
    margin: 5px;
`;

const BaseXmarkSvg = styled(XmarkSvg) <{ ladders?: string }>`
    margin: auto;
    fill: #D32F2F;
    width: ${(props) => (props.ladders === "que" ? '20px' : '30px')};
    height: ${(props) => (props.ladders === "que" ? '20px' : '30px')};
    margin-top: 5px;
    &:active {
        fill: #EF5350;
    }
`;

const BasaeQuestionSvg = styled(QuestionSvg)`
    margin: auto;
    fill: #B388FF;
    width: 17px;
    height: 17px;
    disabled: true;
`;
const BasePublicSvg = styled(PubllicSvg)`
    margin: auto;
    fill: #B388FF;
    width: 15px;
    height: 15px;
    disabled: true;
`;
const BaseProtectedSvg = styled(ProtectedSvg)`
    margin: auto;
    fill: #B388FF;
    width: 15px;
    height: 15px;
    disabled: true;
`;

const BaseTrophySvg = styled(TrophySvg) <{ ladders?: string, isgames?: string }>`
    margin: auto;
    fill: ${(props) => (props.ladders === 'Gold' ? '#ffd700' : (props.ladders === 'Silver' ? '#c0c0c0' : '#CD7F32'))};
    width: ${(props) => (props.isgames === "ok" ? '100px' : '30px')};
    height: ${(props) => (props.isgames === "ok" ? '100px' : '30px')};
`;

const BaseCameraSvg = styled(CameraSvg)`
    margin: auto;
    fill: #B388FF;
    width: 30px;
    height: 30px;
    disabled: true;
    &:active {
        fill: #7C4DFF;
        width: 28px;
        height: 28px;
    }
`;

const BaseReturnSvg = styled(ReturnSvg)`
    margin-top: 5px;
    margin-right: 10px;
    fill: #ECEFF1;
    width: 30px;
    height: 30px;
    &:active {
        fill: #B0BEC5;
        width: 28px;
        height: 28px;
    }
`;

const BaseMenuSvg = styled(MenuSvg)`
    fill: #ECEFF1;
    width: 40px;
    height: 40px;
    &:active {
        fill: #B0BEC5;
        width: 38px;
        height: 38px;
    }
`;

const BaseChatSvg = styled(ChatingSvg)`
    margin: 0;
    fill: #f5f7ff;
    width: 250px;
    height: 250px;
    &:active {
        fill: #bcc0cf;
        width: 244px;
        height: 244px;
    }
`;

const BaseFriendSvg = styled(FriendSvg)`
    margin: 0;
    fill: #f5f7ff;
    width: 250px;
    height: 250px;
    &:active {
        fill: #bcc0cf;
        width: 244px;
        height: 244px;
    }
`;

const BaseGameSvg = styled(GameSvg)`
    margin: 0;
    fill: #f5f7ff;
    width: 250px;
    height: 250px;
    &:active {
        fill: #bcc0cf;
        width: 244px;
        height: 244px;
    }
`;

interface svgType {
    svgName: string;
    isgames?: string;
    isbigs?: number;
    isDisabled?: boolean;
    ladders?: string;
    onClick?: (e: React.MouseEvent<HTMLButtonElement>) => void;
}

export default function SvgButton(props: svgType) {
    return (
        <BaseSvgButton onClick={props.onClick} disabled={props.isDisabled || false}>
            {props.svgName === "CameraSvg" ? <BaseCameraSvg /> : null}
            {props.svgName === "ReturnSvg" ? <BaseReturnSvg /> : null}
            {props.svgName === "MenuSvg" ? <BaseMenuSvg /> : null}
            {props.svgName === "ChatingSvg" ? <BaseChatSvg /> : null}
            {props.svgName === "FriendSvg" ? <BaseFriendSvg /> : null}
            {props.svgName === "GameSvg" ? <BaseGameSvg /> : null}
            {props.svgName === "QueSvg" ? <BasaeQuestionSvg /> : null}
            {props.svgName === "PublicSvg" ? <BasePublicSvg /> : null}
            {props.svgName === "ProtectSvg" ? <BaseProtectedSvg /> : null}
            {props.svgName === "TrophySvg" ? <BaseTrophySvg ladders={props.ladders || 'Bronze'} isgames={props.isgames} /> : null}
            {props.svgName === "XmarkSvg" ? <BaseXmarkSvg ladders={props.ladders} /> : null}
            {props.svgName === "LoadingSvg" ? <BasaeLoadingSvg /> : null}
            {props.svgName === "SuccessSvg" ? <BasaeSuccessSvg /> : null}
            {props.svgName === "ErrorSvg" ? <BasaeErrorSvg /> : null}
            {props.svgName === "MapBaseSvg" ? <MapDefaultSvg isbigs={props.isbigs} isgames={props.isgames} /> : null}
            {props.svgName === "MapBallTwoSvg" ? <MapCustomOneSvg isbigs={props.isbigs} isgames={props.isgames} /> : null}
            {props.svgName === "MapBrickSvg" ? <MapCustomTwoSvg isbigs={props.isbigs} isgames={props.isgames} /> : null}
            {props.svgName === "MapLadderSvg" ? <MapRandomSvg /> : null}
        </BaseSvgButton>
    );
}