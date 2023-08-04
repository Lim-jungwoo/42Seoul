import styled from 'styled-components';
import SvgButton from '../other/SvgButton';

const GameCenterDiv = styled.div`
    text-align: center;
`;

interface mapBigType {
    nabiNum: number,
    mapCounter: number,
}

export default function GamMapBig({ nabiNum, mapCounter }: mapBigType) {

    return (
        <GameCenterDiv>
            {nabiNum === 0 ?
                <SvgButton isbigs={mapCounter} isDisabled={true} svgName={mapCounter === 0 ? 'MapBaseSvg' :
                    (mapCounter === 1 ? 'MapBallTwoSvg' : 'MapBrickSvg')}></SvgButton>
                : <SvgButton svgName='MapLadderSvg' />}
        </GameCenterDiv>
    );
}