#pragma once

#include <array>
#include <string>
#include "piece.h"
#include "types.h"

namespace dama {

// Griglia 8x8 di pezzi, senza nozione di turno.
class Board {
public:
    Board() = default;

    static Board initial();

    Piece get(Pos p) const { return cells_[p.r][p.c]; }
    void set(Pos p, Piece pc) { cells_[p.r][p.c] = pc; }
    void clear(Pos p) { set(p, Piece::None); }

    std::string toString() const;

private:
    std::array<std::array<Piece, kBoardSize>, kBoardSize> cells_{};
};

}  // namespace dama
