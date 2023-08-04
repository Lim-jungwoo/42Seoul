import { Module } from '@nestjs/common';
import { UserService } from 'src/user/user.service';
import { FriendRequestController } from './friend-request.controller';
import { FriendRequestService } from './friend-request.service';

@Module({
  providers: [FriendRequestService, UserService],
  exports: [FriendRequestService],
  controllers: [FriendRequestController],
})
export class FriendRequestModule {}
