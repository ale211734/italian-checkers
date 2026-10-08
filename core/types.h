#pragma once

#include <optional>

namespace dama {
enum class Piece { None, Black, White, BlackKing, WhiteKing };
constexpr int kBoardSize = 8;

struct Pos {
    int r = 0, c = 0;

    Pos() = default;
    Pos(int r, int c) : r(r), c(c) {}

    Pos& operator+=(const Pos& other) {
        r += other.r;
        c += other.c;
        return *this;
    }
    Pos& operator-=(const Pos& other) {
        r -= other.r;
        c -= other.c;
        return *this;
    }
    bool operator==(const Pos& other) const { return r == other.r && c == other.c; }

    friend Pos operator+(Pos a, const Pos& b) { a += b; return a; }
    friend Pos operator-(Pos a, const Pos& b) { a -= b; return a; }
};

inline bool isPosInside(Pos p) {
    return p.r >= 0 && p.r < kBoardSize && p.c >= 0 && p.c < kBoardSize;
}

inline std::optional<Pos> getNeighbour(Pos p, Pos offset) {
    Pos next = p + offset;
    if (isPosInside(next)) return next;
    return std::nullopt;
}
}  // namespace dama
