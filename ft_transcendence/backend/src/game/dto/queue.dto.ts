import { IsNotEmpty, IsOptional } from 'class-validator';

export class QueueDto {
  @IsNotEmpty()
  gametype: string;

  @IsOptional()
  maptype?: string;
}
