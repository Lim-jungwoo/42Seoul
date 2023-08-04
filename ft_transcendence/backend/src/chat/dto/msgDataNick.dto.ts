import { IntersectionType } from '@nestjs/swagger';
import { msgDataDTO } from './msgData.dto';
import { msgNickDTO } from './msgNick.dto';

export class msgDataNickDTO extends IntersectionType(msgDataDTO, msgNickDTO) {}
