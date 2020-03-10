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
   public:
      CSquare(int x, int y) : m_x(x), m_y(y) {}

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

   enum EPiece m_board[CY_SIZE][CX_SIZE];

public:
   CBoard(const std::string& initString = "");

   void print(const CSquare sq = {0,0}) const;
   CSquare getSquare() const;

}; // class CBoard

