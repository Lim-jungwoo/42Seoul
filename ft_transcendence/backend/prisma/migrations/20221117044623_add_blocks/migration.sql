-- CreateTable
CREATE TABLE "Blocks" (
    "bid" SERIAL NOT NULL,
    "uid" INTEGER NOT NULL,
    "tid" INTEGER NOT NULL,

    CONSTRAINT "Blocks_pkey" PRIMARY KEY ("bid")
);
