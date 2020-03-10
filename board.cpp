#include <string.h>
#include <assert.h>
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

std::ostream& operator << (std::ostream& os, const CBoard& rhs)
{
   for (int y=0; y<CBoard::CY_SIZE; ++y)
   {
      for (int x=y; x<CBoard::CY_SIZE; ++x)
      {
         os << " ";
      }

      for (int x=0; x<CBoard::CX_SIZE; ++x)
      {
         switch (rhs.m_board[y][x])
         {
            case P_X :       os << "X "; break;
            case P_O :       os << "O "; break;
            case P_space :   os << ". "; break;
            case P_invalid : os << "  "; break;
         }
      }

      os << std::endl;
   }

   return os;
} // std::ostream& operator <<

