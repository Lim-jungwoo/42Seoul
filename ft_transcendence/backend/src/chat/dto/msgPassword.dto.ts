import { IsNotEmpty, IsString, MaxLength, MinLength } from 'class-validator';

export class msgPasswordDTO {
  @IsNotEmpty()
  @MaxLength(15)
  @IsString()
  password: string;
}
