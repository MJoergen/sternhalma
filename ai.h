#pragma once

#include "board.h"

class CAI
{
private:
   CBoard& m_board;
   int m_maxDepth;
   std::vector<CMove> m_moveList;

public:
   CAI(CBoard& board) : m_board(board), m_maxDepth(0) {}
   void setMaxDepth(int maxDepth) {m_maxDepth=maxDepth;}

   int getValue(int alpha, int beta, int depth);
   CMove getMove();

private:
}; // class CAI

