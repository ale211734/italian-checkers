#include "engine.h"

namespace dama {

namespace {

bool on_board(int r, int c) { return r >= 0 && r < kBoardSize && c >= 0 && c < kBoardSize; }
bool is_black(Piece p) { return p == Piece::Black || p == Piece::BlackKing; }
bool is_white(Piece p) { return p == Piece::White || p == Piece::WhiteKing; }
bool is_king(Piece p) { return p == Piece::BlackKing || p == Piece::WhiteKing; }

}  // namespace

GameState initial_position() {
    GameState p;
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < kBoardSize; ++c)
            if ((r + c) % 2 == 0) p.board[r][c] = Piece::Black;
    for (int r = 5; r < 8; ++r)
        for (int c = 0; c < kBoardSize; ++c)
            if ((r + c) % 2 == 0) p.board[r][c] = Piece::White;
    return p;
}
 
std::vector<Move> legal_moves(const GameState& p, int r, int c) {
    std::vector<Move> moves;
    const Piece pc = p.board[r][c];
    if (pc == Piece::None) return moves;

    const bool black = is_black(pc);
    const bool king = is_king(pc);
    const int dirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (const auto& d : dirs) {
        const int dr = d[0], dc = d[1];
        // I pedoni si muovono solo in avanti; i re in entrambe le direzioni.
        if (!king && !((black && dr > 0) || (!black && dr < 0))) continue;

        const int nr = r + dr, nc = c + dc;
        if (!on_board(nr, nc)) continue;

        const Piece target = p.board[nr][nc];
        if (target == Piece::None) {
            Move m{r, c, nr, nc};
            m.promote = !king && ((black && nr == kBoardSize - 1) || (!black && nr == 0));
            moves.push_back(m);
        } else if ((black && is_white(target)) || (!black && is_black(target))) {
            // Cattura: salto sul pezzo nemico adiacente, atterraggio sulla casa libera.
            const int jr = nr + dr, jc = nc + dc;
            if (on_board(jr, jc) && p.board[jr][jc] == Piece::None) {
                moves.push_back(Move{r, c, jr, jc, true, nr, nc});
            }
        }
    }
    return moves;
}

std::vector<Move> all_legal_moves(const GameState& p) {
    std::vector<Move> moves;
    const bool black = p.black_to_move;
    for (int r = 0; r < kBoardSize; ++r)
        for (int c = 0; c < kBoardSize; ++c) {
            const Piece pc = p.board[r][c];
            if ((black && is_black(pc)) || (!black && is_white(pc))) {
                auto piece_moves = legal_moves(p, r, c);
                moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
            }
        }

    // Regola italiana: la cattura è obbligatoria.
    std::vector<Move> captures;
    for (const auto& m : moves)
        if (m.capture) captures.push_back(m);
    if (!captures.empty()) return captures;
    return moves;
}

GameState apply_move(const GameState& p, const Move& m) {
    GameState q = p;
    Piece pc = q.board[m.from_r][m.from_c];
    q.board[m.from_r][m.from_c] = Piece::None;
    if (m.capture) q.board[m.cap_r][m.cap_c] = Piece::None;
    if (m.promote) pc = is_black(pc) ? Piece::BlackKing : Piece::WhiteKing;
    q.board[m.to_r][m.to_c] = pc;
    q.black_to_move = !q.black_to_move;
    return q;
}

bool has_moves(const GameState& p, bool black) {
    for (int r = 0; r < kBoardSize; ++r)
        for (int c = 0; c < kBoardSize; ++c) {
            const Piece pc = p.board[r][c];
            if ((black && is_black(pc)) || (!black && is_white(pc)))
                if (!legal_moves(p, r, c).empty()) return true;
        }
    return false;
}

bool is_over(const GameState& p) { return !has_moves(p, p.black_to_move); }

std::string to_string(const GameState& p) {
    std::string s;
    for (int r = 0; r < kBoardSize; ++r) {
        for (int c = 0; c < kBoardSize; ++c) {
            switch (p.board[r][c]) {
                case Piece::Black: s += "b "; break;
                case Piece::White: s += "w "; break;
                case Piece::BlackKing: s += "B "; break;
                case Piece::WhiteKing: s += "W "; break;
                default: s += ((r + c) % 2 == 0) ? ". " : "  "; break;
            }
        }
        s += "\n";
    }
    return s;
}

}  // namespace dama
