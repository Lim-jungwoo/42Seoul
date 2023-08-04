import React, { useRef } from 'react';
import styled from 'styled-components';

const TwoFactorInput = styled.input.attrs((props) => ({
    type: props.type,
}))`
    display: block;
    margin: 0;
    padding: 0 0 6px 0;
    width: 300px;
    border: 0;
    font-size: 1.1rem;
    border-radius: 4px;
    color: #B0BEC5;
    // color: #909099;
    background-color: #343434;
    &:focus {
      outline: none;
    }
  `;

const TwoFactorFrom = styled.form`
     display: grid;
     align-content: center;
     justify-items: center;
     padding: 2rem;
`;

const TwoFactorLabel = styled.label<{ reColor: number }>`
    color: ${(props) => (props.reColor === 1 ? '#aa00ff' : '#fafafa')};
    margin: 0;
    padding: 6px 0 6px 0;
`;

interface TfInputType {
    certNum: string,
    restart: string,
    setCertNum: React.Dispatch<React.SetStateAction<string>>,
}

export default function TfInput({ certNum, restart, setCertNum }: TfInputType) {

    const inputFocus = useRef<HTMLInputElement | null>(null);

    const onChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        event.target.value = event.target.value.replace(/[^A-Za-z0-9]/ig, '')
        setCertNum(event.target.value);
    };
    const proSubmit = (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
    };

    return (
        <TwoFactorFrom onSubmit={proSubmit}>
            {restart === 'recheck' ? <TwoFactorLabel reColor={1}>다시 입력해 주세요.</TwoFactorLabel> : null}
            {restart === 'remail' ? <TwoFactorLabel reColor={1}>인증 메일이 재발송 되었습니다.</TwoFactorLabel> : null}
            {restart === 'request' ? <TwoFactorLabel reColor={1}>이메일 재발급이 필요합니다.</TwoFactorLabel> : null}
            {restart === 'dbinput' ? <TwoFactorLabel reColor={1}>이메일을 확인해주세요.</TwoFactorLabel> : null}
            <TwoFactorLabel reColor={2} htmlFor="certNum">인증번호</TwoFactorLabel>
            <TwoFactorInput id="certNum"
                ref={inputFocus}
                onChange={onChange}
                type="text"
                value={certNum}
                maxLength={6}
            />
        </TwoFactorFrom>
    )
}