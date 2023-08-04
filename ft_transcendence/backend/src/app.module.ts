import { MailerModule } from '@nestjs-modules/mailer';
import { Module } from '@nestjs/common';
import { ConfigModule } from '@nestjs/config';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { AppService } from './app.service';
import { AuthModule } from './auth/auth.module';
import { PrismaModule } from './prisma/prisma.module';
import { UserModule } from './user/user.module';
import { HistoryService } from './history/history.service';
import { FriendRequestService } from './friendRequest/friend-request.service';
import { ChatModule } from './chat/chat.module';
import { GameGateway } from './game/game.gateway';
import { GameService } from './game/game.service';
import { GameModule } from './game/game.module';

@Module({
  imports: [
    ConfigModule.forRoot({ isGlobal: true }),
    AuthModule,
    PrismaModule,
    ChatModule,
    MailerModule.forRoot({
      transport: {
        service: 'Naver',
        host: 'smtp.naver.com',
        port: 587,
        auth: {
          user: process.env.MAILER_NAME,
          pass: process.env.MAILER_PASS,
        },
      },
    }),
    GameModule,
  ],
  providers: [],
})
export class AppModule {}
