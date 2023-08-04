-- CreateEnum
CREATE TYPE "LadderRating" AS ENUM ('Bronze', 'Silver', 'Gold');

-- CreateEnum
CREATE TYPE "HistoryType" AS ENUM ('normal', 'ladder');

-- CreateTable
CREATE TABLE "User" (
    "id" INTEGER NOT NULL,
    "email" TEXT NOT NULL,
    "username" TEXT NOT NULL,
    "nickname" TEXT NOT NULL,
    "avatar" TEXT,
    "ladderrating" TEXT NOT NULL DEFAULT 'Bronze',
    "ladderscore" INTEGER NOT NULL DEFAULT 0,
    "lasttokentime" TIMESTAMP(3),
    "tfa" BOOLEAN NOT NULL DEFAULT false,
    "tfacode" TEXT,
    "tfatime" TIMESTAMP(3),
    "rtoken" TEXT,
    "status" TEXT NOT NULL DEFAULT 'offline',

    CONSTRAINT "User_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "History" (
    "myid" INTEGER NOT NULL,
    "yourid" INTEGER NOT NULL,
    "yournickname" TEXT NOT NULL,
    "result" TEXT NOT NULL,
    "myscore" INTEGER NOT NULL,
    "yourscore" INTEGER NOT NULL,
    "scoreresult" TEXT NOT NULL,
    "type" TEXT NOT NULL,
    "historypk" TEXT NOT NULL
);

-- CreateTable
CREATE TABLE "FriendRequest" (
    "requestpk" SERIAL NOT NULL,
    "myid" INTEGER NOT NULL,
    "friendid" INTEGER NOT NULL,
    "friendname" TEXT NOT NULL,

    CONSTRAINT "FriendRequest_pkey" PRIMARY KEY ("requestpk")
);

-- CreateTable
CREATE TABLE "_friends" (
    "A" INTEGER NOT NULL,
    "B" INTEGER NOT NULL
);

-- CreateTable
CREATE TABLE "_FriendRequestToUser" (
    "A" INTEGER NOT NULL,
    "B" INTEGER NOT NULL
);

-- CreateIndex
CREATE UNIQUE INDEX "User_email_key" ON "User"("email");

-- CreateIndex
CREATE UNIQUE INDEX "User_username_key" ON "User"("username");

-- CreateIndex
CREATE UNIQUE INDEX "User_nickname_key" ON "User"("nickname");

-- CreateIndex
CREATE UNIQUE INDEX "History_historypk_key" ON "History"("historypk");

-- CreateIndex
CREATE UNIQUE INDEX "_friends_AB_unique" ON "_friends"("A", "B");

-- CreateIndex
CREATE INDEX "_friends_B_index" ON "_friends"("B");

-- CreateIndex
CREATE UNIQUE INDEX "_FriendRequestToUser_AB_unique" ON "_FriendRequestToUser"("A", "B");

-- CreateIndex
CREATE INDEX "_FriendRequestToUser_B_index" ON "_FriendRequestToUser"("B");

-- AddForeignKey
ALTER TABLE "History" ADD CONSTRAINT "History_myid_fkey" FOREIGN KEY ("myid") REFERENCES "User"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_friends" ADD CONSTRAINT "_friends_A_fkey" FOREIGN KEY ("A") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_friends" ADD CONSTRAINT "_friends_B_fkey" FOREIGN KEY ("B") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_FriendRequestToUser" ADD CONSTRAINT "_FriendRequestToUser_A_fkey" FOREIGN KEY ("A") REFERENCES "FriendRequest"("requestpk") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_FriendRequestToUser" ADD CONSTRAINT "_FriendRequestToUser_B_fkey" FOREIGN KEY ("B") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE;
