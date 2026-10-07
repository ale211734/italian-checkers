#pragma once

#include <string>
#include <vector>
#include <optional>
#include "game_state.h"

namespace dama {

// GameState is already fully defined via #include "game_state.h"

struct Move {
    int from_r = 0, from_c = 0;
    int to_r = 0, to_c = 0;
    bool capture = false;
    int cap_r = -1, cap_c = -1;
    bool promote = false;
};

class Pos {
public:
    int r, c;
    Pos(int r = 0, int c = 0) : r(r), c(c) {}
    Pos& operator+=(const Pos& other) {
        r += other.r;
        c += other.c;
        return *this;
    }
    bool operator==(const Pos& other) const { return r == other.r && c == other.c; }
};

class Board {
public:
    static bool isPosInside(const Pos& p) {
        return p.r >= 0 && p.r < kBoardSize && p.c >= 0 && p.c < kBoardSize;
    }

    static std::optional<Pos> getNeighbour(const Pos& p, const Pos& offset) {
        Pos next = p;
        next += offset;
        if (isPosInside(next)) {
            return next;
        }
        return std::nullopt;
    }
};

std::vector<Move> legal_moves(const GameState& p, int r, int c);
std::vector<Move> all_legal_moves(const GameState& p);
GameState apply_move(const GameState& p, const Move& m);
bool has_moves(const GameState& p, bool black);
bool is_over(const GameState& p);
std::string to_string(const GameState& p);

}  // namespace dama
