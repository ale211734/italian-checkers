#pragma once

#include <array>
#include "types.h"

namespace dama {

class GameState {
public:
    GameState() = default;

    void setPiece(Pos p, Piece pc);
    Piece getPiece(Pos p) const;
    bool blackToMove() const { return black_to_move; }

    static GameState initial();

private:
    // board 8x8 of piece
    std::array<std::array<Piece, kBoardSize>, kBoardSize> board{};
    bool black_to_move = true;
};

}  // namespace dama
