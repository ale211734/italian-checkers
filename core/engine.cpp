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
                Piece pc = p.getPiece({r, c});
                if (pc == Piece::Black) s += "b ";
                else if (pc == Piece::White) s += "w ";
                else if (pc == Piece::BlackKing) s += "B ";
                else if (pc == Piece::WhiteKing) s += "W ";
                else s += ((r + c) % 2 == 0) ? ". " : "  ";
            }
            s += "\n";
        }
        return s;
    }

}  // namespace dama
