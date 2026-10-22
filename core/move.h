#pragma once

#include <vector>
#include "types.h"

namespace dama {

// Una mossa e' il percorso del pezzo (casella di partenza compresa) e le
// posizioni dei pezzi avversari catturati lungo il percorso.
struct Move {
    std::vector<Pos> path;
    std::vector<Pos> captured;

    Move() = default;
    Move(std::vector<Pos> path, std::vector<Pos> captured = {})
        : path(std::move(path)), captured(std::move(captured)) {}

    bool isCapture() const { return !captured.empty(); }
    Pos from() const { return path.front(); }
    Pos to() const { return path.back(); }

    bool operator==(const Move&) const = default;
    auto operator<=>(const Move&) const = default;
};

}  // namespace dama
