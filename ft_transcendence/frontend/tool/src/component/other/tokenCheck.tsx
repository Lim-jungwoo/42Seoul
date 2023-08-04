export const tokenCheck = () => {
    const token = sessionStorage.getItem('token');
    const rtoken = sessionStorage.getItem('rtoken');
    if (!token || !rtoken)
        window.location.href = process.env.REACT_APP_HOME || ""; 
    return true;
}