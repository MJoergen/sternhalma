#pragma once

#include <ostream>

enum EPiece
{
   P_X = 1,
   P_O = 2,
   P_space = 0,
   P_invalid = -1
}; // enum EPiece


class CSquare
{
   private:
      int m_x;
      int m_y;
}; // class CSquare

class CMove
{
   private:
      CSquare m_from;
      CSquare m_to;
}; // class CMove


class CBoard
{
private:
   static const int CX_SIZE = 19;
   static const int CY_SIZE = 19;

   int m_board[CY_SIZE][CX_SIZE];

public:
   CBoard(const std::string& initString = "");

   friend std::ostream& operator << (std::ostream& os, const CBoard& rhs);

}; // class CBoard

