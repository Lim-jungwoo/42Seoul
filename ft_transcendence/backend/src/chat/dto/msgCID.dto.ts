import { IsNotEmpty, IsNumber, MaxLength, MinLength } from 'class-validator';

export class msgCIDDTO {
  @IsNotEmpty()
  @IsNumber()
  id: number;
}
