import { useEffect } from 'react';
import * as HomeStyle from '../style/HomeStyle';



export default function Home() {
    useEffect(() => {
        const token = sessionStorage.getItem('token');
        const rtoken = sessionStorage.getItem('rtoken');
        if (token || rtoken) {
            sessionStorage.removeItem('token');
            sessionStorage.removeItem('rtoken');
        }
    }, [])

    return (
        <HomeStyle.HomeContainer>
            <HomeStyle.HomeSection>
                <HomeStyle.HomeTitle>42FT_TRANSCENDENCE</HomeStyle.HomeTitle>
                <HomeStyle.HomeButton onClick={() => window.location.href = (process.env.REACT_APP_LOGIN_URL || "")}>42 API LOGIN</HomeStyle.HomeButton>
            </HomeStyle.HomeSection>
        </HomeStyle.HomeContainer>
    )
}