import {
  Body,
  Controller,
  Get,
  HttpException,
  ParseIntPipe,
  Patch,
  Post,
  Res,
  UseGuards,
} from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import {
  ApiBearerAuth,
  ApiBody,
  ApiCreatedResponse,
  ApiForbiddenResponse,
  ApiInternalServerErrorResponse,
  ApiOperation,
  ApiResponse,
  ApiTags,
} from '@nestjs/swagger';
import { UserID } from 'src/user/decorator/userid.decorator';
import { FortyTwoProfile } from 'src/user/dto/ftuserprofile.dto';
import { AuthService } from './auth.service';
import { Payload } from './decorator/payload.decorator';
import { PayloadDTO } from './dto/payload.dto';
import { FortyTwoAuthGuard } from './guards/ft.guard';
import { JwtAuthGuard } from './guards/jwt.guard';
import { JwtRefGuard } from './guards/jwtref.guard';

@Controller('auth')
@ApiTags('Auth API')
@ApiForbiddenResponse({ description: 'Unauthorized' })
export class AuthController {
  constructor(
    private authService: AuthService,
    private config: ConfigService,
  ) {}

  @ApiOperation({
    summary: 'logout',
    description: 'this will invalidate refresh token',
  })
  @ApiResponse({
    status: 200,
    description: 'Goodbye',
  })
  @ApiBearerAuth('token')
  @Get('logout')
  @UseGuards(JwtAuthGuard)
  async logout(@UserID(ParseIntPipe) uid: number): Promise<void> {
    console.log(uid);
    this.authService.logout(uid);
  }

  @ApiOperation({
    summary: 'refresh access token',
    description: 'new access token will be issued if refresh token is valid',
  })
  @ApiResponse({
    status: 200,
    description: 'new access token issued',
    schema: {
      type: 'object',
      properties: {
        accessToken: {
          type: 'string',
          description: 'the new access token',
        },
      },
    },
  })
  @ApiResponse({
    status: 401,
    description: 'refresh token compare failed',
  })
  @ApiBearerAuth('rtoken')
  @Get('refresh')
  @UseGuards(JwtRefGuard)
  async refresh(
    @Payload() payload: PayloadDTO,
  ): Promise<{ accessToken: string }> {
    return this.authService.refreshAuthToken(
      payload.id,
      payload.tfa_done,
      payload.refreshToken,
    );
  }

  @ApiOperation({
    summary: 'login entrypoint',
    description: 'redirects user to 42api OAuth page',
  })
  @ApiResponse({
    status: 302,
    description: 'will always redirect to 42api OAuth page',
  })
  @Get('ft_login')
  @UseGuards(FortyTwoAuthGuard)
  ft_login(): void {}

  @ApiOperation({
    summary: '42 OAuth callback url',
    description: '42 OAuth will be redirected here.',
  })
  @ApiResponse({
    status: 302,
    description:
      'will redirect to front-end page login or tfa with token and rtoken in uri',
  })
  @Get('ft_callback')
  @UseGuards(FortyTwoAuthGuard)
  async ft_callback(@Payload() user: FortyTwoProfile, @Res() res) {
    const data = await this.authService.login(user);
    if (!data.accessToken) return;

    const url = new URL(this.config.get<string>('HOST_URL'));
    url.port = this.config.get<string>('FRONT_PORT');
    url.searchParams.set('token', data.accessToken);
    url.searchParams.append('rtoken', data.refreshToken);
    url.pathname = this.config.get<string>('FRONT_LOGIN_URL');

    if (data.tfa) {
      url.pathname = this.config.get<string>('FRONT_TFA_URL');
      this.authService.setOTP(user.id);
    } else if (data.isFirst) 
      url.pathname = this.config.get<string>('FRONT_FIRST_LOGIN_URL');
    

    res.status(302).redirect(url.href);
  }

  @ApiOperation({
    summary: 'OTP email',
    description: 'get email where OTP is sent to',
  })
  @ApiResponse({
    status: 200,
    description: "return user's email",
    schema: {
      type: 'object',
      properties: {
        email: {
          type: 'string',
          description: 'the user email',
        },
      },
    },
  })
  @ApiBearerAuth('token')
  @Get('tfa_email')
  @UseGuards(JwtAuthGuard)
  async tfa_email(
    @UserID(ParseIntPipe) uid: number,
  ): Promise<{ email: string }> {
    return this.authService.getEmail(uid);
  }

