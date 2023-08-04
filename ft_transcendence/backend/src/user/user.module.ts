import { forwardRef, Module } from '@nestjs/common';
import { UserService } from './user.service';
import { UserController } from './user.controller';
import { HistoryService } from 'src/history/history.service';
import { FriendRequestService } from 'src/friendRequest/friend-request.service';
import { HistoryModule } from 'src/history/history.module';
import { FriendRequestModule } from 'src/friendRequest/friend-request.module';
import { UserGateway } from './user.gateway';
import { AuthModule } from 'src/auth/auth.module';
import { ChatModule } from 'src/chat/chat.module';

@Module({
  imports: [
    HistoryModule,
    FriendRequestModule,
    forwardRef(() => AuthModule),
    forwardRef(() => ChatModule),
  ],
  providers: [UserService, UserGateway],
  exports: [UserService],
  controllers: [UserController],
})
export class UserModule {}
