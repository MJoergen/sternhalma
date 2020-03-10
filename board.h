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
      CSquare() : m_x(-1), m_y(-1) {}
      CSquare(int x, int y) : m_x(x), m_y(y) {}
      CSquare(const CSquare& rhs) : m_x(rhs.m_x), m_y(rhs.m_y) {}

      bool operator == (const CSquare& rhs) const {return m_x == rhs.m_x && m_y == rhs.m_y;}
      int m_x;
      int m_y;
}; // class CSquare

class CMove
{
   public:
      CSquare m_from;
      CSquare m_to;
}; // class CMove


class CBoard
{
private:
   static const int CX_SIZE = 19;
   static const int CY_SIZE = 19;

   enum EPiece m_board[CY_SIZE][CX_SIZE];

   CMove m_move;

public:
   CBoard(const std::string& initString = "");

   void print() const;
   void getSquare(CSquare& sq) const;
   void getMove(CMove &move) const;
   void makeMove(CMove &move);

   void setFrom(const CSquare& sq) {m_move.m_from = sq;}
   void setTo(const CSquare& sq)   {m_move.m_to = sq;}

}; // class CBoard

