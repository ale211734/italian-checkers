#include "board.h"

namespace dama {

Board Board::initial() {
    Board b;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            if ((r + c) % 2 != 0) continue;
            if (r < 3) b.set({r, c}, Piece::Black);
            else if (r > 4) b.set({r, c}, Piece::White);
        }
    }
    return b;
}

std::string Board::toString() const {
    std::string s;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            Piece pc = get({r, c});
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
