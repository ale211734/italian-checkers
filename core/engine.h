#pragma once

#include <string>
#include <vector>
#include <optional>
#include "game_state.h"
#include <set>

namespace dama {

    class Move {
    public:
        Move() : pieceStart(Piece::None), numberKingCaptured(0), numberNoKingCaptured(0), promote(false) {}
        Move(std::vector<Pos> path, std::vector<Pos> captured = {}, bool promote = false)
            : path(std::move(path)), captured(std::move(captured)), promote(promote), 
              pieceStart(Piece::None), numberKingCaptured(0), numberNoKingCaptured(0) {}
        std::vector<Pos> path;
        std::vector<Pos> captured;
        bool isCaptured() const { return !captured.empty(); }
        bool isPromoted() const { return promote; }
        Pos from() const { return path.front(); };
        Pos to() const { return path.back(); };

        // score need to order the capture moves.
        int score() const;
        
        Piece pieceStart;
        int numberKingCaptured;
        int numberNoKingCaptured;


        // Custom equality: only path and captured matter for move identity
        bool operator==(const Move& other) const {
            return path == other.path && captured == other.captured;
        }

        // C++20: Genera automaticamente <, <=, >, >=
        auto operator<=>(const Move&) const = default;

        bool promote = false;
    };


    inline std::optional<Pos> getNeighbour(Pos p, Pos offset) {
        Pos next = p + offset;
        if (isPosInside(next)) return next;
        return std::nullopt;
    }

    static GameState initial_position();
    static std::string to_string(const GameState& p);
    static void movePiece(GameState& s, Pos source, Pos dest);
    static void orderMoves(std::vector<Move>& moves);
    
    std::vector<std::optional<Pos>> getNeighbourAll(Pos p, const GameState& g);



    void findCapture(GameState& s, std::set<Pos>& visited, Move& m, std::vector<Move>& moves);

    std::vector<Move> legalMove(const GameState& s);


}  // namespace dama
