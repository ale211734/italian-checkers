#pragma once

#include <array>
#include "types.h"

namespace dama {

struct GameState {
    // board 8x8 of piece
    std::array<std::array<Piece, kBoardSize>, kBoardSize> board{};
    bool black_to_move = true;

    static GameState initial();
};
}
