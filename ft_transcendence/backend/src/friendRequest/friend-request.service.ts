import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PrismaService } from 'src/prisma/prisma.service';

@Injectable()
export class FriendRequestService {
  constructor(private prisma: PrismaService, private config: ConfigService) {}

  async deleteAllRequest() {
    return this.prisma.friendRequest.deleteMany({});
  }

  async getFriendRequest(userid: number, friendname: string) {
    return this.prisma.friendRequest.findFirst({
      where: {
        AND: [{ myid: userid }, { friendname: friendname }],
      },
    });
  }

  async getNumberFriendRequest(userid: number) {
    return this.prisma.friendRequest.count({
      where: {
        myid: userid,
      },
    });
  }

  // await prisma.product.findMany({
  //   where: {
  //     AND: [
  //       { price: 21.99 },
  //       { filters: { some: { name: 'ram', value: '8GB' } } },
  //       { filters: { some: { name: 'storage', value: '256GB' } } },
  //     ],
  //   },
  // })
}
