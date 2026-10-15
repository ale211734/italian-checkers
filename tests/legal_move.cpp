#include <gtest/gtest.h>
#include "engine.h"
#include <cstdint>

using namespace dama;

static bool isValidateMove(const Move& move_to_check, const std::vector<Move>& moves_list) {
    for (const auto& mr : moves_list) {
        if (move_to_check == mr) return true;
    }
    return false;
}

TEST(MandatoryCapture, findCapture_simple_black) {

    // create a capture scenario
    GameState s;

    s.setPiece(Pos(2, 2), dama::Piece::Black);
    s.setPiece(Pos(3, 3), dama::Piece::White);

    Move m;
    std::vector<Move> moves;
    std::set<Pos> visited;
    m.path.push_back(Pos(2, 2));
    findCapture(s, visited, m, moves);

    EXPECT_EQ(moves.size(), 1);

    auto mr = moves.front();

    EXPECT_TRUE(mr.path.front() == Pos(2, 2));
    EXPECT_TRUE(mr.path.back() == Pos(4, 4));

}

TEST(MandatoryCapture, findCapture_black_simple_branch) {

    // create a capture scenario
    GameState s;

    s.setPiece(Pos(2, 2), dama::Piece::Black);
    s.setPiece(Pos(3, 1), dama::Piece::White);
    s.setPiece(Pos(3, 3), dama::Piece::White);

    Move m1({ Pos(2, 2),Pos(4, 0) }, {Pos(3,1)}, false);
    Move m2({ Pos(2, 2),Pos(4, 4) }, { Pos(3,3) }, false);
      
    
    std::vector<Move> match = {m1,m2};

    Move m;
    m.path.push_back(Pos(2, 2));
    std::vector<Move> result;
    std::set<Pos> visited;
   
    // bisognerebbe rendere unici i risultati cosi non va bene
    findCapture(s, visited, m, result);

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }

    EXPECT_EQ(result.size(), match.size());

}


TEST(MandatoryCapture, findCapture_king_branch) {

    // create a capture scenario
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 1), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 1), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 3), dama::Piece::WhiteKing);

    Move m1({ Pos(4, 2),Pos(2, 0) }, { Pos(3,1) }, false);
    Move m2({ Pos(4, 2),Pos(2, 4) }, { Pos(3,3) }, false);
    Move m3({ Pos(4, 2),Pos(6, 0) }, { Pos(5,1) }, false);
    Move m4({ Pos(4, 2),Pos(6, 4) }, { Pos(5,3) }, false);


    std::vector<Move> match = { m1,m2,m3,m4 };

    Move m;
    m.path.push_back(Pos(4, 2));
    std::vector<Move> result;
    std::set<Pos> visited;

    // bisognerebbe rendere unici i risultati cosi non va bene
    findCapture(s, visited, m, result);

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }

    EXPECT_EQ(result.size(), match.size());

}


TEST(MandatoryCapture, findCapture_king_multicapture) {

    // create a capture scenario
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 5), dama::Piece::WhiteKing);

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(4,6), Pos(6,4)}, {Pos(3,3),Pos(3,5),Pos(5,5) }, false);


    std::vector<Move> match = { m1};

    Move m;
    m.path.push_back(Pos(4, 2));
    std::vector<Move> result;
    std::set<Pos> visited;

    // bisognerebbe rendere unici i risultati cosi non va bene
    findCapture(s, visited, m, result);

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }

    EXPECT_EQ(result.size(), match.size());

}


TEST(MandatoryCapture, findCapture_king_multicapture_multibranch) {

    // create a capture scenario
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 1), dama::Piece::WhiteKing);

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(4,6), Pos(6,4) }, { Pos(3,3),Pos(3,5),Pos(5,5) }, false);
    Move m2({ Pos(4, 2),Pos(2, 0) }, { Pos(3,1) }, false);


    std::vector<Move> match = { m1, m2 };

    Move m;
    m.path.push_back(Pos(4, 2));
    std::vector<Move> result;
    std::set<Pos> visited;

    // bisognerebbe rendere unici i risultati cosi non va bene
    findCapture(s, visited, m, result);

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }

    EXPECT_EQ(result.size(), match.size());

}



TEST(MandatoryCapture, findCapture_king_multicapture_loop) {

    // create a capture scenario
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 3), dama::Piece::WhiteKing);

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(4,6), Pos(6,4), Pos(4, 2) }, { Pos(3,3),Pos(3,5),Pos(5,5),Pos(5,3) }, false);


    std::vector<Move> match = { m1 };

    Move m;
    m.path.push_back(Pos(4, 2));
    std::vector<Move> result;
    std::set<Pos> visited;

    // bisognerebbe rendere unici i risultati cosi non va bene
    findCapture(s, visited, m, result);

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }

    EXPECT_EQ(result.size(), match.size());

}


TEST(MandatoryCapture, findCapture_no_capture1) {
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);

    Move m;
    m.path.push_back(Pos(4, 2));
    std::set<Pos> visited;
    std::vector<Move> result;
    findCapture(s, visited, m, result);
    EXPECT_EQ(result.size(), 0);
}

TEST(MandatoryCapture, findCapture_no_capture2) {
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(5, 3), dama::Piece::BlackKing);

    Move m;
    m.path.push_back(Pos(4, 2));
    std::set<Pos> visited;
    std::vector<Move> result;
    findCapture(s, visited, m, result);
    EXPECT_EQ(result.size(), 0);
}

TEST(MandatoryCapture, findcapture_check_score) {

    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 5), dama::Piece::White);
    s.setPiece(Pos(5, 3), dama::Piece::WhiteKing);

    Move m;
    m.path.push_back(Pos(4, 2));
    std::set<Pos> visited;
    std::vector<Move> result;
    findCapture(s, visited, m, result);

    EXPECT_EQ(result.size(), 1);
    auto m_res = result[0];

    EXPECT_EQ(m_res.numberKingCaptured, 3);
    EXPECT_EQ(m_res.numberNoKingCaptured, 1);
}
