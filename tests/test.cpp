#include <gtest/gtest.h>

#include "engine.h"

using namespace dama;

TEST(InitialPosition, twelve_pieces_each) {
    Position p = initial_position();
    int black = 0, white = 0;
    for (auto& row : p.board)
        for (Piece pc : row) {
            if (pc == Piece::Black) ++black;
            if (pc == Piece::White) ++white;
        }
    EXPECT_EQ(black, 12);
    EXPECT_EQ(white, 12);
}

TEST(Moves, corner_piece_has_one_move) {
    Position p = initial_position();
    EXPECT_EQ(legal_moves(p, 2, 0).size(), 1u);
}

TEST(Moves, all_legal_moves_nonempty) {
    Position p = initial_position();
    EXPECT_FALSE(all_legal_moves(p).empty());
}
