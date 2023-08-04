import { useState, useRef, useEffect } from 'react';
import styled from 'styled-components';
import SvgButton from '../other/SvgButton';
import mainImage from '../../images/mainImage.png';
import imageCompression from "browser-image-compression";
import StateModal from '../modal/StateModal';

const BaseImage = styled.img`
    width: 250px;
    height: 250px;
    margin: 25px 0 0 0;
    border: 1px solid white;
    border-radius: 70%;
    overflow: hidden;
    object-fit: cover;
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-user-drag: none;
    user-drag: none;
    -webkit-touch-callout: none;
`;

const BaseFileDiv = styled.div`
    display: grid;
    grid-template-rows: 270px 40px;
    justify-items: center;
`;

const BaseFileInput = styled.input`
    display: none;
`;

interface pfImgType {
    isDisabled: boolean;
    avatar: string;
    setAvatar: React.Dispatch<React.SetStateAction<string>>
}

interface stateType {
    stateImg: string;
    msg: string;
}

export default function ProfileImg({ isDisabled, avatar, setAvatar }: pfImgType) {
    const fileRef = useRef<HTMLInputElement | null>(null);
    const [imageUrl, setImageUrl] = useState("");
    const [modalOpen, setModalOpen] = useState(false);
    const [stateData, setStateData] = useState<stateType>({
        stateImg: "",
        msg: "",
    })


    const imageFileUpLoad = () => {
        fileRef.current?.click();
    }
    const fileChange = (e: any) => {
        actionImgCompress(e.target.files[0]);
    }

    const actionImgCompress = async (fileSrc: any) => {
        const options = {
            maxSizeMB: 0.2,
            maxWidthOrHeight: 250,
            useWebWorker: true
        };
        try {
            const compressedFile = await imageCompression(fileSrc, options);
            // FileReader 는 File 혹은 Blob 객체를 이용하여, 파일의 내용을 읽을 수 있게 해주는 Web API
            const reader = new FileReader();
            reader.readAsDataURL(compressedFile);

            reader.onloadend = () => {
                const base64data = reader.result;
                if (base64data) {
                    setImageUrl(base64data.toString());
                    setAvatar(base64data.toString());
                }
            };
        } catch (error: any) {
            setModalOpen(true);
            setStateData({ stateImg: "Error", msg: error.message });
        }
    };

    useEffect(() => {
        setImageUrl(avatar);
    }, [avatar])

    return (
        <BaseFileDiv>
            <BaseImage src={imageUrl === "" ? mainImage : imageUrl} />
            <div>
                <BaseFileInput accept={'image/jpg,image/png,image/jpeg'} type='file' id='fileInput' name='profileImg' ref={fileRef} onChange={fileChange} />
                <SvgButton onClick={imageFileUpLoad} svgName='CameraSvg' isDisabled={isDisabled} />
            </div>
            {modalOpen ? <StateModal modalOpen={modalOpen} setModalOpen={setModalOpen} stateImg={stateData.stateImg} msg={stateData.msg} ></StateModal> : null}
        </BaseFileDiv>);
}