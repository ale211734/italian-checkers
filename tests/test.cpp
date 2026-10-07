#include <gtest/gtest.h>
#include "engine.h"

using namespace dama;

TEST(InitialPosition, twelve_pieces_each) {
    GameState p = GameState::initial();
    int black = 0, white = 0;
    for (auto& row : p.board)
        for (Piece pc : row) {
            if (pc == Piece::Black) ++black;
            if (pc == Piece::White) ++white;
        }
    EXPECT_EQ(black, 12);
    EXPECT_EQ(white, 12);
}

TEST(InitialPosition, black_pieces) {
    GameState p = GameState::initial();
    int black = 0, white = 0;
    for (auto& row : p.board)
        for (Piece pc : row) {
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
            if (p.board[r][c] == Piece::Black) nblack++;
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
            if (p.board[r][c] == Piece::White) nwhite++;
        }
    }
    EXPECT_EQ(nwhite, 12);
}