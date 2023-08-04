import {
  IsAlphanumeric,
  IsBoolean,
  IsOptional,
  IsString,
  MaxLength,
  MinLength,
} from 'class-validator';

export class UpdateUserDto {
  @IsOptional()
  @MaxLength(15)
  @MinLength(3)
  @IsString()
  @IsAlphanumeric()
  nickname?: string;

  @IsOptional()
  @IsString()
  avatar?: string;

  @IsOptional()
  @IsBoolean()
  tfa?: boolean;
}
