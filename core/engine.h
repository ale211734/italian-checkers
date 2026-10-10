#pragma once

#include <string>
#include <vector>
#include <optional>
#include "game_state.h"
#include <set>

namespace dama {

    class Move {
    public:
        Move() = default;
        Move(std::vector<Pos> path, std::vector<Pos> captured = {}, bool promote = false)
            : path(std::move(path)), captured(std::move(captured)), promote(promote) {}
        std::vector<Pos> path;
        std::vector<Pos> captured;
        bool isCaptured() { return !captured.empty(); }
        bool isPromoted() { return promote; }
        Pos from() { return path.front(); };
        Pos to() { return path.back(); };

        // C++20: Genera automaticamente ==, !=, <, <=, >, >=
        auto operator<=>(const Move&) const = default;

        bool promote = false;
    };


    inline std::optional<Pos> getNeighbour(Pos p, Pos offset) {
        Pos next = p + offset;
        if (isPosInside(next)) return next;
        return std::nullopt;
    }

    std::vector<std::optional<Pos>> getNeighbourAll(Pos p, const GameState& g);







    void findCapture(Pos p, GameState& s, std::set<Pos>& visited, Move& m, std::vector<Move>& moves);

    std::vector<Move> legalMove(const GameState& s);


}  // namespace dama
