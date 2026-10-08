#include "game_state.h"

namespace dama {

    void GameState::setPiece(Pos p, Piece pc) { board[p.r][p.c] = pc; }
    Piece GameState::getPiece(Pos p) const { return board[p.r][p.c]; }

    GameState GameState::initial() {
        GameState gs;
        // Implementazione logica iniziale:
        // Nere (Black) in alto (righe 0-2), Bianche (White) in basso (righe 5-7).
        for (int r = 0; r < kBoardSize; ++r) {
            for (int c = 0; c < kBoardSize; ++c) {
                if ((r + c) % 2 == 0) {
                    if (r < 3) gs.board[r][c] = Piece::Black;
                    else if (r > 4) gs.board[r][c] = Piece::White;
                    else gs.board[r][c] = Piece::None;
                } else {
                    gs.board[r][c] = Piece::None;
                }
            }
        }
        gs.black_to_move = true;
        return gs;
    }

}  // namespace dama