  @ApiOperation({
    summary: 'post OTP password for authorization',
    description: "server will compare provided OTP with DB's data",
  })
  @ApiBody({
    schema: {
      type: 'object',
      properties: {
        otp: {
          type: 'string',
          description: 'otp to try',
        },
      },
    },
  })
  @ApiCreatedResponse({
    description: 'OTP match, new token generated',
    schema: {
      type: 'object',
      properties: {
        token: {
          type: 'string',
          description: 'the new access token',
        },
        rtoken: {
          type: 'string',
          description: 'the new refresh token',
        },
      },
    },
  })
  @ApiResponse({
    status: 302,
    description: 'OTP match, token and rtoken given as query',
  })
  @ApiResponse({
    status: 400,
    description: 'OTP is null',
  })
  @ApiResponse({
    status: 403,
    description: 'OTP auth failed',
  })
  @ApiInternalServerErrorResponse({
    status: 500,
    description: 'failed to retrieve OTP hash from DB',
  })
  @ApiBearerAuth('token')
  @Patch('tfa_login')
  @UseGuards(JwtAuthGuard)
  async tfa_login(
    @UserID(ParseIntPipe) uid: number,
    @Body('otp') otp: string,
  ): Promise<{ token: string; rtoken: string }> {
    if (!otp) throw new HttpException('otp cannot be null', 400);
    const match = await this.authService.loginOTP(uid, otp);
    if (match) {
      return {
        token: await this.authService.genAuthToken(uid, true),
        rtoken: await this.authService.genRefreshToken(uid, true),
      };
    } else {
      throw new HttpException('OTP auth failed', 403);
    }
  }

  @ApiOperation({
    summary: 'generate OTP password',
    description: "save the generated OTP password into user's DB",
  })
  @ApiCreatedResponse({
    description: 'OTP created and saved in DB',
  })
  @ApiBearerAuth('token')
  @Post('tfa_gen')
  @UseGuards(JwtAuthGuard)
  async tfa_generate(@Payload() payload: PayloadDTO): Promise<void> {
    if (payload.tfa_done)
      throw new HttpException('user has done OTP auth already.', 401);
    return this.authService.setOTP(payload.id);
  }

  // @ApiOperation({
  //   summary: 'get token for testing',
  //   description: "will create user with id 0 and return it's token",
  // })
  // @ApiResponse({
  //   status: 200,
  //   schema: {
  //     type: 'object',
  //     description: 'the created access token for testing',
  //     properties: {
  //       accessToken: {
  //         type: 'string',
  //         description: 'the created access token for testing',
  //       },
  //       refreshToken: {
  //         type: 'string',
  //         description: 'the created refresh token for testing',
  //       },
  //     },
  //   },
  // })
  // @Get('token')
  // async token(): Promise<{ accessToken: string; refreshToken: string }> {
  //   const data = await this.authService.login({
  //     id: 0,
  //     username: 'test',
  //     nickname: 'testaccount',
  //     email: 'test@example.com',
  //   });
  //   return {
  //     accessToken: data.accessToken,
  //     refreshToken: data.refreshToken,
  //   };
  // }

  // @Post('test')
  // @UseGuards(JwtAuthGuard)
  // @ApiBody({
  //   schema: {
  //     type: 'object',
  //     properties: {
  //       otp: {
  //         type: 'string',
  //         description: 'otp to try',
  //       },
  //     },
  //   },
  // })
  // @ApiBearerAuth('token')
  // async test(@UserID(ParseIntPipe) uid: number): Promise<boolean> {
  //   console.log(uid);
  //   // console.log("WHAT");
  //   // const token = {accessToken: "test"};
  //   // const url = new URL("http://dbuntu.lan");
  //   // url.port = "3000";
  //   // url.pathname = "login";
  //   // url.searchParams.set("token", token.accessToken);

  //   // res.status(302).redirect(url.href);
  //   // return token;
  //   // res.status(200).json(['a','ok']);
  //   // res.send();
  //   // res.send({a: "TEST"});
  //   // console.log(req);
  //   // console.log("\n");
  //   // console.log(res);
  //   // res.status(302).redirect("/");

  //   return true;
  //   // return res.send(true);
  //   // console.log(res.send("test"));
  //   // return true;
  //   // return (true);
  //   // return true;
  // }

  
  @ApiOperation({
    summary: 'generate random ID and login',
    description: 'BOTS',
  })
  @ApiResponse({
    status: 302,
    description: 'token and rtoken for the bot',
  })
  @Get('botgen')
  async botgen(@Res() res) {
    const uid = Math.floor(Math.random() * 1000000000);
    const user = {
      id: uid,
      email: uid.toString(),
      username: uid.toString(),
      nickname: 'bot-' + uid.toString(),
    };
    const data = await this.authService.login(user);

    const url = new URL(this.config.get<string>('HOST_URL'));
    url.port = this.config.get<string>('FRONT_PORT');
    url.searchParams.set('token', data.accessToken);
    url.searchParams.append('rtoken', data.refreshToken);
    url.pathname = this.config.get<string>('FRONT_LOGIN_URL');
    res.status(302).redirect(url.href);
  }
}
