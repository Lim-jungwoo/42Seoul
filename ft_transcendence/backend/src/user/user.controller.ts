import {
  BadRequestException,
  Body,
  Controller,
  Delete,
  forwardRef,
  Get,
  Header,
  Headers,
  HttpException,
  Inject,
  NotFoundException,
  Param,
  ParseIntPipe,
  Patch,
  Post,
  Query,
  Req,
  Res,
  UseFilters,
  UseGuards,
} from '@nestjs/common';
import {
  ApiBearerAuth,
  ApiBody,
  ApiHeader,
  ApiOperation,
  ApiParam,
  ApiProperty,
  ApiQuery,
  ApiResponse,
} from '@nestjs/swagger';
import { History, User, User as UserModel } from '@prisma/client';
import { send } from 'process';
import { JwtAuthGuard } from 'src/auth/guards/jwt.guard';
import { ChatService } from 'src/chat/chat.service';
import { isNativeError } from 'util/types';
import { UserID } from './decorator/userid.decorator';
import { UpdateUserDto } from './dto/updateUser.dto';
import { UserPageDto } from './dto/userPage.dto';
import { FortyTwoUserProfile, UserProfile } from './user.interface';
import { UserService } from './user.service';

@Controller('user')
export class UserController {
  constructor(
    @Inject(forwardRef(() => ChatService))
    private chatService: ChatService,
    private userService: UserService,
  ) {}

