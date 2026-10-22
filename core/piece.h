#pragma once

#include <span>
#include "types.h"

namespace dama {

class Piece {
public:
    enum class Color { None, Black, White };
    enum class Kind { Man, King };

    constexpr Piece() = default;
    constexpr Piece(Color color, Kind kind) : color_(color), kind_(kind) {}

    static const Piece None, Black, White, BlackKing, WhiteKing;

    constexpr Color color() const { return color_; }
    constexpr bool isEmpty() const { return color_ == Color::None; }
    constexpr bool isBlack() const { return color_ == Color::Black; }
    constexpr bool isWhite() const { return color_ == Color::White; }
    constexpr bool isKing() const { return !isEmpty() && kind_ == Kind::King; }

    constexpr bool isOpponentOf(Piece other) const {
        return !isEmpty() && !other.isEmpty() && color_ != other.color_;
    }

    // Una pedina semplice non puo' catturare una dama.
    constexpr bool canCapture(Piece target) const {
        return isOpponentOf(target) && (isKing() || !target.isKing());
    }

    // Direzioni di movimento: avanti per la pedina, tutte e quattro per la dama.
    std::span<const Pos> directions() const;

    // Riga di promozione: nera in fondo (7), bianca in cima (0).
    constexpr bool promotesAt(int row) const {
        if (isEmpty() || isKing()) return false;
        return row == (isBlack() ? kBoardSize - 1 : 0);
    }
    constexpr Piece promoted() const { return Piece(color_, Kind::King); }

    constexpr bool operator==(const Piece&) const = default;

private:
    Color color_ = Color::None;
    Kind kind_ = Kind::Man;
};

inline constexpr Piece Piece::None{};
inline constexpr Piece Piece::Black{Color::Black, Kind::Man};
inline constexpr Piece Piece::White{Color::White, Kind::Man};
inline constexpr Piece Piece::BlackKing{Color::Black, Kind::King};
inline constexpr Piece Piece::WhiteKing{Color::White, Kind::King};

}  // namespace dama
