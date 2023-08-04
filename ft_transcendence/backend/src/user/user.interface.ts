import { FriendRequest, History, User } from '@prisma/client';

export interface FortyTwoUserProfile {
  id: number;
  username: string;
  nickname: string;
  email: string;
}

export interface UserProfile {
  email: string;
  username: string;
  nickname: string;
  avatar?: string;
  status: string;
  tfa: boolean;
  // historys: History[];
  // friends: User[];
  // friendsrequests: FriendRequest[];
}
