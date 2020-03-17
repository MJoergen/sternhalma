#pragma once

#include <string>
#include <vector>
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
      friend std::ostream& operator <<(std::ostream &os, const CSquare &rhs);
      int m_x;
      int m_y;
}; // class CSquare


class CMove
{
   public:
      CMove() {}
      CMove(const CSquare& from, const CSquare& to) : m_from(from), m_to(to) {}
      CSquare m_from;
      CSquare m_to;

      bool operator == (const CMove& rhs) const {return m_from == rhs.m_from && m_to == rhs.m_to;}
      bool operator < (const CMove& rhs) const {return m_to.m_y - m_from.m_y < rhs.m_to.m_y - rhs.m_from.m_y;}
      friend std::ostream& operator <<(std::ostream &os, const CMove &rhs);
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
   void getMove(CMove &move) const;
   void makeMove(CMove &move);
   void undoMove(CMove &move);
   bool isMoveLegal(CMove& move) const;
   std::vector<CMove> getLegalMoves(enum EPiece piece) const;
   std::pair<int, int> getScorePair() const;

private:
   int getScore(enum EPiece piece) const;
   void getSquare(CSquare& sq) const;
   std::vector<CMove> getLegalMoveDestinations(const CSquare& from) const;
   std::vector<CSquare> getLegalJumpDestinations(const CSquare& from) const;
   void getAllLegalJumpDestinations(std::vector<CMove>& moves, const CSquare& cur, const CSquare& from) const;
   std::vector<CMove> getLegalMovesFrom(const CSquare& from) const;

   void setFrom(const CSquare& sq) {m_move.m_from = sq;}
   void setTo(const CSquare& sq)   {m_move.m_to = sq;}
}; // class CBoard

