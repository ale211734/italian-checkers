#include <gtest/gtest.h>
#include "move_generator.h"
#include <algorithm>
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
    auto moves = MoveGenerator(s).capturesFrom(Pos(2, 2));

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

    Move m1({ Pos(2, 2),Pos(4, 0) }, {Pos(3,1)});
    Move m2({ Pos(2, 2),Pos(4, 4) }, { Pos(3,3) });
      
    
    std::vector<Move> match = {m1,m2};
   
    // bisognerebbe rendere unici i risultati cosi non va bene
    auto result = MoveGenerator(s).capturesFrom(Pos(2, 2));

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

    Move m1({ Pos(4, 2),Pos(2, 0) }, { Pos(3,1) });
    Move m2({ Pos(4, 2),Pos(2, 4) }, { Pos(3,3) });
    Move m3({ Pos(4, 2),Pos(6, 0) }, { Pos(5,1) });
    Move m4({ Pos(4, 2),Pos(6, 4) }, { Pos(5,3) });


    std::vector<Move> match = { m1,m2,m3,m4 };

    // bisognerebbe rendere unici i risultati cosi non va bene
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));

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

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(4,6), Pos(6,4)}, {Pos(3,3),Pos(3,5),Pos(5,5) });


    std::vector<Move> match = { m1};

    // bisognerebbe rendere unici i risultati cosi non va bene
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));

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

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(4,6), Pos(6,4) }, { Pos(3,3),Pos(3,5),Pos(5,5) });
    Move m2({ Pos(4, 2),Pos(2, 0) }, { Pos(3,1) });


    std::vector<Move> match = { m1, m2 };

    // bisognerebbe rendere unici i risultati cosi non va bene
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));

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

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(4,6), Pos(6,4), Pos(4, 2) }, { Pos(3,3),Pos(3,5),Pos(5,5),Pos(5,3) });
    // lo stesso giro in senso opposto e' una sequenza distinta e altrettanto valida
    Move m2({ Pos(4, 2),Pos(6, 4), Pos(4,6), Pos(2,4), Pos(4, 2) }, { Pos(5,3),Pos(5,5),Pos(3,5),Pos(3,3) });


    std::vector<Move> match = { m1, m2 };

    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }

    EXPECT_EQ(result.size(), match.size());

}


TEST(MandatoryCapture, findCapture_no_capture1) {
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));
    EXPECT_EQ(result.size(), 0);
}

TEST(MandatoryCapture, findCapture_no_capture2) {
    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(5, 3), dama::Piece::BlackKing);
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));
    EXPECT_EQ(result.size(), 0);
}

TEST(MandatoryCapture, findcapture_check_score) {

    GameState s;

    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 5), dama::Piece::White);
    s.setPiece(Pos(5, 3), dama::Piece::WhiteKing);
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));

    // il giro si puo' fare nei due versi, con la stessa priorita'
    ASSERT_EQ(result.size(), 2);
    for (const Move& m_res : result) {
        auto pr = CapturePriority::of(m_res, s.board());
        EXPECT_EQ(pr.kings, 3);
        EXPECT_EQ(pr.pieces - pr.kings, 1);
    }
}


TEST(MandatoryCapture, findcapture_check_score2) {
    GameState s;
    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 1), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 3), dama::Piece::White);

    Move m1({ Pos(4, 2),Pos(2, 0) }, { Pos(3,1) });


    std::vector<Move> match = { m1 };
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));


    EXPECT_EQ(result.size(), 2);

    EXPECT_EQ(CapturePriority::of(result[0], s.board()).kings, 1);
    EXPECT_EQ(CapturePriority::of(result[0], s.board()).pieces - CapturePriority::of(result[0], s.board()).kings, 0);

    EXPECT_EQ(CapturePriority::of(result[1], s.board()).kings, 0);
    EXPECT_EQ(CapturePriority::of(result[1], s.board()).pieces - CapturePriority::of(result[1], s.board()).kings, 1);
}


TEST(MandatoryCapture, legal_move_take_max_number_piece) {
    GameState s;
    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 1), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 5), dama::Piece::WhiteKing);
    s.setPiece(Pos(5, 5), dama::Piece::White);
    s.setPiece(Pos(5, 3), dama::Piece::WhiteKing);

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(4,6), Pos(6,4), Pos(4, 2), Pos(2, 0) }, { Pos(3,3),Pos(3,5),Pos(5,5),Pos(5,3),Pos(3,1) });
    // lo stesso giro in senso opposto e' una sequenza distinta e altrettanto valida
    Move m2({ Pos(4, 2),Pos(6, 4), Pos(4,6), Pos(2,4), Pos(4, 2), Pos(2, 0) }, { Pos(5,3),Pos(5,5),Pos(3,5),Pos(3,3),Pos(3,1) });


    std::vector<Move> match = { m1, m2 };
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));
    result = CapturePriority::best(result, s.board());

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }
}


TEST(MandatoryCapture, legal_move_priority_king_over_piece) {
    GameState s;
    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 1), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 3), dama::Piece::White);

    Move m1({ Pos(4, 2),Pos(2, 0) }, { Pos(3,1) });


    std::vector<Move> match = { m1 };
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));
    result = CapturePriority::best(result, s.board());

    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }
}


