import { useEffect, useState } from 'react';
import styled from 'styled-components';
import SvgButton from '../other/SvgButton';


const Ladderdiv = styled.div<{ isgames?: string }>`
    display: flex;
    width: ${(props) => props.isgames === "ok" ? '100%' : '300px'};
    color: #aa00ff;
    cursor: default;
    -ms-user-select: none;
    -moz-user-select: -moz-none;
    -khtml-user-select: none;
    -webkit-user-select: none;
    user-select: none;
    align-items: ${(props) => props.isgames === "ok" && 'center'};
    justify-content: ${(props) => props.isgames === "ok" && 'center'};
`
const LadderContent = styled.p`
    height: 40px;
    justify-content: center;
    text-align: center;
    vertical-align: middle;
    font-size: 1rem;
    margin-right 5px;
    padding-top: 15px;
`;

const LadderPannel = styled.p<{ isgames?: string, numCheck: number }>`
    height: ${(props) => (props.isgames === "ok" ? '150px' : '40px')};
    width: ${(props) => (props.isgames === "ok" ? '80px' : '30px')};
    background-color: #343434;
    color: #909099;
    margin 2px;
    margin-left: ${(props) => (props.numCheck === 0 && '15px')};
    font-size: ${(props) => (props.isgames === "ok" ? '5rem' : '2rem')};
    line-height: ${(props) => (props.isgames === "ok" && '150px')};
    text-align: center;
    padding-top: 5px;
`;

interface ladderType {
    isgames?: string,
    ladders: string,
    scores: string,
}

export default function LadderScore({ isgames, ladders, scores }: ladderType) {
    const [fillScores, setFillScores] = useState<string[]>([]);
    const [trophyLadder, setTrophyLadder] = useState("");

    useEffect(() => {
        const splirtScores = scores.padStart(4, ' ').split('');
        splirtScores.push('P');
        splirtScores.push('T');
        setFillScores(splirtScores);
        setTrophyLadder(ladders);
    }, [ladders, scores])

    return (
        <Ladderdiv isgames={isgames}>
            {isgames === "ok" ? null : <LadderContent>레더</LadderContent>}
            <SvgButton svgName='TrophySvg' ladders={trophyLadder} isgames={isgames}></SvgButton>
            {fillScores.map((score, index) => (
                <LadderPannel isgames={isgames} key={index} numCheck={index}>{score}</LadderPannel>
            ))}
        </Ladderdiv>
    );
}