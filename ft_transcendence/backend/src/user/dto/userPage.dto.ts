import { IsNotEmpty, IsOptional } from 'class-validator';

export class UserPageDto {
  @IsNotEmpty()
  currentpage: number;

  @IsNotEmpty()
  nextpage: number;

  @IsOptional()
  firstusername: string;

  @IsOptional()
  lastusername: string;
}
