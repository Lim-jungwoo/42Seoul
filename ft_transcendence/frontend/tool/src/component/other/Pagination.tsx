import styled from 'styled-components';
import React, { useState, useEffect } from 'react';

const PaginDiv = styled.div`
    width: 100%;
    height: 100%;
    text-align: center;
    display: block;
    justify-content: center;
`
const PaginNum = styled.button.attrs((props) => ({
    type: 'button',
    disabled: props.disabled
})) <{ isClickNum?: boolean, isLastNum: boolean, isSelectNum: number }>`
    color: ${(props) => props.isLastNum ? 'white' : '#909099'};
    height: 100%;
    font-size: 1rem;
    background-color: ${(props) => props.isClickNum ? '#6200EA' : 'transparent'};
    border-radius: ${(props) => props.isClickNum ? '5px' : '0'};
    border: 0;
    padding: ${(props) => props.isSelectNum > 6 ? '0 13px' : '0 16px'};
    text-decoration: none;
    &:active {
        background-color: #6200EA;
        border-radius: 5px;
    }
    &:hover:not(&:active) {
        background-color: #9E9E9E;
        border-radius: 5px;
    }
`

interface pageType {
    allPageNum: number;
    selectNum: number;
    setSelectNum: React.Dispatch<React.SetStateAction<number>>
    setBeforeSelectNum: React.Dispatch<React.SetStateAction<number>>
}

export default function Paginnation({ allPageNum, selectNum, setSelectNum, setBeforeSelectNum }: pageType) {
    const [firstNum, setFirstNum] = useState<number>(1);
    const [lastNum, setlastNum] = useState<number>(6);

    const pageCheckNum = (e: React.MouseEvent) => {
        const displayPage = (e.target as HTMLButtonElement).innerText;
        if (selectNum > 1 && displayPage === '«') {
            if (selectNum === firstNum && firstNum !== 1) {
                setFirstNum((prev) => prev - 1);
                setlastNum((prev) => prev - 1);
            }
            setBeforeSelectNum(selectNum);
            setSelectNum((prev) => prev - 1);
        } else if (displayPage === '»' && selectNum + 1 <= allPageNum) {
            if (selectNum === lastNum && lastNum < allPageNum) {
                setFirstNum((prev) => prev + 1);
                setlastNum((prev) => prev + 1);
            }
            setBeforeSelectNum(selectNum);
            setSelectNum((prev) => prev + 1);
        } else if (!(displayPage === '«' || displayPage === '»')) {
            setBeforeSelectNum(selectNum);
            setSelectNum(parseInt(displayPage));
        }
    }
    useEffect(() => {
        if (selectNum === 1 && firstNum > 1) {
            setFirstNum(1);
            setlastNum(6);
        }
    }, [selectNum, firstNum])

    return (
        <PaginDiv>
            <PaginNum onClick={pageCheckNum} disabled={false} isSelectNum={firstNum} isLastNum={true}>&laquo;</PaginNum>
            <PaginNum onClick={pageCheckNum}
                disabled={!(allPageNum >= firstNum)}
                isSelectNum={firstNum}
                isClickNum={allPageNum >= firstNum && selectNum === firstNum}
                isLastNum={allPageNum >= firstNum}>{firstNum}</PaginNum>
            <PaginNum onClick={pageCheckNum}
                disabled={!(allPageNum >= firstNum + 1)}
                isSelectNum={firstNum}
                isClickNum={allPageNum >= firstNum + 1 && selectNum === firstNum + 1}
                isLastNum={allPageNum >= firstNum + 1}>{firstNum + 1}</PaginNum>
            <PaginNum onClick={pageCheckNum}
                disabled={!(allPageNum >= firstNum + 2)}
                isSelectNum={firstNum}
                isClickNum={allPageNum >= firstNum + 2 && selectNum === firstNum + 2}
                isLastNum={allPageNum >= firstNum + 2}>{firstNum + 2}</PaginNum>
            <PaginNum onClick={pageCheckNum}
                disabled={!(allPageNum >= firstNum + 3)}
                isSelectNum={firstNum}
                isClickNum={allPageNum >= firstNum + 3 && selectNum === firstNum + 3}
                isLastNum={allPageNum >= firstNum + 3}>{firstNum + 3}</PaginNum>
            <PaginNum onClick={pageCheckNum}
                disabled={!(allPageNum >= firstNum + 4)}
                isSelectNum={firstNum}
                isClickNum={allPageNum >= firstNum + 4 && selectNum === firstNum + 4}
                isLastNum={allPageNum >= firstNum + 4}>{firstNum + 4}</PaginNum>
            <PaginNum onClick={pageCheckNum}
                disabled={!(allPageNum >= lastNum)}
                isSelectNum={firstNum}
                isClickNum={allPageNum >= lastNum && selectNum === lastNum}
                isLastNum={allPageNum >= lastNum}>{lastNum}</PaginNum>
            <PaginNum onClick={pageCheckNum} disabled={false} isSelectNum={firstNum} isLastNum={true}>&raquo;</PaginNum>
        </PaginDiv>
    );
}