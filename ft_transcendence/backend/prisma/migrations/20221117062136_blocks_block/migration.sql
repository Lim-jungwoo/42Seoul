/*
  Warnings:

  - You are about to drop the `Blocks` table. If the table is not empty, all the data it contains will be lost.

*/
-- DropTable
DROP TABLE "Blocks";

-- CreateTable
CREATE TABLE "Block" (
    "bid" SERIAL NOT NULL,
    "uid" INTEGER NOT NULL,
    "tid" INTEGER NOT NULL,

    CONSTRAINT "Block_pkey" PRIMARY KEY ("bid")
);
