import { customAxios } from './customAxios';

interface emailType {
    data: {
        email: string;
    };
}

export const tfaGetApi = {
    getBindEmail: () => customAxios().get<any, emailType>('auth/tfa_email'),
}

export const logOutAPi = {
    getLogOut: () => customAxios().get('auth/logout'),
}

interface userInfo {
    data: {
        nickname: string;
        username: string;
        email: string;
        avatar: string;
        status: string;
        ladderrating: string;
        ladderscore: number;
        tfa: boolean;
    }
}

export const pfGetApi = {
    getLeftInput: () => customAxios().get<any, userInfo>('user/get_myself'),
}

export const historyGetApi = {
    getRightHistory: (currentpage: number, nextpage: number, firsthistorypk: number, lasthistorypk: number, type: string) => customAxios().post('user/get_five_history', {
        currentpage: currentpage,
        nextpage: nextpage,
        firsthistorypk: firsthistorypk,
        lasthistorypk: lasthistorypk,
        type: type
    })
}