import { useState, useEffect, useContext, useRef, useCallback } from 'react';
import * as ChatRoomStyled from '../../style/ChatRoomStyle'
import mainImage from '../../images/mainImage.png';
import { SocketContext, RoomInfoChat, SocketValidate,StateModalControllerContext } from '../../lib/socketContext';
import { useNavigate } from 'react-router-dom';


const ForOther = (prop: any) => {
    return (
        <ChatRoomStyled.ForOther>
            <ChatRoomStyled.ChatImage src={prop.avatar || mainImage} />
            <ChatRoomStyled.MsgBoxForOther>{prop.nick}: {prop.msg}</ChatRoomStyled.MsgBoxForOther>
        </ChatRoomStyled.ForOther>
    )
}

const ForWhisperOther = (prop: any) => {
    return (
        <ChatRoomStyled.ForOther>
            <ChatRoomStyled.ChatImage src={prop.avatar || mainImage} />
            <ChatRoomStyled.MsgBoxForWhisperOther>{prop.nick}: {prop.msg}</ChatRoomStyled.MsgBoxForWhisperOther>
        </ChatRoomStyled.ForOther>
    )
}

const ForWhisperMe = (prop: any) => {
    return (
        <ChatRoomStyled.ForMe>
            <ChatRoomStyled.MsgBoxForWhisperMe>{prop.msg}</ChatRoomStyled.MsgBoxForWhisperMe>
            <ChatRoomStyled.ChatImage src={prop.avatar || mainImage} />
        </ChatRoomStyled.ForMe>
    )
}

const ForMe = (prop: any) => {
    return (
        <ChatRoomStyled.ForMe>
            <ChatRoomStyled.MsgBoxForMe>{prop.msg}</ChatRoomStyled.MsgBoxForMe>
            <ChatRoomStyled.ChatImage src={prop.avatar || mainImage} />
        </ChatRoomStyled.ForMe>
    )
}

const ForBattle = (prop: any) => {
    const socket = useContext(SocketContext);
    const navigator = useNavigate();
    const stateModal = useContext(StateModalControllerContext);

    const onClickAccept = () => {
        socket?.emit("battleAccept", {
            roomId: prop.roomId,
            accept: true,
        }, (resp: any) => {
            if (resp.status) {
                stateModal?.setOpen(true);
                stateModal?.setStateType({
                    stateImg: "Error",
                    msg: resp.message,
                });
            }
        });
    }

    const onClickReject = () => {
        socket?.emit("battleAccept", {
            roomId: prop.roomId,
            accept: false,
        }, (resp: any) => {
            if (resp.status) {
                stateModal?.setOpen(true);
                stateModal?.setStateType({
                    stateImg: "Error",
                    msg: resp.message,
                });
            }
        });
    }

    const onClickWat = () => {
        socket?.disconnect();
        navigator(`/game/gameroom/${prop.roomId}?maptype=map_0&usertype=spectator`);
    }

    return (
        <ChatRoomStyled.ForBattle>
            <ChatRoomStyled.BoxForVersus>
                <ChatRoomStyled.ChatImage src={prop.user1?.avatar || mainImage} />
                <ChatRoomStyled.NickForVersus>{prop.user1?.nick}</ChatRoomStyled.NickForVersus>
                VS
                <ChatRoomStyled.NickForVersus>{prop.user2?.nick}</ChatRoomStyled.NickForVersus>
                <ChatRoomStyled.ChatImage src={prop.user2?.avatar || mainImage} />
            </ChatRoomStyled.BoxForVersus>
            <ChatRoomStyled.BoxForGame>
                {
                    prop.state === "pending" ?
                        (prop.user2?.isMe ?
                            <>
                                <ChatRoomStyled.ButtonForVersus onClick={onClickAccept}>⭕</ChatRoomStyled.ButtonForVersus>
                                <ChatRoomStyled.ButtonForVersus onClick={onClickReject}>❌</ChatRoomStyled.ButtonForVersus>
                            </>
                            : <ChatRoomStyled.ButtonForVersus>⏸️</ChatRoomStyled.ButtonForVersus>
                        )
                        : (prop.state === "playing" ?
                            <ChatRoomStyled.ButtonForVersus onClick={onClickWat}>👀</ChatRoomStyled.ButtonForVersus>
                            : (prop.state === "finished" ?
                                <ChatRoomStyled.ButtonForVersus>⛳</ChatRoomStyled.ButtonForVersus>
                                : <ChatRoomStyled.ButtonForVersus>⏸️</ChatRoomStyled.ButtonForVersus>
                            )
                        )
                }
            </ChatRoomStyled.BoxForGame>
        </ChatRoomStyled.ForBattle>
    )
}

