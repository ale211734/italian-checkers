#include <gtest/gtest.h>
#include "engine.h"

using namespace dama;

TEST(InitialPosition, twelve_pieces_each) {
    GameState p = GameState::initial();
    int black = 0, white = 0;
    for (int r = 0; r < kBoardSize; ++r)
        for (int c = 0; c < kBoardSize; ++c) {
            Piece pc = p.getPiece({r, c});
            if (pc == Piece::Black) ++black;
            if (pc == Piece::White) ++white;
        }
    EXPECT_EQ(black, 12);
    EXPECT_EQ(white, 12);
}


TEST(InitialPosition, black)
{
    int nblack = 0;
    GameState p = GameState::initial();
    for (int r = 0; r < 3; r++)
    {
        int offset = ((r % 2) == 0) ? 0 : 1;
        for (int c = offset; c < dama::kBoardSize; c += 2)
        {
            if (p.getPiece({r, c}) == Piece::Black) nblack++;
        }
    }
    EXPECT_EQ(nblack,12);
}

TEST(InitialPosition, white)
{
    int nwhite = 0;
    GameState p = GameState::initial();
    for (int r = 5; r < 8; r++)
    {
        int offset = ((r % 2) != 0) ? 1 : 0;
        for (int c = offset; c < dama::kBoardSize; c += 2)
        {
            if (p.getPiece({r, c}) == Piece::White) nwhite++;
        }
    }
    EXPECT_EQ(nwhite, 12);
}

TEST(SetAndGet, set)
{
    GameState p = GameState::initial();
    p.setPiece(Pos(1, 2), Piece::BlackKing);
    EXPECT_EQ(p.getPiece(Pos(1, 2)), Piece::BlackKing);

}

TEST(SetAndGet, get)
{
    GameState p = GameState::initial();
    EXPECT_EQ(p.getPiece(Pos(6, 0)), Piece::White);

}