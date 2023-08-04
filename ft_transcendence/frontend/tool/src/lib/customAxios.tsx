import axios, { AxiosInstance } from 'axios';

export const customAxios = () => {
    const token = sessionStorage.getItem('token');
    const rtoken = sessionStorage.getItem('rtoken');
    const baseAxios: AxiosInstance = axios.create({
        baseURL: process.env.REACT_APP_API_URL,
        headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${token}`,
        },
        withCredentials: true,
    })

    const maxRetry = 2;

    const errorHandler = async (error: any) => {
        error.config.retryCount = error.config.retryCount ?? 0;
        const shoudRetry = error.config.retryCount < maxRetry;
        if (error.response && error.response.status === 401) {

            const res = await axios({
                method: 'get',
                url: process.env.REACT_APP_API_URL + '/auth/refresh',
                headers: {
                    'Authorization': `Bearer ${rtoken}`,
                }
            });
            if (res.status === 200 && shoudRetry) {
                sessionStorage.removeItem("token");
                sessionStorage.setItem("token", res.data.accessToken);
                error.config.retryCount += 1;
                error.config.headers = {
                    'Authorization': `Bearer ${res.data.accessToken}`,
                }
                return baseAxios.request(error.config);
            }
        }
        const errorMsg = (error.message === "Network Error") ? {
            response: {
                status: 500,
                data: { message: "Network Error" }
            }
        } : { response: { 
                data: error.response.data,
                status: error.response.status,
            }};
        return Promise.reject(errorMsg);
    }
    baseAxios.interceptors.response.use(
        (response: any) => {
            return response;
        },
        error => errorHandler({ ...error })
    );

    return baseAxios;
}