export default function ChatBox() {
    const roomInfo = useContext(RoomInfoChat);
    const socket = useContext(SocketContext);
    const [msgBox, setMsgBox] = useState<any[]>([]);
    const msgBoxRef = useRef(msgBox);
    const navigator = useNavigate();
    const socketVal = useContext(SocketValidate);
    const scrollRef = useRef<HTMLDivElement>(null);

    const emitChatList = useCallback(() => {
        if (socket)
            socket?.emit("chatList", (resp: any) => {
                let tmp = msgBoxRef.current.concat(resp);
                setMsgBox(tmp);
            });
    }, [socket, msgBoxRef])

    useEffect(() => {
        if (socketVal)
            emitChatList();
    }, [socketVal, emitChatList])

    useEffect(() => {
        socket?.on("chat", (data: any) => {
            setMsgBox(oldMsgBox => [...oldMsgBox, data]);
        })
        socket?.on("directChat", (data: any) => {
            data.dm = true;
            setMsgBox(oldMsgBox => [...oldMsgBox, data]);
        })
        socket?.on("battleAlert", (data: any) => {
            setMsgBox(oldMsgBox => [...oldMsgBox, data]);
        })
        socket?.on("battleUpdated", (data: any) => {
            let tmp = new Array<any>();
            msgBoxRef.current.forEach((msg, idx) => {
                tmp.push(msg);
                if (msg.roomId === data.roomId) {
                    tmp[idx].state = data.state;
                    msg.roomId = data.newRoomId;
                }
            })
            setMsgBox(tmp);
        })
        socket?.on("gameStart", (data: any) => {
            socket.disconnect();
            navigator(`/game/gameroom/${data.roomId}?maptype=map_0&usertype=player`);
        })
    }, [socket, navigator])

    useEffect(() => {
        msgBoxRef.current = msgBox;
        scrollRef.current!.scrollTop = scrollRef.current!.scrollHeight;
    }, [msgBox, scrollRef])

    const Welcome = () => {
        return (
            <ChatRoomStyled.Welcome>
                <ChatRoomStyled.BoxForWelcom>
                    Welcome to Channel number : {roomInfo?.id}
                </ChatRoomStyled.BoxForWelcom>
            </ChatRoomStyled.Welcome>
        )
    }

    return (
        <ChatRoomStyled.ChatBox ref={scrollRef}>
            <Welcome />
            {
                msgBox.map((item, index) => (
                    item.status === undefined ?
                        (item.msg !== undefined ?
                            (item.dm !== undefined ?
                                (
                                    item.isMe ?
                                        <ForWhisperMe key={index} avatar={item.avatar} nick={item.nick} msg={item.msg} />
                                        : <ForWhisperOther key={index} avatar={item.avatar} nick={item.nick} msg={item.msg} />
                                ) : item.isMe ?
                                    <ForMe key={index} avatar={item.avatar} nick={item.nick} msg={item.msg} />
                                    : <ForOther key={index} avatar={item.avatar} nick={item.nick} msg={item.msg} />
                            )
                            : <ForBattle key={index}
                                user1={item.user1}
                                user2={item.user2}
                                state={item.state}
                                roomId={item.roomId}
                            />
                        ) : null
                ))
            }
        </ChatRoomStyled.ChatBox>
    )
}