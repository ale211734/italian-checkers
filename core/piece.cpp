#include "piece.h"

#include <array>

namespace dama {

std::span<const Pos> Piece::directions() const {
    static const std::array<Pos, 2> white = {Pos(-1, -1), Pos(-1, 1)};
    static const std::array<Pos, 2> black = {Pos(1, -1), Pos(1, 1)};
    static const std::array<Pos, 4> king = {Pos(-1, -1), Pos(1, -1), Pos(-1, 1), Pos(1, 1)};

    if (isKing()) return king;
    if (isWhite()) return white;
    if (isBlack()) return black;
    return {};
}

}  // namespace dama
