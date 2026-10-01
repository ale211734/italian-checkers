#pragma once

#include <array>
#include <string>
#include <vector>

namespace dama {

enum class Piece { None, Black, White, BlackKing, WhiteKing };

constexpr int kBoardSize = 8;

struct Position {
    std::array<std::array<Piece, kBoardSize>, kBoardSize> board{};
    bool black_to_move = true;
};

struct Move {
    int from_r = 0, from_c = 0;
    int to_r = 0, to_c = 0;
    bool capture = false;
    int cap_r = -1, cap_c = -1;
    bool promote = false;
};

// Posizione iniziale: nere in alto (righe 0-2), bianche in basso (righe 5-7).
Position initial_position();

// Mosse legali di un singolo pezzo in (r, c).
std::vector<Move> legal_moves(const Position& p, int r, int c);

// Tutte le mosse legali del giocatore al turno (cattura obbligatoria, regole italiane).
std::vector<Move> all_legal_moves(const Position& p);

// Applica una mossa e passa il turno.
Position apply_move(const Position& p, const Move& m);

// Il giocatore indicato ha almeno una mossa?
bool has_moves(const Position& p, bool black);

// Partita finita se il giocatore al turno non ha mosse.
bool is_over(const Position& p);

// Rappresentazione testuale della scacchiera (per il CLI).
std::string to_string(const Position& p);

}  // namespace dama
