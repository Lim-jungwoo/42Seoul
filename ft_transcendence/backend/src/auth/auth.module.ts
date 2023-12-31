import { forwardRef, Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthController } from './auth.controller';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { FortyTwoStrategy } from './strategies/ft.strategy';
import { UserModule } from 'src/user/user.module';
import { JwtAuthStrategy } from './strategies/jwt.strategy';
import { JwtRefStrategy } from './strategies/jwtref.startegy';
import { ChatModule } from 'src/chat/chat.module';
import { GameModule } from 'src/game/game.module';

@Module({
  imports: [
    JwtModule.register({
      secret: process.env.JWT_SECRET,
      signOptions: { expiresIn: process.env.JWT_VTIME },
    }),
    PassportModule,
    forwardRef(() => UserModule),
    forwardRef(() => ChatModule),
    forwardRef(() => GameModule),
  ],
  providers: [AuthService, FortyTwoStrategy, JwtAuthStrategy, JwtRefStrategy],
  exports: [AuthService],
  controllers: [AuthController],
})
export class AuthModule {}
