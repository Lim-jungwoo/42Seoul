/*
  Warnings:

  - The `historypk` column on the `History` table would be dropped and recreated. This will lead to data loss if there is data in the column.

*/
-- DropIndex
DROP INDEX "History_historypk_key";

-- AlterTable
ALTER TABLE "History" DROP COLUMN "historypk",
ADD COLUMN     "historypk" SERIAL NOT NULL,
ADD CONSTRAINT "History_pkey" PRIMARY KEY ("historypk");