  @ApiOperation({
    summary: 'using token to update nickname, avatar, tfa',
  })
  @ApiBody({
    description:
      'Body example => { "nickname": "changename", "avatar": "picturefile", "tfa": false }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Patch('update_user')
  async updateUser(
    @Body()
    userData: UpdateUserDto,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    const user = await this.userService.getUser({
      id: uid,
    });
    if (!user) {
      throw new HttpException('There is no user matching token', 404);
    }

    let checkNickName: User;
    if (userData.nickname) {
      checkNickName = await this.userService.getUser({
        nickname: userData.nickname,
      });
    }
    if (checkNickName && user.id === checkNickName.id) {
    } else if (checkNickName) {
      throw new HttpException('A user with a nickname already exists', 403);
    }
    const updateUser = await this.userService.updateUser({
      where: { id: uid },
      data: {
        nickname: userData.nickname,
        avatar: userData.avatar,
        tfa: userData.tfa,
      },
    });

    if (userData.nickname || userData.avatar)
      this.chatService.updateUser(uid, user.nickname, userData.nickname, userData.avatar);

    if (!updateUser) {
      res.status(500).send('update user is failed');
      throw new HttpException('update user is failed', 500);
    }
    res.status(200).send(updateUser);
  }

  @ApiOperation({
    summary: "get user profile by user's username",
  })
  @ApiBody({
    description: 'input user\'s username ex) { "username": "jlim" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('get_user')
  async getUserByUserName(@Body('nickname') name: string, @Res() res) {
    if (!name) throw new HttpException('nickname cannot be null', 403);
    const user = await this.userService.getUserProfile({
      nickname: name,
    });
    if (!user) {
      throw new HttpException('There is no user matching username', 404);
    }
    res.status(200).send(user);
  }

  @ApiOperation({
    summary: 'get user myself profile',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Get('get_myself')
  async getUser(@UserID(ParseIntPipe) uid: number, @Res() res) {
    const user = await this.userService.getUserProfile({
      id: uid,
    });
    if (!user) {
      throw new HttpException('There is no user who has token', 404);
    }
    res.status(200).send(user);
  }

  @ApiOperation({
    summary: 'get five user, 현재 페이지와 이동할 페이지를 숫자로 입력',
  })
  @ApiBody({
    description:
      'ex => { "currentpage": number, "nextpage": number, "firstusername": "1", "lastusername": "2" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('get_five_user')
  async getFiveUser(
    @Body()
    page: UserPageDto,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    const myself = await this.userService.getUser({ id: uid });
    let user = await this.userService.getFiveUser(page, uid);
    let userInfo = [];
    const totalNumberUser = await this.userService.getNumberUser();
    for (let i in user) {
      userInfo.push(user[i]);
      userInfo[i].isfriend = await this.userService.checkIsFriend(
        user[i].username,
        myself.username,
      );
    }
    res.status(200).send([userInfo, { total: totalNumberUser - 1 }]);
  }

  // @ApiOperation({
  //   summary: 'test accpet token',
  // })
  // @ApiBearerAuth('token')
  // @UseGuards(JwtAuthGuard)
  // @Get('testToken')
  // async testToken() {
  //   return 'authorization complete';
  // }

  @ApiOperation({
    summary: 'get all friend, /user/getfriendall',
  })
  @ApiResponse({
    status: 200,
    description:
      'if success to get all friend, this returns body [ [friends array], number of friends ]',
  })
  @ApiBody({
    description:
      'ex => { "currentpage": number, "nextpage": number, "firstusername": "1", "lastusername": "2" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('get_five_friend')
  async getFiveFriend(
    @Body()
    page: UserPageDto,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    const user = await this.userService.getUser({ id: uid });
    if (!user) {
      throw new HttpException('It has error to get myself', 404);
    }

    const friends = (await this.userService.getFiveFriend(page, uid)).friends;
    const totalNumberFriend = await this.userService.getTotalNumberFriend(uid);

    res
      .status(200)
      .send([friends, { total: totalNumberFriend[0]._count.friends }]);
  }

  @ApiOperation({
    summary: 'friend request accept',
  })
  @ApiBody({
    description: 'ex => { "username": "request\'s friend name" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('accept_friend')
  async acceptFriend(
    @Body('username') userName: string,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    if (!userName) throw new HttpException('username cannot be null', 403);
    const user = await this.userService.getUser({ id: uid });
    if (!user) {
      throw new HttpException('It has error to get myself', 404);
    }
    const friend = await this.userService.getUser({ username: userName });
    if (!friend) {
      throw new HttpException(
        'There is no user matching friend request username',
        404,
      );
    }
    const acceptResult = await this.userService.acceptFriend(user, friend);
    if (typeof acceptResult === 'string') {
      throw new HttpException(acceptResult, 404);
    }
    const declineResult = await this.userService.declineFriend(
      uid,
      friend.username,
    );
    if (typeof declineResult === 'string') {
      throw new HttpException(declineResult, 404);
    }
    res.status(200).send('accept friend request success');
  }

  @ApiOperation({
    summary: 'friend request decline',
  })
  @ApiBody({
    description: 'ex => { "username": "request\'s friend name" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('decline_friend')
  async declineFriend(
    @Body('username') userName: string,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    if (!userName) throw new HttpException('username cannot be null', 403);
    const friend = await this.userService.getUser({ username: userName });
    if (!friend) {
      throw new HttpException(
        'There is no user matching friend request username',
        404,
      );
    }
    const declineResult = await this.userService.declineFriend(
      uid,
      friend.username,
    );
    if (typeof declineResult === 'string') {
      throw new HttpException(declineResult, 404);
    }
    res.status(200).send('decline friend request success');
  }

  @ApiOperation({
    summary: 'delete friend',
  })
  @ApiBody({
    description: 'ex => { "username": "delete friend name" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('delete_friend')
  async deleteFriend(
    @Body('username') friendName: string,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    if (!friendName) throw new HttpException('username cannot be null', 403);
    const friend = await this.userService.getUser({ username: friendName });
    if (!friend) {
      throw new HttpException('There is no user matching friendname', 404);
    }
    const user = await this.userService.getUser({ id: uid });
    if (!user) {
      throw new HttpException('There is no user matching token', 404);
    }
    await this.userService.deleteFriend(user, friend);
    res.status(200).send('delete friend success');
  }

  @ApiOperation({
    summary: 'block user',
  })
  @ApiBody({
    description: 'ex => { "username": "block user username" }',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @Post('block_user')
  async blockUser(
    @Body('username') username: string,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    if (!username) throw new HttpException('username cannot be null', 403);
    const blockUser = await this.userService.getUser({ username: username });
    if (!blockUser) throw new HttpException('There is no user matching username', 404);
    if (uid === blockUser?.id) throw new HttpException('User cannot block himself', 403);
    this.userService.blockUser(uid, blockUser.id);
    res.status(200).send('block user success');
  }
}
// async createDraft(
//   @Body() postData: { title: string; content?: string; authorEmail: string },
// ): Promise<PostModel> {
//   const { title, content, authorEmail } = postData;
//   return this.postService.createPost({
//     title,
//     content,
//     author: {
//       connect: { email: authorEmail },
//     },
//   });
// }
