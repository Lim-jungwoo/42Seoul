import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-42';
import { FortyTwoUserProfile } from 'src/user/user.interface';

@Injectable()
export class FortyTwoStrategy extends PassportStrategy(Strategy) {
  constructor(private config: ConfigService) {
    super({
      clientID: config.get<string>('FT_API_CID'),
      clientSecret: config.get<string>('FT_API_SEC'),
      callbackURL: config.get<string>('FT_API_CALLBACK'),
    });
  }

  validate(accessToken: string, refreshToken: string, profile: any): any {
    const { id, username, emails } = profile;
    const valueemail = Object.values(emails)[0];
    const email = String(valueemail['value']);
    const idNumber = +id;
    let userProfile: FortyTwoUserProfile = {
      id: idNumber,
      username: username,
      nickname: username,
      email,
    };
    if (!userProfile)
      throw new HttpException('Invalid 42api Token', HttpStatus.UNAUTHORIZED);

    return userProfile;
  }
}
