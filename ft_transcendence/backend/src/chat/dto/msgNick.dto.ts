import { IsNotEmpty, IsString, MaxLength, MinLength } from 'class-validator';

export class msgNickDTO {
  @IsNotEmpty()
  @MinLength(3)
  @MaxLength(15)
  @IsString()
  nick: string;
}
