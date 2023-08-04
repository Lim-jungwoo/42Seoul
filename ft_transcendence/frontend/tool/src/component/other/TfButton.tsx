import React from 'react'
import { useNavigate } from 'react-router-dom';
import styled from 'styled-components'
import { tfaPostApi } from '../../lib/postAxios';

const TwoFactorButton = styled.button`
    background-color: transparent;
    width: 300px;
    font-size: 2rem;
    border: 2px solid white;
    color: #fafafa;
    padding: 1rem;
    border-radius: 24px;

    &:hover {
        background-color: rgba(247, 242, 242, 0.2)
    }
`;

const TwoFactorReSend = styled.button`
    display: block;
    background-color: transparent;
    font-size: 1rem;
    border: 0px;
    color: #fafafa;
    margin-left: 40%;
    padding: 1rem;
    &:hover {
        color: rgba(176, 190, 197, 0.5);
    }
`;

interface tfButtonType {
    certNum: string,
    setRestart: React.Dispatch<React.SetStateAction<string>>,
    setCertNum: React.Dispatch<React.SetStateAction<string>>,
}

interface reEmailSendType {
    data: {
        token: string,
        rtoken: string
    },
}

export default function TfButton({ certNum, setRestart, setCertNum }: tfButtonType) {
    const navi = useNavigate();

    const otpCheck = (res: reEmailSendType) => {
        if (!res.data) return;
        navi({
            pathname: '/main',
            search: `token=${res.data.token}&rtoken=${res.data.rtoken}`,
        })
    }

    const certNumClick = async () => {
        try {
            const res = await tfaPostApi.postOtpCheck(certNum);
            otpCheck(res);
        } catch (e: any) {
            if (e.response.status === 302) setRestart('recheck');
            else if (e.response.status === 400) setRestart('recheck');
            else if (e.response.status === 403) setRestart('request');
            else if (e.response.status === 500) setRestart('dbinput');

        }
        setCertNum("");
    }

    const reSendClick = async () => {
        try {
            const res = await tfaPostApi.postOtpReSend();
            if (res.status === 201) setRestart("remail");
        } catch (e: any) {
            if (e.response.status === 403) setRestart('remail');
        }
        setCertNum("");
    }
    return (
        <div>
            <TwoFactorReSend onClick={reSendClick}>인증코드 재발송</TwoFactorReSend>
            <TwoFactorButton onClick={certNumClick}>Auth</TwoFactorButton>
        </div>
    )
}