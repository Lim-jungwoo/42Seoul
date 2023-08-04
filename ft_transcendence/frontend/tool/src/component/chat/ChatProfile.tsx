import { useState, useEffect, useContext, useRef } from 'react';
import * as ChatRoomStyled from '../../style/ChatRoomStyle'
import mainImage from '../../images/mainImage.png';
import {SocketContext, EventInfo, ModalControllerContext, SocketValidate, RoomInfoChat, StateModalControllerContext} from '../../lib/socketContext';

const ProfileOne = (prop :any) => {
    const [isOpen, setIsOpen] = useState<boolean>(false);
    const socket = useContext(SocketContext);
    const eventInfo = useContext(EventInfo);
    const modalController = useContext(ModalControllerContext);
    const roomInfo = useContext(RoomInfoChat);
    const stateModal = useContext(StateModalControllerContext);

    const onClick = () => {
        setIsOpen(!isOpen);
    }
    const OnClickProfile = () => {
        eventInfo?.setEvent("Profile");
        eventInfo?.setTarget(prop.nick);
        modalController?.setOpen(true);
        modalController?.setModalNum(6);
        setIsOpen(old => !old);
    }
    const OnClickGameInvite = () => {
        socket?.emit("gameInvite", {
            nick: prop.nick,
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
        setIsOpen(old => !old);
    }
    const OnClickMute = () => {
        socket?.emit("mute", {
            nick: prop.nick,
        }, (resp: any) => {
            if (resp.status) {
                stateModal?.setOpen(true);
                stateModal?.setStateType({
                    stateImg: "Error",
                    msg: resp.message,
                });
            }
        });
        setIsOpen(old => !old);
    }
    const OnClickBan = () => {
        socket?.emit("ban", {
            nick: prop.nick,
        }, (resp: any) => {
            if (resp.status) {
                stateModal?.setOpen(true);
                stateModal?.setStateType({
                    stateImg: "Error",
                    msg: resp.message,
                });
            }
        });
        setIsOpen(old => !old);
    }
    const OnClickBlock = () => {
        socket?.emit("block", {
            nick: prop.nick,
        }, (resp: any) => {
            if (resp.status) {
                stateModal?.setOpen(true);
                stateModal?.setStateType({
                    stateImg: "Error",
                    msg: resp.message,
                });
            }
        });
        setIsOpen(old => !old);
    }
    const OnClickSetAdmin = () => {
        setIsOpen(old => !old);
        socket?.emit("setAdmin", {
            nick: prop.nick,
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

    const OnClickWhisper = (e: React.MouseEvent<HTMLButtonElement>) => {
        prop.setWhisper(!(prop.isWhisper));
        if (!prop.isWhisper)
            prop.setWhisperTarget(prop.nick);
        else
            prop.setWhisperTarget("");
    }

    const OnClickSetPassword = (e: React.MouseEvent<HTMLButtonElement>) => {
        modalController?.setOpen(true);
        modalController?.setModalNum(7);
    }

    const OnClickKick = (e: React.MouseEvent<HTMLButtonElement>) => {
        socket?.emit("kick", {
            nick: prop.nick,
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
    
    const DropBox = () => {
        if (!prop.isMe && prop.amAdmin && !prop.isOwner)
        {
            return(
                <>
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickProfile}>Profile</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickGameInvite}>GameInvite</ChatRoomStyled.ProfileDropBox>
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickBlock}>Block</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickMute}>Mute</ChatRoomStyled.ProfileDropBox>
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickKick}>Kick</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickBan}>Ban</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickSetAdmin}>SetAdmin</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickWhisper}>Whisper</ChatRoomStyled.ProfileDropBox> 
                </>
            )
        }
        else if (prop.isMe && prop.isOwner)
        {
            if (roomInfo?.type === 'private')
                return (
                    <>
                        <ChatRoomStyled.ProfileDropBox onClick={OnClickProfile}>Profile</ChatRoomStyled.ProfileDropBox> 
                    </>
                )
            return (
                <>
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickProfile}>Profile</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickSetPassword}>SetPassword</ChatRoomStyled.ProfileDropBox> 
                </>
            )
        }
        else if (prop.isMe)
        {
            return (
                <>
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickProfile}>Profile</ChatRoomStyled.ProfileDropBox> 
                </>
            )
        }
        else
        {
            return (
                <>
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickProfile}>Profile</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickGameInvite}>GameInvite</ChatRoomStyled.ProfileDropBox>
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickBlock}>Block</ChatRoomStyled.ProfileDropBox> 
                    <ChatRoomStyled.ProfileDropBox onClick={OnClickWhisper}>Whisper</ChatRoomStyled.ProfileDropBox>
                </>
            )
        }
    }

    return (
        <>
            <ChatRoomStyled.ProfileOne onClick={onClick}>
                <ChatRoomStyled.ChatImage src={prop.avatar || mainImage}/>
                <ChatRoomStyled.NickForProfile>{prop.nick}</ChatRoomStyled.NickForProfile>
            </ChatRoomStyled.ProfileOne>
            {isOpen ? DropBox() : null}
        </>
    )
}

interface Whisper {
    isWhisper: boolean,
    setWhisper: React.Dispatch<React.SetStateAction<boolean>>,
    setWhisperTarget: React.Dispatch<React.SetStateAction<string>>,
    isModal: boolean,
    setModal: React.Dispatch<React.SetStateAction<boolean>>,
}

export default function ChatProfile({ isWhisper, setWhisper, setWhisperTarget, isModal, setModal }: Whisper) {
    const socket = useContext(SocketContext);
    const [userBox, setUserBox] = useState<any[]>([]);
    const userBoxRef = useRef(userBox);
    const [amAdmin, setAdmin] = useState<boolean>(false);
    const socketVal = useContext(SocketValidate);

    useEffect(() => {
        if(socketVal && socket)
            socket?.emit("userList", (resp: any[]) => {
                setUserBox(resp);
            });
    }, [socketVal, socket])

    useEffect(() => {
        if (socket)
        {
            socket.on("userJoin", (data: any) => {
                setUserBox(oldUserBox => [...oldUserBox, data]); 
            })
            socket.on("userLeave", (data: any) => {
                let tmp = new Array<any>();
                userBoxRef.current.forEach((user, idx) => {
                    if (user.nick !== data.nick)
                        tmp.push(user);
                })
                setUserBox(tmp);
            })
            socket.on("setAdmin", () => {
                setAdmin(true);
            });
        }
    }, [socket])

    useEffect(() => {
        userBoxRef.current = userBox;
        userBox.forEach((user, idx) => {
            if (user.isMe && user.isAdmin)
                setAdmin(true);
        });
    }, [userBox])

    return (
        <ChatRoomStyled.ProfileBox>
            {userBox.map((item, index) => (
                <ProfileOne key={index}
                    avatar={item.avatar}
                    nick={item.nick}
                    isMe={item.isMe}
                    isOwner={item.isOwner}
                    amAdmin={amAdmin}
                    isWhisper={isWhisper}
                    setWhisper={setWhisper}
                    setWhisperTarget={setWhisperTarget}
                    isModal={isModal}
                    setModal={setModal}
                />
            ))}
        </ChatRoomStyled.ProfileBox>
    )
}