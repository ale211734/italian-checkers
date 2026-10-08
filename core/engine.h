#pragma once

#include <string>
#include <vector>
#include <optional>
#include "game_state.h"

namespace dama {

    struct Move {
        std::vector<Pos> path;
        std::vector<Pos> captured;
        bool isCaptured() { return !captured.empty(); }
        bool isPromoted() { return promote; }
        bool promote = false;
    };

}  // namespace dama
