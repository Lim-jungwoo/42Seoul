import { IsBoolean, IsNotEmpty, IsNumberString } from 'class-validator';

export class PayloadDTO {
  @IsNotEmpty()
  @IsNumberString()
  id: number;

  @IsNotEmpty()
  @IsBoolean()
  tfa_done: boolean;

  @IsNotEmpty()
  refreshToken: string;
}
