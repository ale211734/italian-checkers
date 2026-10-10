#include <gtest/gtest.h>
#include "engine.h"
#include <cstdint>

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
    EXPECT_TRUE(isPosInside(Pos(0, 0)));
    EXPECT_TRUE(isPosInside(Pos(7, 7)));
    EXPECT_FALSE(isPosInside(Pos(-1, 0)));
    EXPECT_FALSE(isPosInside(Pos(8, 0)));
}

TEST(BoardTest, getNeighbour) {
    Pos p(4, 4);
    Pos offset(-1, -1);
    
    auto result = getNeighbour(p, offset);
    EXPECT_TRUE(result.has_value());
    EXPECT_TRUE(result.value() == Pos(3, 3));

    // Test out of bounds
    Pos edge(0, 0);
    Pos bad_offset(-1, 0);
    auto bad_result = getNeighbour(edge, bad_offset);
    EXPECT_FALSE(bad_result.has_value());

    // Test out of bounds
    Pos edgeTop(7, 7);
    Pos bad_offset2(1, 1);
    auto res = getNeighbour(edgeTop, bad_offset2);
    EXPECT_FALSE(res.has_value());
}

TEST(BoardTest, getNeighbourAll_black) {
    
    GameState s = dama::GameState::initial();
    
    Pos p1(2, 2);
    std::vector<Pos> nearb1 = { Pos(3,1), Pos(3,3) };

    Pos p2(2, 0);
    std::vector<Pos> nearb2 = { Pos(3,1) };

    Pos p3(1, 7);
    std::vector<Pos> nearb3 = { Pos(2,6) };
  

    std::vector<Pos> startPos = { p1,p2,p3 };
    std::vector<std::vector<Pos>> results_match = { nearb1, nearb2, nearb3 };

    auto linearConversion = [](int r, int c)->uint64_t
    {
        return r * 8 + c;
    };

    for (int i=0;i<startPos.size();i++)
    {
        uint64_t check = 0;
        int size = 0;
        auto result = getNeighbourAll(startPos[i], s);
        for (auto r : result)
        {
            if (r.has_value())
            {
                uint64_t val = linearConversion(r.value().r, r.value().c);
                assert(val < 63);
                check = check | (1 << val);
                size++;
            }
        }

        // check result
        for (auto n : results_match[i])
        {
            uint64_t val = linearConversion(n.r, n.c);

            EXPECT_EQ(results_match[i].size(), size);
            EXPECT_TRUE(check & (1 << val));
        }


    }
}


TEST(BoardTest, getNeighbourAll_white) {

    GameState s = dama::GameState::initial();

    Pos p1(6, 0);
    std::vector<Pos> nearb1 = { Pos(5,1)};

    Pos p2(5, 1);
    std::vector<Pos> nearb2 = { Pos(4,0), Pos(4,2)};

    Pos p3(5, 7);
    std::vector<Pos> nearb3 = { Pos(4,6) };


    std::vector<Pos> startPos = { p1,p2,p3 };
    std::vector<std::vector<Pos>> results_match = { nearb1, nearb2, nearb3 };

    auto linearConversion = [](int r, int c)->uint64_t
        {
            return r * 8 + c;
        };

    for (int i = 0; i < startPos.size(); i++)
    {
        uint64_t check = 0;
        int size = 0;
        auto result = getNeighbourAll(startPos[i], s);
        for (auto r : result)
        {
            if (r.has_value())
            {
                uint64_t val = linearConversion(r.value().r, r.value().c);
                assert(val < 63);
                check = check | (1 << val);
                size++;
            }
        }

        // check result
        for (auto n : results_match[i])
        {
            uint64_t val = linearConversion(n.r, n.c);

            EXPECT_EQ(results_match[i].size(), size);
            EXPECT_TRUE(check & (1 << val));
        }


    }
}


TEST(BoardTest, getNeighbourAll_king) {

    GameState s;

    s.setPiece(Pos(1, 1), Piece::BlackKing);
    s.setPiece(Pos(5, 7), Piece::BlackKing);
    s.setPiece(Pos(7, 7), Piece::BlackKing);

    Pos p1(1, 1);
    std::vector<Pos> nearb1 = { Pos(0,0), Pos(0,2), Pos(2,0), Pos(2,2) };

    Pos p2(5, 7);
    std::vector<Pos> nearb2 = { Pos(4,6), Pos(6,6) };

    Pos p3(7, 7);
    std::vector<Pos> nearb3 = { Pos(6,6)};


    std::vector<Pos> startPos = { p1,p2,p3 };
    std::vector<std::vector<Pos>> results_match = { nearb1, nearb2, nearb3 };

    auto linearConversion = [](int r, int c)->uint64_t
        {
            return r * 8 + c;
        };

    for (int i = 0; i < startPos.size(); i++)
    {
        uint64_t check = 0;
        int size = 0;
        auto result = getNeighbourAll(startPos[i], s);
        for (auto r : result)
        {
            if (r.has_value())
            {
                uint64_t val = linearConversion(r.value().r, r.value().c);
                assert(val < 63);
                check = check | (1 << val);
                size++;
            }
        }

        // check result
        for (auto n : results_match[i])
        {
            uint64_t val = linearConversion(n.r, n.c);

            EXPECT_EQ(results_match[i].size(), size);
            EXPECT_TRUE(check & (1 << val));
        }


    }
}
