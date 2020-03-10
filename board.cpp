#include <string.h>
#include <assert.h>
#include <ncurses.h>
#include "board.h"

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
         switch (thisInitString[y*CX_SIZE+x])
         {
            case '#' : m_board[y][x] = P_invalid; break;
            case 'X' : m_board[y][x] = P_X; break;
            case 'O' : m_board[y][x] = P_O; break;
            case '.' : m_board[y][x] = P_space; break;
            default: assert(false);
         }
      }
   }

} // CBoard

static char enumToChar(const enum EPiece& en)
{
   switch (en)
   {
      case P_X :       return 'X';
      case P_O :       return 'O';
      case P_space :   return '.';
      case P_invalid : return ' ';
   }
   return '?';
}; // static char enumToChar()

void CBoard::print(const CSquare sq) const
{
   for (int y=0; y<CBoard::CY_SIZE; ++y)
   {
      move(y, y);
      for (int x=0; x<CBoard::CX_SIZE; ++x)
      {
         if (sq.m_x==x && sq.m_y==y)
         {
            attron(A_REVERSE);
         }
         mvaddch(y, 2*x-y+5, enumToChar(m_board[y][x]));
         if (sq.m_x==x && sq.m_y==y)
         {
            attroff(A_REVERSE);
         }
      }
   }
} // void CBoard::print()

CSquare CBoard::getSquare() const
{
   CSquare sq(10, 14);

   while (true)
   {
      print(sq);
      CSquare oldSq(sq);

      int ch = getch();
      switch (ch)
      {
         case KEY_DOWN  : sq.m_y += 1; break;
         case KEY_UP    : sq.m_y -= 1; break;
         case KEY_RIGHT : sq.m_x += 1; break;
         case KEY_LEFT  : sq.m_x -= 1; break;
         default        :
            if (m_board[sq.m_y][sq.m_x] == P_X)
            {
               return sq;
            }
      } // switch

      if (m_board[sq.m_y][sq.m_x] == P_invalid)
      {
         sq = oldSq;
      }
   }
} // CSquare CBoard::getSquare() const

