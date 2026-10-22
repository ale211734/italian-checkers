#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "game_state.h"

using namespace dama;

namespace {
bool hasDirection(Piece p, Pos d) {
    auto dirs = p.directions();
    return std::find(dirs.begin(), dirs.end(), d) != dirs.end();
}
}  // namespace

TEST(PosTest, operators) {
    Pos p1(1, 1);
    Pos p2(2, 3);
    p1 += p2;
    EXPECT_EQ(p1.r, 3);
    EXPECT_EQ(p1.c, 4);
    EXPECT_TRUE(p1 == Pos(3, 4));
}

TEST(BoardTest, isPosInside) {
    EXPECT_TRUE(isPosInside(Pos(0, 0)));
    EXPECT_TRUE(isPosInside(Pos(7, 7)));
    EXPECT_FALSE(isPosInside(Pos(-1, 0)));
    EXPECT_FALSE(isPosInside(Pos(8, 0)));
}

TEST(BoardTest, set_get_clear) {
    Board b;
    EXPECT_EQ(b.get(Pos(3, 3)), Piece::None);
    b.set(Pos(3, 3), Piece::WhiteKing);
    EXPECT_EQ(b.get(Pos(3, 3)), Piece::WhiteKing);
    b.clear(Pos(3, 3));
    EXPECT_TRUE(b.get(Pos(3, 3)).isEmpty());
}

TEST(PieceTest, black_man_moves_down) {
    EXPECT_EQ(Piece::Black.directions().size(), 2u);
    EXPECT_TRUE(hasDirection(Piece::Black, Pos(1, -1)));
    EXPECT_TRUE(hasDirection(Piece::Black, Pos(1, 1)));
}

TEST(PieceTest, white_man_moves_up) {
    EXPECT_EQ(Piece::White.directions().size(), 2u);
    EXPECT_TRUE(hasDirection(Piece::White, Pos(-1, -1)));
    EXPECT_TRUE(hasDirection(Piece::White, Pos(-1, 1)));
}

TEST(PieceTest, king_moves_in_all_four_directions) {
    for (Piece k : {Piece::BlackKing, Piece::WhiteKing}) {
        EXPECT_EQ(k.directions().size(), 4u);
    }
}

TEST(PieceTest, empty_has_no_directions) {
    EXPECT_TRUE(Piece::None.directions().empty());
}

TEST(PieceTest, capture_rules) {
    EXPECT_TRUE(Piece::Black.canCapture(Piece::White));
    EXPECT_FALSE(Piece::Black.canCapture(Piece::WhiteKing));   // la pedina non prende la dama
    EXPECT_TRUE(Piece::BlackKing.canCapture(Piece::WhiteKing));
    EXPECT_FALSE(Piece::Black.canCapture(Piece::Black));
    EXPECT_FALSE(Piece::Black.canCapture(Piece::None));
}

TEST(PieceTest, promotion) {
    EXPECT_TRUE(Piece::Black.promotesAt(7));
    EXPECT_FALSE(Piece::Black.promotesAt(0));
    EXPECT_TRUE(Piece::White.promotesAt(0));
    EXPECT_FALSE(Piece::BlackKing.promotesAt(7));
    EXPECT_EQ(Piece::Black.promoted(), Piece::BlackKing);
    EXPECT_EQ(Piece::White.promoted(), Piece::WhiteKing);
}
