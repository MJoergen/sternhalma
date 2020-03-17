#include <algorithm>
#include "ai.h"

CMove CAI::getMove() const
{
    std::vector<CMove> moves = m_board.getLegalMoves(P_O);

    std::sort(moves.begin(), moves.end());

    return moves.back();
} // CMove CAI::getMove() const

