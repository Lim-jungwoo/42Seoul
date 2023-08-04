import React from 'react';
import Approuter from './routers/Approuter';
import { Reset } from 'styled-reset';
import styled from 'styled-components';

const AppDiv = styled.div`
  background-color: #121212;
  width: 100vw;
  height: 100vh;
`;

function App() {

  return (
    <React.Fragment>
      <Reset />
      <AppDiv>
        <Approuter></Approuter>
      </AppDiv>
    </React.Fragment>
  );
}

export default App;
