#pragma once

#include "board.h"
#include "move.h"

namespace dama {

class GameState {
public:
    GameState() = default;

    void setPiece(Pos p, Piece pc) { board_.set(p, pc); }
    Piece getPiece(Pos p) const { return board_.get(p); }
    const Board& board() const { return board_; }
    bool blackToMove() const { return black_to_move_; }
    Piece::Color sideToMove() const { return black_to_move_ ? Piece::Color::Black : Piece::Color::White; }

    // Stato risultante dall'applicazione di `move`: sposta il pezzo, rimuove
    // le catture, promuove e cambia il turno. Lo stato corrente non cambia.
    GameState play(const Move& move) const;

    static GameState initial();

private:
    Board board_;
    bool black_to_move_ = true;
};

}  // namespace dama
