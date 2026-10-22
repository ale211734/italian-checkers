#pragma once

#include <vector>
#include "capture_priority.h"
#include "game_state.h"
#include "move.h"

namespace dama {

// Genera le mosse legali del lato al tratto in uno stato dato.
class MoveGenerator {
public:
    explicit MoveGenerator(const GameState& state) : state_(state) {}

    // Se c'e' una presa e' obbligatoria (solo le piu' prioritarie), altrimenti le mosse semplici.
    std::vector<Move> legalMoves() const;

    // Tutte le sequenze massimali di cattura del lato al tratto.
    std::vector<Move> captures() const;

    // Sequenze massimali di cattura del pezzo in `from` (qualunque colore abbia).
    std::vector<Move> capturesFrom(Pos from) const;

    std::vector<Move> simpleMoves() const;

private:
    void extendCapture(Piece mover, Move partial, std::vector<Move>& out) const;

    const GameState& state_;
};

}  // namespace dama
