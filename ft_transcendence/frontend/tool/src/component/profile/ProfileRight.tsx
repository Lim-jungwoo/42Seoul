import { useState } from 'react';
import styled from 'styled-components';
import NabigationBar from '../other/NabigationBar';
import TableScore from './TableScore';
import Paginnation from '../other/Pagination';

const ProfileMain = styled.main`
    display: grid;
    grid-template-columns: 1fr;
    grid-template-rows: 44px 1fr 43px;
`;

export default function ProfileRight() {
    const [nabiNum, setNabiNum] = useState(0);
    const [beforeNabiNum, setBeforeNabiNum] = useState(0);
    const [selectNum, setSelectNum] = useState(1);
    const [beforeSelectNum, setBeforeSelectNum] = useState(1);
    const [allPageNum, setAllPageNum] = useState(1);

    return (
        <ProfileMain>
            <NabigationBar isListHeader='전체,일반,레더' setBeforeNabiNum={setBeforeNabiNum} setNabiNum={setNabiNum}></NabigationBar>
            <TableScore setSelectNum={setSelectNum} setBeforeNabiNum={setBeforeNabiNum} setBeforeSelectNum={setBeforeSelectNum} nabiNum={nabiNum} beforeNabiNum={beforeNabiNum} selectNum={selectNum} beforeSelectNum={beforeSelectNum} setAllPageNum={setAllPageNum}></TableScore>
            <Paginnation allPageNum={allPageNum} selectNum={selectNum} setSelectNum={setSelectNum} setBeforeSelectNum={setBeforeSelectNum} />
        </ProfileMain>
    );
}