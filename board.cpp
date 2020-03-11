#include <string.h>
#include <assert.h>
#include <ncurses.h>
#include "board.h"

static enum EPiece charToEnum(char ch)
{
   switch (ch)
   {
      case 'X' : return P_X;
      case 'O' : return P_O;
      case '.' : return P_space;
      case '#' : return P_invalid;
   }
   assert(false);
}; // static char enumToChar()

static char enumToChar(const enum EPiece& en)
{
   switch (en)
   {
      case P_X :       return 'X';
      case P_O :       return 'O';
      case P_space :   return '.';
      case P_invalid : return ' ';
   }
   assert(false);
}; // static char enumToChar()


CBoard::CBoard(const std::string& initString)
{
   std::string thisInitString(initString);

   if (thisInitString.length() == 0)
   {
      thisInitString = 
         "###################"
         "#####O#############"
         "#####OO############"
         "#####OOO###########"
         "#####OOOO##########"
         "#.............#####"
         "##............#####"
         "###...........#####"
         "####..........#####"
         "#####.........#####"
         "#####..........####"
         "#####...........###"
         "#####............##"
         "#####.............#"
         "##########XXXX#####"
         "###########XXX#####"
         "############XX#####"
         "#############X#####"
         "###################";
   }

   assert(thisInitString.length() >= CX_SIZE*CY_SIZE);

   for (int y=0; y<CY_SIZE; ++y)
   {
      for (int x=0; x<CX_SIZE; ++x)
      {
         char ch = thisInitString[y*CX_SIZE+x];
         m_board[y][x] = charToEnum(ch);
      }
   }

} // CBoard

void CBoard::print() const
{
   for (int y=0; y<CBoard::CY_SIZE; ++y)
   {
      move(y, y);
      for (int x=0; x<CBoard::CX_SIZE; ++x)
      {
         CSquare sq(x,y);
         if (sq == m_move.m_from) attron(A_REVERSE);
         if (sq == m_move.m_to)   attron(A_REVERSE);
         if (sq == m_move.m_to)   attron(A_BLINK);
         mvaddch(y, 2*x-y+5, enumToChar(m_board[y][x]));
         if (sq == m_move.m_from) attroff(A_REVERSE);
         if (sq == m_move.m_to)   attroff(A_REVERSE);
         if (sq == m_move.m_to)   attroff(A_BLINK);
      }
   }
   std::vector<CMove> legalMoves = getLegalMoves();
   mvprintw(20, 20, "%d legal moves   ", legalMoves.size());
} // void CBoard::print()

void CBoard::getMove(CMove& move) const
{
   ((CBoard *)this)->setFrom({-1, -1});
   ((CBoard *)this)->setTo({-1, -1});

   move = {{10, 14}, {10, 14}};
   // Get FROM square
   while (true)
   {
      getSquare(move.m_from);
      if (m_board[move.m_from.m_y][move.m_from.m_x] == P_X)
         break;
   }
   ((CBoard *)this)->setFrom(move.m_from);

   move.m_to = move.m_from;
   // Get TO square
   while (true)
   {
      getSquare(move.m_to);
      if (m_board[move.m_to.m_y][move.m_to.m_x] == P_space)
         break;
   }
} // CMove CBoard::getMove() const

void CBoard::getSquare(CSquare& sq) const
{
   // Get FROM square
   while (true)
   {
      ((CBoard *)this)->setTo(sq);
      print();
      CSquare oldSq(sq);

      int ch = getch();
      switch (ch)
      {
         case KEY_DOWN  : sq.m_y += 1; break;
         case KEY_UP    : sq.m_y -= 1; break;
         case KEY_RIGHT : sq.m_x += 1; break;
         case KEY_LEFT  : sq.m_x -= 1; break;
         default        : return;
      } // switch

      if (m_board[sq.m_y][sq.m_x] == P_invalid)
      {
         sq = oldSq;
      }
   }
} // CSquare CBoard::getSquare() const

void CBoard::makeMove(CMove& move)
{
   m_board[move.m_to.m_y][move.m_to.m_x] = m_board[move.m_from.m_y][move.m_from.m_x];
   m_board[move.m_from.m_y][move.m_from.m_x] = P_space;
} // void CBoard::makeMove(CMove& move)

