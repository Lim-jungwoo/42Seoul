import { Module } from '@nestjs/common';
import { FriendRequestService } from 'src/friendRequest/friend-request.service';
import { UserService } from 'src/user/user.service';
import { HistoryController } from './history.controller';
import { HistoryService } from './history.service';

@Module({
  providers: [HistoryService, UserService, FriendRequestService],
  exports: [HistoryService],
  controllers: [HistoryController],
})
export class HistoryModule {}
