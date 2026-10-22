#pragma once

#include <vector>
#include "board.h"
#include "move.h"

namespace dama {

// Regola italiana della presa obbligatoria: tra le catture possibili si deve
// scegliere quella che, in ordine, cattura piu' pezzi, e' fatta da una dama,
// cattura piu' dame, incontra una dama il prima possibile.
struct CapturePriority {
    int pieces = 0;      // pezzi catturati
    int kings = 0;       // di cui dame
    bool byKing = false; // catturato da una dama
    int firstKing = 0;   // indice della prima dama catturata (== pieces se nessuna)

    static CapturePriority of(const Move& move, const Board& board);

    // Mantiene solo le catture di priorita' massima (a parita' le tiene tutte).
    static std::vector<Move> best(const std::vector<Move>& captures, const Board& board);

    bool operator==(const CapturePriority&) const = default;
    bool operator<(const CapturePriority& o) const;
};

}  // namespace dama
