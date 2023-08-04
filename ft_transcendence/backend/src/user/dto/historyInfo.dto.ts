import { IsNotEmpty, IsOptional } from 'class-validator';

export class HistoryInfoDto {
  @IsOptional()
  nickname: string;
  @IsNotEmpty()
  currentpage: number;
  @IsNotEmpty()
  nextpage: number;
  @IsOptional()
  firsthistorypk: number;
  @IsOptional()
  lasthistorypk: number;
  @IsOptional()
  type: string;
}
