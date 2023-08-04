import { IsBoolean, IsNotEmpty, IsString, MaxLength } from 'class-validator';

export class msgBattleAlertDTO {
  @IsNotEmpty()
  @IsString()
  roomId: string;

  @IsBoolean()
  @IsNotEmpty()
  accept: boolean;
}
