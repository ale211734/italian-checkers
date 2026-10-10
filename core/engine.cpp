#include "engine.h"

namespace dama {

namespace {

    bool on_board(int r, int c) { return r >= 0 && r < kBoardSize && c >= 0 && c < kBoardSize; }
    bool is_black(Piece p) { return p == Piece::Black || p == Piece::BlackKing; }
    bool is_white(Piece p) { return p == Piece::White || p == Piece::WhiteKing; }
    bool is_king(Piece p)  { return p == Piece::BlackKing || p == Piece::WhiteKing; }
    bool is_empty(Piece p) { return p == Piece::None; };
    bool is_opposite(Piece p, Piece q) { 
        return ((is_black(p) && is_white(q)) || (is_white(p) && is_black(q)));
    };

    bool canPromote(Pos source, Pos dest, const GameState & p)
    {
        auto piece     = p.getPiece(source);
        if (is_king(piece)) return false;
        auto pieceDest = p.getPiece(dest);
        if (is_empty(pieceDest))
        {
            if (is_white(piece) && (dest.r == 0)) return true;
            else if (is_black(piece) && (dest.r == 7)) return true;
        }
        return false;
    }


    }  // namespace

    GameState initial_position() {
        GameState p;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < kBoardSize; ++c)
                if ((r + c) % 2 == 0) p.setPiece({r, c}, Piece::Black);
        for (int r = 5; r < 8; ++r)
            for (int c = 0; c < kBoardSize; ++c)
                if ((r + c) % 2 == 0) p.setPiece({r, c}, Piece::White);
        return p;
    }
 
    std::string to_string(const GameState& p) {
        std::string s;
        for (int r = 0; r < kBoardSize; ++r) {
            for (int c = 0; c < kBoardSize; ++c) {
                switch (p.getPiece({r, c})) {
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


    std::vector<std::optional<Pos>> getNeighbourAll(Pos p, const GameState& g)
    {
        std::vector<std::optional<Pos>> neighbours;

        // Riferimenti statici per non ricreare i vettori a ogni chiamata
        static const std::vector<Pos> posWhite = { Pos(-1,-1), Pos(-1,1) };
        static const std::vector<Pos> posBlack = { Pos(1,-1) ,Pos(1,1) };
        static const std::vector<Pos> posKing = { Pos(-1,-1), Pos(1,-1), Pos(-1,1), Pos(1,1) };

        const auto& piece = g.getPiece(p);
        const std::vector<Pos>* selectedPos = nullptr;

        // 1. Controlla PRIMA se è un re
        if (is_king(piece)) {
            selectedPos = &posKing;
        }
        else if (is_white(piece)) {
            selectedPos = &posWhite;
        }
        else if (is_black(piece)) {
            selectedPos = &posBlack;
        }

        // Se la casella è vuota o il pezzo non è valido, ritorna vuoto
        if (!selectedPos) {
            return neighbours;
        }

        // 2. Cicla direttamente sulle coordinate corrette senza duplicarle
        for (const auto& n : *selectedPos) {
            neighbours.push_back(getNeighbour(p, n));
        }

        return neighbours;
    }

    void movePiece(GameState& s, Pos source, Pos dest)
    {
        s.setPiece(dest, s.getPiece(source));
        s.setPiece(source, Piece::None);
    }


    void findCapture(GameState& s, std::set<Pos> & visited, Move & m, std::vector<Move> & moves)
    {
        Pos p = m.path.back();
        auto positions = getNeighbourAll(p, s); // da distinguere per pedina e dama
        visited.insert(p);
        auto piece = s.getPiece(p);
        int newCapture = 0;
        for (auto pos: positions)
        {
            Pos offset(0,0);
            if (pos.has_value())
            {
                offset = pos.value() - p;
                auto nextPiece = s.getPiece(pos.value());
                if (is_empty(nextPiece) ) continue; // no capture possible
           
                auto jumpPos = pos.value() + offset;
                auto jumpPiece = s.getPiece(jumpPos);
                bool stateChange = false;
                if (is_opposite(piece, nextPiece) && is_empty(jumpPiece))
                {
                    if (!is_king(piece) && is_king(nextPiece)) continue;
                    if ((visited.find(jumpPos) == visited.end()) || (jumpPos == m.path.front()))
                    {
                        m.path.push_back(jumpPos);
                        m.captured.push_back(pos.value());
                        movePiece(s, p, jumpPos);
                        findCapture(s, visited, m, moves);
                        stateChange = true;
                        newCapture++;
                    }
                }
                else 
                {
                    // finiti i capture
                    moves.push_back(m);
                    if (canPromote(m.path.front(), m.path.back(), s))
                    {
                        m.promote = true;
                    }
                }
                // backpropagation step
                if (m.path.back() == jumpPos)
                {
                    m.path.pop_back();
                    m.captured.pop_back();
                    s.setPiece(p, dama::Piece::None);
                    if (stateChange) movePiece(s, jumpPos, p);
                }
                    
                
            }
                 
        }
        // no new capture movements
        if (newCapture == 0)
        {
            // finiti i capture
            moves.push_back(m);
            if (canPromote(m.path.front(), m.path.back(), s))
            {
                m.promote = true;
            }
        }
    }

    std::vector<Move> legalMove(const GameState& s)
    {
        GameState scopy = s;
        std::vector<Move> result;
        for (int r = 0; r < kBoardSize; r++)
        {
            for (int c = 0; c < kBoardSize; c++)
            {
                auto p = s.getPiece(Pos(r, c));
                if (s.blackToMove() && is_black(p))
                {
                    Move m;
                    m.path.push_back(Pos(r, c));
                    std::vector<Move> moves;
                    std::set<Pos> visited;
                    findCapture(scopy, visited, m, moves);

                    if (!moves.empty()) // there are some captures
                    {
                        Move m;
                        //m.captured = true;
                    }
                }
                
                else if (!s.blackToMove() && is_white(p))
                {
                }
            }
        }
        return std::vector<Move>();
    }

}  // namespace dama
