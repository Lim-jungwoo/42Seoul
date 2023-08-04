import { IsEmail, IsNotEmpty } from 'class-validator';

export class FortyTwoProfile {
  @IsNotEmpty()
  id: number;

  @IsNotEmpty()
  username: string;

  @IsNotEmpty()
  nickname: string;

  @IsEmail()
  email: string;
}
