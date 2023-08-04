import { useEffect, useState, useRef, useCallback } from 'react';
import styled, { css } from 'styled-components';
import { historyGetApi } from '../../lib/getAxios';
import StateModal from '../modal/StateModal';

const StyleTr = styled.tr`
    border: 1px solid black;
`;

const StyleTd = styled.td< { isHeader: string, isVisble?: boolean } >`
    padding: 10px;
    ${(props) => props.isVisble === true ? css`
    display: none;
    ` : css``}
    color: ${(props) => (props.isHeader === 'header' ? '#6200EA' : (props.isHeader === 'win' ? '#C62828' : (props.isHeader === 'lose' ? '#1976D2' : '#909099')))};
    background-color: ${(props) => (props.isHeader === 'header' ? '#B388FF' : '#455A64')};
    vertical-align: middle;
`;

const StyleTable = styled.table< { trSum: string } >`
    width: 100%;
    margin: 0;
    max-height: ${(props) => props.trSum};
    margin-top: 10px;
    padding: 0;
    cursor: default;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
    text-align: center;
`;


interface tableHeader {
    name: string;
}

interface tableBody {
    historypk: string,
    result: string,
    scoreresult: string,
    type: string,
    yournickname: string,
};

interface tableScoreType {
    selectNum: number;
    setSelectNum: React.Dispatch<React.SetStateAction<number>>;
    beforeSelectNum: number;
    setBeforeSelectNum: React.Dispatch<React.SetStateAction<number>>;
    nabiNum: number;
    beforeNabiNum: number;
    setBeforeNabiNum: React.Dispatch<React.SetStateAction<number>>;
    setAllPageNum: React.Dispatch<React.SetStateAction<number>>;
}

const TABLE_HEADER: tableHeader[] = [
    { name: '경기' },
    { name: '결과' },
    { name: '스코어' },
    { name: '상대' },
];

interface stateType {
    stateImg: string;
    msg: string;
}

export default function TableScore({ selectNum, setSelectNum, beforeSelectNum, setBeforeSelectNum, nabiNum, beforeNabiNum, setBeforeNabiNum, setAllPageNum }: tableScoreType) {
    const tbodyRef = useRef<HTMLTableSectionElement | null>(null);
    const [tableList, setTableList] = useState<Array<tableBody>>([]);
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })

    const getHistoryAll = useCallback(
        async (beforNums: number, nums: number, firstHistory: number, lastHistory: number) => {
            try {
                if (nabiNum !== 0) return;
                if (firstHistory === 0 && lastHistory === 0) {
                    setBeforeSelectNum(1);
                    setSelectNum(1);
                }
                const res = await historyGetApi.getRightHistory(beforNums, nums, firstHistory, lastHistory, "all");
                setTableList(res.data[0]);
                const totals = (parseInt(res.data[1].total) % 15 !== 0 || Math.floor(parseInt(res.data[1].total) / 15) === 0 ? Math.floor(parseInt(res.data[1].total) / 15) + 1
                    : Math.floor(parseInt(res.data[1].total) / 15));
                setAllPageNum(totals);
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message });
            }

        }, [nabiNum, setAllPageNum, setSelectNum, setBeforeSelectNum]);

    const getHistoryNomal = useCallback(
        async (beforNums: number, nums: number, firstHistory: number, lastHistory: number) => {
            try {
                if (nabiNum !== 1) return;
                if (firstHistory === 0 && lastHistory === 0) {
                    setBeforeSelectNum(1);
                    setSelectNum(1);
                }
                const res = await historyGetApi.getRightHistory(beforNums, nums, firstHistory, lastHistory, "normal");
                setTableList(res.data[0]);
                const totals = (parseInt(res.data[1].total) % 15 !== 0 || Math.floor(parseInt(res.data[1].total) / 15) === 0 ? Math.floor(parseInt(res.data[1].total) / 15) + 1
                    : Math.floor(parseInt(res.data[1].total) / 15));
                setAllPageNum(totals);
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message });
            }

        }, [nabiNum, setAllPageNum, setSelectNum, setBeforeSelectNum]);

    const getHistoryLadder = useCallback(
        async (beforNums: number, nums: number, firstHistory: number, lastHistory: number) => {
            try {
                if (nabiNum !== 2) return;
                if (firstHistory === 0 && lastHistory === 0) {
                    setBeforeSelectNum(1);
                    setSelectNum(1);
                }
                const res = await historyGetApi.getRightHistory(beforNums, nums, firstHistory, lastHistory, "ladder");
                setTableList(res.data[0]);
                const totals = (parseInt(res.data[1].total) % 15 !== 0 || Math.floor(parseInt(res.data[1].total) / 15) === 0 ? Math.floor(parseInt(res.data[1].total) / 15) + 1
                    : Math.floor(parseInt(res.data[1].total) / 15));
                setAllPageNum(totals);
            } catch (e: any) {
                setModalOpen(true);
                setStateData({ stateImg: "Error", msg: e.response.data.message });
            }

        }, [nabiNum, setAllPageNum, setSelectNum, setBeforeSelectNum]);


    useEffect(() => {
        if (nabiNum === 0) getHistoryAll(1, 1, 0, 0);
        if (nabiNum === 1) getHistoryNomal(1, 1, 0, 0);
        if (nabiNum === 2) getHistoryLadder(1, 1, 0, 0);
    }, [nabiNum, getHistoryAll, getHistoryNomal, getHistoryLadder])

    useEffect(() => {
        const firstHistoryPk = parseInt(tbodyRef.current?.firstChild?.childNodes[0]?.textContent || "0");
        const LastHistoryPk = parseInt(tbodyRef.current?.lastChild?.childNodes[0]?.textContent || "0");
        if (beforeNabiNum !== nabiNum) {
            setBeforeNabiNum(nabiNum);
            return;
        }
        if (beforeSelectNum !== selectNum) {
            if (nabiNum === 0) getHistoryAll(beforeSelectNum, selectNum, firstHistoryPk, LastHistoryPk);
            if (nabiNum === 1) getHistoryNomal(beforeSelectNum, selectNum, firstHistoryPk, LastHistoryPk);
            if (nabiNum === 2) getHistoryLadder(beforeSelectNum, selectNum, firstHistoryPk, LastHistoryPk);
        }
    }, [selectNum, beforeSelectNum, beforeNabiNum, setBeforeNabiNum, nabiNum, getHistoryAll, getHistoryNomal, getHistoryLadder])

    const tableCount: string = ((tableList.length + 1) * 30) + 'px';

    return (
        <>
            <StyleTable trSum={tableCount}>
                <thead>
                    <StyleTr>
                        {TABLE_HEADER.map((list, index) => {
                            return (<StyleTd isHeader={'header'} key={index}>{list.name}</StyleTd>);
                        })}
                    </StyleTr>
                </thead>
                <tbody ref={tbodyRef}>
                    {tableList.map((list) => {
                        return (
                            <StyleTr key={list.historypk}>
                                <StyleTd isHeader={'bodys'} isVisble={true}>{list.historypk}</StyleTd>
                                <StyleTd isHeader={'bodys'}>{(list.type === "normal" ? "일반" : "레더")}</StyleTd>
                                <StyleTd isHeader={list.result}>{list.result.toUpperCase()}</StyleTd>
                                <StyleTd isHeader={'bodys'}>{list.scoreresult}</StyleTd>
                                <StyleTd isHeader={'bodys'}>{list.yournickname}</StyleTd>
                            </StyleTr>
                        );
                    })}
                </tbody>
            </StyleTable >
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </>
    );
}