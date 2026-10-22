#include "move_generator.h"

#include <algorithm>

namespace dama {

std::vector<Move> MoveGenerator::legalMoves() const {
    std::vector<Move> caps = captures();
    if (!caps.empty()) return CapturePriority::best(caps, state_.board());
    return simpleMoves();
}

std::vector<Move> MoveGenerator::captures() const {
    std::vector<Move> result;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            Pos from(r, c);
            if (state_.getPiece(from).color() != state_.sideToMove()) continue;
            std::vector<Move> moves = capturesFrom(from);
            result.insert(result.end(), moves.begin(), moves.end());
        }
    }
    return result;
}

std::vector<Move> MoveGenerator::capturesFrom(Pos from) const {
    std::vector<Move> result;
    extendCapture(state_.getPiece(from), Move({from}), result);
    return result;
}

std::vector<Move> MoveGenerator::simpleMoves() const {
    std::vector<Move> result;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            Pos from(r, c);
            Piece piece = state_.getPiece(from);
            if (piece.color() != state_.sideToMove()) continue;
            for (const Pos& dir : piece.directions()) {
                Pos to = from + dir;
                if (isPosInside(to) && state_.getPiece(to).isEmpty()) {
                    result.emplace_back(std::vector<Pos>{from, to});
                }
            }
        }
    }
    return result;
}

// Ricerca in profondita': il pezzo che muove non e' mai spostato sulla scacchiera
// e quelli catturati restano dov'erano fino a fine mossa (non si saltano due volte
// e occupano la casella). Per questo la scacchiera non cambia durante la ricerca e
// solo il percorso parziale viene copiato a ogni salto.
void MoveGenerator::extendCapture(Piece mover, Move partial, std::vector<Move>& out) const {
    const Pos at = partial.to();
    const Board& board = state_.board();
    bool extended = false;

    for (const Pos& dir : mover.directions()) {
        const Pos over = at + dir;
        const Pos land = over + dir;
        if (!isPosInside(land)) continue;
        if (!mover.canCapture(board.get(over))) continue;
        if (!board.get(land).isEmpty() && land != partial.from()) continue;
        if (std::ranges::find(partial.captured, over) != partial.captured.end()) continue;

        Move next = partial;
        next.path.push_back(land);
        next.captured.push_back(over);
        extendCapture(mover, std::move(next), out);
        extended = true;
    }

    if (!extended && partial.path.size() > 1) out.push_back(std::move(partial));
}

}  // namespace dama
