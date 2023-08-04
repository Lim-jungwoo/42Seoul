import { useState, useEffect, useContext } from 'react';
import * as ChatRoomStyled from '../../style/ChatRoomStyle'
import { SocketContext, StateModalControllerContext } from '../../lib/socketContext';

interface WhisperInput {
    isWhisper: boolean,
    whisperTarget: string,
}

export default function ChatInput({ isWhisper, whisperTarget }: WhisperInput) {
    const socket = useContext(SocketContext);
    const [textInput, setTextInput] = useState("");
    const [placeholder, setPlaceholder] = useState<string>("Text msg");
    const stateModal = useContext(StateModalControllerContext);

    const onChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        setTextInput(e.target.value.normalize("NFC"));
    }

    const onClick = () => {
        if (!isWhisper)
            socket?.emit("chat", {
                msg: textInput
            }, (resp: any) => {
                if (resp.status) {
                    stateModal?.setOpen(true);
                    stateModal?.setStateType({
                        stateImg: "Error",
                        msg: resp.message,
                    });
                }
            });
        else
            socket?.emit("directChat", {
                msg: textInput,
                nick: whisperTarget,
            }, (resp: any) => {
                if (resp.status) {
                    stateModal?.setOpen(true);
                    stateModal?.setStateType({
                        stateImg: "Error",
                        msg: resp.message,
                    });
                }
            });
        setTextInput("");
    }

    const onKeyPress = (event :React.KeyboardEvent<HTMLInputElement>) => {
        if (event.key === 'Enter')
        {
            onClick();
        }
    }

    const SendBtn = () => {
        return(
            <ChatRoomStyled.SendBtn onClick={onClick}>
                Send
            </ChatRoomStyled.SendBtn>
        )
    }
    useEffect(() => {
        setTextInput("");
        if (isWhisper)
            setPlaceholder("Text msg for " + whisperTarget);
        else
            setPlaceholder("Text msg");
    }, [isWhisper, whisperTarget])

    return (
        <ChatRoomStyled.InputBox>
            <ChatRoomStyled.Input
                placeholder={placeholder}
                isWhisper={isWhisper}
                type="text"
                value={textInput}
                onChange={onChange}
                onKeyPress={onKeyPress}
                maxLength={1000}
            />
            <SendBtn/>
        </ChatRoomStyled.InputBox>
    )
}