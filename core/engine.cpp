#include "engine.h"
#include "rules.h"
#include "move_generator.h"

namespace dama {

    GameState initial_position() {
        GameState p;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < kBoardSize; ++c)
                if ((r + c) % 2 == 0) p.setPiece({r, c}, Piece::Black);
        for (int r = 5; r < 8; ++r)
            for (int c = 0; c < kBoardSize; ++c)
                if ((r + c) % 2 == 0) p.setPiece({r, c}, Piece::White);
        return p;
    }
 
    std::string to_string(const GameState& p) {
        std::string s;
        for (int r = 0; r < kBoardSize; ++r) {
            for (int c = 0; c < kBoardSize; ++c) {
                switch (p.getPiece({r, c})) {
                    case Piece::Black: s += "b "; break;
                    case Piece::White: s += "w "; break;
                    case Piece::BlackKing: s += "B "; break;
                    case Piece::WhiteKing: s += "W "; break;
                    default: s += ((r + c) % 2 == 0) ? ". " : "  "; break;
                }
            }
            s += "\n";
        }
        return s;
    }

}  // namespace dama
