#pragma once

#include "board.h"

class CAI
{
private:
   CBoard& m_board;

public:
   CAI(CBoard& board) : m_board(board) {}

   CMove getMove() const;
}; // class CAI

