import {
  Controller,
  Body,
  Post,
  Req,
  Res,
  UseGuards,
  ParseIntPipe,
  UseFilters,
  HttpException,
} from '@nestjs/common';
import { HistoryService } from './history.service';
import { ApiBearerAuth, ApiOperation, ApiBody } from '@nestjs/swagger';
import { JwtAuthGuard } from 'src/auth/guards/jwt.guard';
import { UserService } from 'src/user/user.service';
import { HistoryInfoDto } from 'src/user/dto/historyInfo.dto';
import { UserID } from 'src/user/decorator/userid.decorator';

@Controller('user')
export class HistoryController {
  constructor(
    private historyService: HistoryService,
    private userService: UserService,
  ) {}

  @ApiOperation({
    summary: 'get history',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @ApiBody({
    description:
      'ex => { "currentpage": number, "nextpage": number, "firsthistorypk": "1", "lasthistorypk": "2", "type": input "all" or "normal" or "ladder" }',
  })
  @Post('get_five_history')
  async getFiveHistory(
    @Body()
    historyInfo: HistoryInfoDto,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    const user = await this.userService.getUser({ id: uid });
    if (!user) {
      throw new HttpException('There is no user matching token', 404);
    }

    if (!historyInfo) {
      throw new HttpException('Body has invalid value', 404);
    }

    if (
      !(
        historyInfo.type === 'all' ||
        historyInfo.type === 'normal' ||
        historyInfo.type === 'ladder'
      )
    ) {
      throw new HttpException(
        'It has invalid type, please input all or normal or ladder',
        403,
      );
    }
    const historyResult = await this.historyService.getHistory(
      uid,
      historyInfo,
    );
    const totalNumberHistory =
      historyInfo.type === 'all'
        ? await this.historyService.getTotalNumberHistory(uid)
        : await this.historyService.getNormalLadderHistory(
            uid,
            historyInfo.type,
          );
    res.status(200).send([historyResult, { total: totalNumberHistory }]);
  }

  @ApiOperation({
    summary: 'get user history',
  })
  @ApiBearerAuth('token')
  @UseGuards(JwtAuthGuard)
  @ApiBody({
    description:
      'ex => { "nickname": "string", "currentpage": number, "nextpage": number, "firsthistorypk": "1", "lasthistorypk": "2", "type": input "all" or "normal" or "ladder" }',
  })
  @Post('get_user_five_history')
  async getUserFiveHistory(
    @Body()
    historyInfo: HistoryInfoDto,
    @UserID(ParseIntPipe) uid: number,
    @Res() res,
  ) {
    const user = await this.userService.getUser({ id: uid });
    if (!user) {
      throw new HttpException('There is no user matching token', 404);
    }

    if (!historyInfo) {
      throw new HttpException('Body has invalid value', 404);
    }

    const otherUser = await this.userService.getUser({ nickname: historyInfo.nickname });
    if (!otherUser) {
      throw new HttpException('There is no user matching nickname', 404);
    }

    if (
      !(
        historyInfo.type === 'all' ||
        historyInfo.type === 'normal' ||
        historyInfo.type === 'ladder'
      )
    ) {
      throw new HttpException(
        'It has invalid type, please input all or normal or ladder',
        403,
      );
    }
    const historyResult = await this.historyService.getHistory(
      otherUser.id,
      historyInfo,
    );
    const totalNumberHistory =
      historyInfo.type === 'all'
        ? await this.historyService.getTotalNumberHistory(otherUser.id)
        : await this.historyService.getNormalLadderHistory(
            otherUser.id,
            historyInfo.type,
          );
    res.status(200).send([historyResult, { total: totalNumberHistory }]);
  }
}