TEST(MandatoryCapture, legal_move_priority_king_over_piece2) {
    GameState s;
    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(3, 1), dama::Piece::WhiteKing);
    s.setPiece(Pos(1, 1), dama::Piece::White);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(1, 5), dama::Piece::WhiteKing);
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));
    result = CapturePriority::best(result, s.board());

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(0,6)}, { Pos(3, 3), Pos(1, 5) });
    std::vector<Move> match = { m1 };


    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }
}

TEST(MandatoryCapture, legal_move_same_number_and_priority_first_king) {
    GameState s;
    s.setPiece(Pos(4, 2), dama::Piece::BlackKing);
    s.setPiece(Pos(1, 1), dama::Piece::WhiteKing);
    s.setPiece(Pos(3, 1), dama::Piece::White);
    s.setPiece(Pos(3, 3), dama::Piece::WhiteKing);
    s.setPiece(Pos(1, 5), dama::Piece::WhiteKing);
    auto result = MoveGenerator(s).capturesFrom(Pos(4, 2));
    result = CapturePriority::best(result, s.board());

    Move m1({ Pos(4, 2),Pos(2, 4), Pos(0,6) }, { Pos(3, 3), Pos(1, 5) });
    std::vector<Move> match = { m1 };


    for (auto r : result)
    {
        EXPECT_TRUE(isValidateMove(r, match));
    }
}
TEST(LegalMoves, initial_position_has_seven_simple_moves_per_side) {
    GameState s = GameState::initial();
    EXPECT_EQ(MoveGenerator(s).legalMoves().size(), 7);

    // dopo una mossa del nero tocca al bianco, che ha a sua volta 7 mosse
    GameState next = s.play(MoveGenerator(s).legalMoves().front());
    EXPECT_FALSE(next.blackToMove());
    EXPECT_EQ(MoveGenerator(next).legalMoves().size(), 7);
}

TEST(LegalMoves, white_man_moves_forward_only) {
    GameState s = GameState::initial();
    s = s.play(MoveGenerator(s).legalMoves().front());   // turno del bianco

    for (const Move& m : MoveGenerator(s).legalMoves()) {
        EXPECT_LT(m.to().r, m.from().r);
    }
}

TEST(LegalMoves, capture_is_mandatory) {
    GameState s;
    s.setPiece(Pos(2, 2), Piece::Black);
    s.setPiece(Pos(3, 3), Piece::White);
    s.setPiece(Pos(0, 0), Piece::Black);   // avrebbe una mossa semplice

    auto moves = MoveGenerator(s).legalMoves();
    ASSERT_EQ(moves.size(), 1);
    EXPECT_EQ(moves[0], Move({ Pos(2, 2), Pos(4, 4) }, { Pos(3, 3) }));
}

TEST(LegalMoves, white_capture_is_found) {
    GameState s;
    s.setPiece(Pos(4, 4), Piece::White);
    s.setPiece(Pos(3, 3), Piece::Black);
    s.setPiece(Pos(0, 0), Piece::Black);
    s = s.play(Move({ Pos(0, 0), Pos(1, 1) }));   // passa il turno al bianco

    auto moves = MoveGenerator(s).legalMoves();
    // dopo il primo salto la pedina prosegue su (1,1)
    ASSERT_EQ(moves.size(), 1);
    EXPECT_EQ(moves[0], Move({ Pos(4, 4), Pos(2, 2), Pos(0, 0) }, { Pos(3, 3), Pos(1, 1) }));
}

TEST(LegalMoves, man_cannot_capture_king) {
    GameState s;
    s.setPiece(Pos(2, 2), Piece::Black);
    s.setPiece(Pos(3, 3), Piece::WhiteKing);

    EXPECT_TRUE(MoveGenerator(s).capturesFrom(Pos(2, 2)).empty());
}

TEST(LegalMoves, equal_priority_captures_are_all_kept) {
    GameState s;
    s.setPiece(Pos(4, 2), Piece::Black);
    s.setPiece(Pos(5, 1), Piece::White);
    s.setPiece(Pos(5, 3), Piece::White);

    EXPECT_EQ(MoveGenerator(s).legalMoves().size(), 2);
}

TEST(LegalMoves, same_piece_reached_by_two_paths_is_captured_once) {
    // la dama puo' prendere (3,3) e (3,5) in entrambi gli ordini? No: la ricerca
    // deve comunque non contare due volte lo stesso pezzo in un percorso.
    GameState s;
    s.setPiece(Pos(4, 2), Piece::BlackKing);
    s.setPiece(Pos(3, 3), Piece::WhiteKing);
    s.setPiece(Pos(3, 5), Piece::WhiteKing);
    s.setPiece(Pos(5, 5), Piece::WhiteKing);
    s.setPiece(Pos(5, 3), Piece::WhiteKing);

    for (const Move& m : MoveGenerator(s).capturesFrom(Pos(4, 2))) {
        auto c = m.captured;
        std::sort(c.begin(), c.end());
        EXPECT_EQ(std::adjacent_find(c.begin(), c.end()), c.end());
    }
}
