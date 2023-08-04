import { useState, useEffect } from 'react';
import { useSearchParams, useNavigate } from 'react-router-dom';
import * as TwoFactorStyle from '../style/TwoFactorStyle';
import { tfaGetApi } from '../lib/getAxios';
import Tfinput from '../component/other/TfInput';
import TfButton from '../component/other/TfButton';

export default function TwoFactor() {
    const [mail, setMail] = useState<string>("");
    const [certNum, setCertNum] = useState<string>("");
    const [searchParams] = useSearchParams();
    const [loading, setLoading] = useState(false);
    const [restart, setRestart] = useState("null");
    const nabi = useNavigate();

    const getEmail = async () => {
        try {
            const respone = await tfaGetApi.getBindEmail();
            setMail(respone.data.email);
        } catch (e: any) {
            setMail(e.response.data.message);
        }
    }

    useEffect(() => {
        const token = searchParams.get('token');
        const rtoken = searchParams.get('rtoken');
        if (token !== null && rtoken !== null) {
            sessionStorage.setItem('token', token || "none");
            sessionStorage.setItem('rtoken', rtoken || "none");
            window.history.pushState("", "", '/twofactor');
        }
        else {
            const token = sessionStorage.getItem("token") || null;
            const rtoken = sessionStorage.getItem("rtoken") || null;
            if (!token || !rtoken)
                nabi("/");
        }

        getEmail();
        setLoading(true);
    }, [searchParams, nabi])

    return (
        <TwoFactorStyle.TwoFactorContainer>
            {loading ?
                <TwoFactorStyle.TwoFactorSection>
                    <TwoFactorStyle.TwoFactorTitle stringEmail={false}>42Check Mail Verification</TwoFactorStyle.TwoFactorTitle>
                    <TwoFactorStyle.TwoFactorTitle stringEmail={true}>{mail}</TwoFactorStyle.TwoFactorTitle>
                    <Tfinput certNum={certNum} restart={restart} setCertNum={setCertNum} />
                    <TfButton certNum={certNum} setRestart={setRestart} setCertNum={setCertNum} />
                </TwoFactorStyle.TwoFactorSection> : null}
        </TwoFactorStyle.TwoFactorContainer>
    );
}
