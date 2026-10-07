#include <gtest/gtest.h>
#include "engine.h"

using namespace dama;

TEST(PosTest, operators) {
    Pos p1(1, 1);
    Pos p2(2, 3);
    p1 += p2;
    EXPECT_EQ(p1.r, 3);
    EXPECT_EQ(p1.c, 4);
    EXPECT_TRUE(p1 == Pos(3, 4));
}

TEST(BoardTest, isPosInside) {
    EXPECT_TRUE(Board::isPosInside(Pos(0, 0)));
    EXPECT_TRUE(Board::isPosInside(Pos(7, 7)));
    EXPECT_FALSE(Board::isPosInside(Pos(-1, 0)));
    EXPECT_FALSE(Board::isPosInside(Pos(8, 0)));
}

TEST(BoardTest, getNeighbour) {
    Pos p(4, 4);
    Pos offset(-1, -1);
    
    auto result = Board::getNeighbour(p, offset);
    EXPECT_TRUE(result.has_value());
    EXPECT_TRUE(result.value() == Pos(3, 3));

    // Test out of bounds
    Pos edge(0, 0);
    Pos bad_offset(-1, 0);
    auto bad_result = Board::getNeighbour(edge, bad_offset);
    EXPECT_FALSE(bad_result.has_value());

    // Test out of bounds
    Pos edgeTop(7, 7);
    Pos bad_offset2(1, 1);
    auto res = Board::getNeighbour(edgeTop, bad_offset2);
    EXPECT_FALSE(res.has_value());
}
