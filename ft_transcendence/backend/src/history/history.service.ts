import { Injectable } from '@nestjs/common';
import { History, Prisma } from '@prisma/client';
import { userInfo } from 'os';
import { PrismaService } from 'src/prisma/prisma.service';

export interface sendHistory {
  yournickname: string;
  result: string;
  scoreresult: string;
  type: string;
  historypk: string;
}

@Injectable()
export class HistoryService {
  constructor(private prisma: PrismaService) {}

  async createHistory(data: Prisma.HistoryCreateInput): Promise<History> {
    return this.prisma.history.create({
      data,
    });
  }

  async getTotalNumberHistory(userid: number) {
    return this.prisma.history.count({
      where: { myid: userid },
    });
  }

  async getNormalLadderHistory(userid: number, type: string) {
    return this.prisma.history.count({
      where: { myid: userid, type: type },
    });
  }

  async getHistory(
    userid: number,
    page: {
      currentpage: number;
      nextpage: number;
      firsthistorypk: number;
      lasthistorypk: number;
      type: string;
    },
  ) {
    const movePage = page.nextpage - page.currentpage;
    const skip = 1;
    const take = movePage >= 0 ? 15 : -15;
    const cursor =
      movePage === 0
        ? null
        : movePage > 0
        ? page.lasthistorypk
        : page.firsthistorypk;

    if (page.type === 'all') {
      if (cursor === null) {
        return this.prisma.history.findMany({
          where: { myid: userid },
          take: take,
          orderBy: {
            historypk: 'desc',
          },
          select: {
            yournickname: true,
            result: true,
            scoreresult: true,
            type: true,
            historypk: true,
          },
        });
      } else {
        return this.prisma.history.findMany({
          where: { myid: userid },
          skip: skip + (Math.abs(movePage) - 1) * Math.abs(take),
          take: take,
          cursor: { historypk: cursor },
          orderBy: {
            historypk: 'desc',
          },
          select: {
            yournickname: true,
            result: true,
            scoreresult: true,
            type: true,
            historypk: true,
          },
        });
      }
    } else {
      if (cursor === null) {
        return this.prisma.history.findMany({
          where: { myid: userid, type: page.type },
          take: take,
          orderBy: {
            historypk: 'desc',
          },
          select: {
            yournickname: true,
            result: true,
            scoreresult: true,
            type: true,
            historypk: true,
          },
        });
      } else {
        return this.prisma.history.findMany({
          where: { myid: userid, type: page.type },
          skip: skip + (Math.abs(movePage) - 1) * Math.abs(take),
          take: take,
          cursor: { historypk: cursor },
          orderBy: {
            historypk: 'desc',
          },
          select: {
            yournickname: true,
            result: true,
            scoreresult: true,
            type: true,
            historypk: true,
          },
        });
      }
    }
  }

  async deleteAllHistory() {
    return this.prisma.history.deleteMany({});
  }
}
