import { IsNotEmpty, IsOptional } from 'class-validator';

export class InputDto {
  @IsNotEmpty()
  roomnumber: string;

  @IsOptional()
  up?: boolean;

  @IsOptional()
  down?: boolean;
}
