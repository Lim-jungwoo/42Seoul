import styled from 'styled-components';
import React, { useState } from 'react';
import SvgButton from '../other/SvgButton';

const MapDiv = styled.div`
    text-align: center;
`;

interface mapListType {
    setMapCounter: React.Dispatch<React.SetStateAction<number>>;
}

export default function GameMapList({ setMapCounter }: mapListType) {
    const [useActive, setUseActive] = useState("0");

    const baseSvgClick = () => {
        setUseActive("0");
        setMapCounter(0);
    }
    const ballSvgClick = () => {
        setUseActive("1");
        setMapCounter(1);
    }
    const brickSvgClick = () => {
        setUseActive("2");
        setMapCounter(2);
    }


    return (
        <MapDiv>
            <SvgButton isgames={useActive} svgName='MapBaseSvg' onClick={baseSvgClick}></SvgButton>
            <SvgButton isgames={useActive} svgName='MapBallTwoSvg' onClick={ballSvgClick}></SvgButton>
            <SvgButton isgames={useActive} svgName='MapBrickSvg' onClick={brickSvgClick}></SvgButton>
        </MapDiv>);
}