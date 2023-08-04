import { forwardRef, Module } from '@nestjs/common';
import { AuthModule } from 'src/auth/auth.module';
import { HistoryModule } from 'src/history/history.module';
import { UserModule } from 'src/user/user.module';
import { GameGateway } from './game.gateway';
import { GameService } from './game.service';
import { ScheduleModule } from '@nestjs/schedule';
import { GamePlayGateway } from './game-play.gateway';

@Module({
  imports: [
    forwardRef(() => AuthModule),
    forwardRef(() => UserModule),
    HistoryModule,
    ScheduleModule.forRoot(),
  ],
  providers: [GameGateway, GameService, GamePlayGateway],
  exports: [GameService],
  controllers: [],
})
export class GameModule {}
