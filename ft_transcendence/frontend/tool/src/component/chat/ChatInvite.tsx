import { useState, useContext } from 'react';
import * as ChatRoomStyled from '../../style/ChatRoomStyle'
import { SocketContext, StateModalControllerContext } from '../../lib/socketContext';

export default function ChatInvite() {
    const [textInput, setTextInput] = useState("");
    const socket = useContext(SocketContext);
    const stateModal = useContext(StateModalControllerContext);
    const onChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        e.target.value = e.target.value.replace(/[^A-Za-z0-9]/ig, '');
        setTextInput(e.target.value);
    }

    const onClick = () => {
        socket?.emit("roomInvite", {
            nick: textInput
        }, (resp: any) => {
            if (resp.status)
            {
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

    const InviteBtn = () => {
        return (
            <ChatRoomStyled.InviteBtn onClick={onClick}>
                Invite
            </ChatRoomStyled.InviteBtn>
        )   
    }

    return (
        <ChatRoomStyled.InviteBox>
            <ChatRoomStyled.InviteInput
                placeholder={"Enter nickname"}
                type="text"
                value={textInput}
                onChange={onChange}
                onKeyPress={onKeyPress}
            />
            <InviteBtn/>
        </ChatRoomStyled.InviteBox>
    )
}