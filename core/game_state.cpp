#include "game_state.h"

namespace dama {

GameState GameState::initial() {
    GameState gs;
    gs.board_ = Board::initial();
    return gs;
}

GameState GameState::play(const Move& move) const {
    GameState next = *this;
    Piece piece = board_.get(move.from());

    for (const Pos& c : move.captured) next.board_.clear(c);
    next.board_.clear(move.from());

    if (piece.promotesAt(move.to().r)) piece = piece.promoted();
    next.board_.set(move.to(), piece);

    next.black_to_move_ = !black_to_move_;
    return next;
}

}  // namespace dama
