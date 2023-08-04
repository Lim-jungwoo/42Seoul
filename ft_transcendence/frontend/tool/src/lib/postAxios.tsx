import { customAxios } from './customAxios';


interface reEmailSendType {
    data: {
        token: string,
        rtoken: string
    },
}

export const tfaPostApi = {
    postOtpCheck: (otpNum: string) => customAxios().patch<any, reEmailSendType>('auth/tfa_login', {
        otp: otpNum
    }),
    postOtpReSend: () => customAxios().post('auth/tfa_gen', {}),
}

export const pfPostApi = {
    postLeftInput: (nickname: string) => customAxios().post('user/get_user', {
        nickname: nickname
    }),

    patchLeftUpdate: (nickname: string, avatar: string, isTfa: boolean) => customAxios().patch('user/update_user', {
        nickname: nickname,
        avatar: avatar,
        tfa: isTfa,
    })
}

export const friendPostApi = {
    postFiveUser: (currentpage: number, nextpage: number, firstusername: string, lastusername: string) => customAxios().post('user/get_five_user', {
        currentpage: currentpage,
        nextpage: nextpage,
        firstusername: firstusername,
        lastusername: lastusername,
    }),
    postFiveFriend: (currentpage: number, nextpage: number, firstusername: string, lastusername: string) => customAxios().post('user/get_five_friend', {
        currentpage: currentpage,
        nextpage: nextpage,
        firstusername: firstusername,
        lastusername: lastusername,
    }),
    postFiveRequest: (currentpage: number, nextpage: number, firstusername: string, lastusername: string) => customAxios().post('user/get_five_friend_request', {
        currentpage: currentpage,
        nextpage: nextpage,
        firstusername: firstusername,
        lastusername: lastusername,
    }),
    postFriendSend: (username: string) => customAxios().post('user/send_friend_request', {
        username: username,
    }),
    postFriendAccept: (username: string) => customAxios().post('user/accept_friend', {
        username: username,
    }),
    postFriendDel: (username: string) => customAxios().post('user/delete_friend', {
        username: username,
    }),
    postFriendDecline: (username: string) => customAxios().post('user/decline_friend', {
        username: username,
    }),
    postUserBlock: (username: string) => customAxios().post('user/block_user', {
        username: username,
    }),
}

export const historyPostApi = {
    getRightHistory: (nickname: string, currentpage: number, nextpage: number, firsthistorypk: number, lasthistorypk: number, type: string) => customAxios().post('user/get_user_five_history',
        {
            nickname: nickname,
            currentpage: currentpage,
            nextpage: nextpage,
            firsthistorypk: firsthistorypk,
            lasthistorypk: lasthistorypk,
            type: type
        })
}