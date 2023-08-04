import {
  Controller,
  UseGuards,
  Post,
  Body,
  Req,
  Res,
  ParseIntPipe,
  UseFilters,
  HttpException,
} from '@nestjs/common';
import { FriendRequestService } from './friend-request.service';
import {
  ApiOperation,
  ApiBearerAuth,
  ApiBody,
  ApiResponse,
} from '@nestjs/swagger';
import { JwtAuthGuard } from 'src/auth/guards/jwt.guard';
import { UserService } from 'src/user/user.service';
import { UserID } from 'src/user/decorator/userid.decorator';
import { UserPageDto } from 'src/user/dto/userPage.dto';

@Controller('user')
export class FriendRequestController {
  constructor(
    private friendRequestService: FriendRequestService,
    private userService: UserService,
  ) {}

  @ApiOperation({
    summary: 'test send friend request',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @ApiBody({
    description: 'ex => { "username": "find friend name" }',
  })
  @Post('send_friend_request')
  async sendFriendRequest(
    @Body('username') userName: string,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    if (!userName) throw new HttpException('username cannot be null', 403);
    const friend = await this.userService.getUser({ username: userName });
    if (!friend) {
      // res.status(404).send('There is no user matching friend name');
      throw new HttpException('There is no user matching friend name', 404);
    }
    const myself = await this.userService.getUser({ id: uid });
    if (friend.username === myself.username) {
      // res.status(403).send('User cannot add yourself as friend');
      throw new HttpException('User cannot add yourself as friend', 403);
    }

    const checkIsFriend = await this.userService.checkIsFriend(
      myself.username,
      friend.username,
    );
    if (checkIsFriend === true) {
      // res.status(403).send('You are already friends');
      throw new HttpException('You are already friends', 403);
    }

    const sendFriendRequestResult = await this.userService.sendFriendRequest(
      friend,
      myself,
    );
    if (typeof sendFriendRequestResult === 'string') {
      // res.status(403).send(sendFriendRequestResult);
      throw new HttpException(sendFriendRequestResult, 403);
    }
    res.status(200).send('send friend request success');
  }

  // @ApiOperation({
  //   summary: 'send friend request from user1 to user2',
  // })
  // @ApiBody({
  //   description: 'ex => { "username1": "user1", "username2": "user2" }',
  // })
  // @Post('send_friend_request_user')
  // async sendFriendRequestUser(
  //   @Body() data: { username1: string; username2: string },
  //   @Res() res,
  // ) {
  //   const user1 = await this.userService.getUser({ username: data.username1 });
  //   if (!user1) {
  //     res.status(404).send('There is no user1 matching username1');
  //     return 'There is no user1 matching username1';
  //   }
  //   const user2 = await this.userService.getUser({ username: data.username2 });
  //   if (!user2) {
  //     res.status(404).send('There is no user2 matching username2');
  //     return 'There is no user2 matching username1';
  //   }

  //   const checkIsFriend = await this.userService.checkIsFriend(
  //     user1.username,
  //     user2.username,
  //   );
  //   if (checkIsFriend === true) {
  //     res.status(403).send('User1 and User2 are already friends');
  //     return 'User1 and User2 are already friends';
  //   }

  //   const sendFriendRequestResult = await this.userService.sendFriendRequest(
  //     user2,
  //     user1,
  //   );
  //   if (typeof sendFriendRequestResult === 'string') {
  //     res.status(403).send(sendFriendRequestResult);
  //     return;
  //   }
  //   res.status(200).send('send friend request success');
  //   return;
  // }

  @ApiOperation({
    summary: 'get five friend request',
  })
  @ApiResponse({
    status: 200,
    description:
      'Response has user information and number of total firend request',
  })
  @ApiBody({
    description:
      'ex => { "currentpage": number, "nextpage": number, "firstusername": "1", "lastusername": "2" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('get_five_friend_request')
  async getFiveFriendRequest(
    @Body()
    page: UserPageDto,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    const friendRequest = await this.userService.getFiveFriendRequest(
      page,
      uid,
    );
    let user = [];
    if (typeof friendRequest === 'string') {
      // res.status(404).send(friendRequest);
      throw new HttpException(friendRequest, 404);
    } else {
      for (let i in friendRequest) {
        user.push(
          await this.userService.getUserProfile({
            username: friendRequest[i].friendname,
          }),
        );
      }
    }

    const totalNumberFriendRequest =
      await this.friendRequestService.getNumberFriendRequest(uid);

    res.status(200).send([user, { total: totalNumberFriendRequest }]);
  }
}
