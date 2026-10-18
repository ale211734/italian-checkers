#pragma once

#include <string>
#include <vector>
#include <optional>
#include "game_state.h"
#include "move_generator.h"
#include <set>

namespace dama {

    static GameState initial_position();
    static std::string to_string(const GameState& p);

}  // namespace dama
