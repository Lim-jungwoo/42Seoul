import styled from 'styled-components'

const NotFoundHeader = styled.h1`
    font-size: 2rem;
    color: white;
`;

export default function NotFound() {
    return (
        <NotFoundHeader>해당 웹페이지는 찾을수 없는 페이지 입니다.</NotFoundHeader>
    )
}