#include "capture_priority.h"

#include <algorithm>
#include <tuple>

namespace dama {

CapturePriority CapturePriority::of(const Move& move, const Board& board) {
    CapturePriority p;
    p.pieces = static_cast<int>(move.captured.size());
    p.firstKing = p.pieces;
    p.byKing = board.get(move.from()).isKing();

    for (int i = 0; i < p.pieces; ++i) {
        if (!board.get(move.captured[i]).isKing()) continue;
        if (p.kings == 0) p.firstKing = i;
        ++p.kings;
    }
    return p;
}

bool CapturePriority::operator<(const CapturePriority& o) const {
    // una dama incontrata prima e' meglio, quindi firstKing e' confrontato al contrario
    return std::tie(pieces, byKing, kings, o.firstKing) <
           std::tie(o.pieces, o.byKing, o.kings, firstKing);
}

std::vector<Move> CapturePriority::best(const std::vector<Move>& captures, const Board& board) {
    std::vector<CapturePriority> priorities;
    for (const Move& m : captures) priorities.push_back(of(m, board));
    if (priorities.empty()) return {};

    const CapturePriority top = *std::max_element(priorities.begin(), priorities.end());

    std::vector<Move> result;
    for (size_t i = 0; i < captures.size(); ++i) {
        if (priorities[i] == top) result.push_back(captures[i]);
    }
    return result;
}

}  // namespace dama