std::vector<CMove> CBoard::getLegalMoveDestinations(const CSquare& from) const
{
   std::vector<CMove> legalMoves;
   CMove move;
   move.m_from=from;

   int x = from.m_x;
   int y = from.m_y;

   if (m_board[y][x+1] == P_space)
   {
      move.m_to=CSquare(x+1, y);
      legalMoves.push_back(move);
   }
   if (m_board[y][x-1] == P_space)
   {
      move.m_to=CSquare(x-1, y);
      legalMoves.push_back(move);
   }
   if (m_board[y+1][x] == P_space)
   {
      move.m_to=CSquare(x, y+1);
      legalMoves.push_back(move);
   }
   if (m_board[y+1][x+1] == P_space)
   {
      move.m_to=CSquare(x+1, y+1);
      legalMoves.push_back(move);
   }
   if (m_board[y-1][x] == P_space)
   {
      move.m_to=CSquare(x, y-1);
      legalMoves.push_back(move);
   }
   if (m_board[y-1][x-1] == P_space)
   {
      move.m_to=CSquare(x-1, y-1);
      legalMoves.push_back(move);
   }

   return legalMoves;
} // std::vector<CMove> CBoard::getLegalMoveDestinations(const CSquare& from) const

std::vector<CMove> CBoard::getLegalJumpDestinations(const CSquare& from) const
{
   std::vector<CMove> legalMoves;
   CMove move;
   move.m_from=from;

   int x = from.m_x;
   int y = from.m_y;

   if ((m_board[y][x+1] == P_X || m_board[y][x+1] == P_O) && m_board[y][x+2] == P_space)
   {
      move.m_to=CSquare(x+2, y);
      legalMoves.push_back(move);
   }
   if ((m_board[y][x-1] == P_X || m_board[y][x-1] == P_O) && m_board[y][x-2] == P_space)
   {
      move.m_to=CSquare(x-2, y);
      legalMoves.push_back(move);
   }
   if ((m_board[y+1][x] == P_X || m_board[y+1][x] == P_O) && m_board[y+2][x] == P_space)
   {
      move.m_to=CSquare(x, y+2);
      legalMoves.push_back(move);
   }
   if ((m_board[y+1][x+1] == P_X || m_board[y+1][x+1] == P_O) && m_board[y+2][x+2] == P_space)
   {
      move.m_to=CSquare(x+2, y+2);
      legalMoves.push_back(move);
   }
   if ((m_board[y-1][x] == P_X || m_board[y-1][x] == P_O) && m_board[y-2][x] == P_space)
   {
      move.m_to=CSquare(x, y-2);
      legalMoves.push_back(move);
   }
   if ((m_board[y-1][x-1] == P_X || m_board[y-1][x-1] == P_O) && m_board[y-2][x-2] == P_space)
   {
      move.m_to=CSquare(x-2, y-2);
      legalMoves.push_back(move);
   }

   return legalMoves;
} // std::vector<CMove> CBoard::getLegalJumpDestinations(const CSquare& from) const


std::vector<CMove> CBoard::getAllLegalJumpDestinations(const CSquare& from) const
{
   return getLegalJumpDestinations(from);
} // std::vector<CMove> CBoard::getAllLegalJumpDestinations(const CSquare& from) const


std::vector<CMove> CBoard::getLegalMoves() const
{
   std::vector<CMove> legalMoves;

   for (int y=0; y<CBoard::CY_SIZE; ++y)
   {
      for (int x=0; x<CBoard::CX_SIZE; ++x)
      {
         if (m_board[y][x] == P_X)
         {
            CSquare from=CSquare(x, y);

            std::vector<CMove> moves = getLegalMoveDestinations(from);
            legalMoves.insert(legalMoves.end(), moves.begin(), moves.end());

            moves = getAllLegalJumpDestinations(from);
            legalMoves.insert(legalMoves.end(), moves.begin(), moves.end());
         }
      }
   }

   return legalMoves;
} // std::vector<CMove> getLegalMoves() const

