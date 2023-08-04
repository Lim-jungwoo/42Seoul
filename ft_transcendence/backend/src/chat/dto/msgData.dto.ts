import { IsNotEmpty, IsString, MaxLength } from 'class-validator';

export class msgDataDTO {
  @IsNotEmpty()
  @IsString()
  @MaxLength(1024)
  msg: string;
}
