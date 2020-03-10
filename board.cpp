/*
   The physical board looks something like the following:
            O
           O O
          O O O
         O O O O
. . . . . . . . . . . . .
 . . . . . . . . . . . .
  . . . . . . . . . . .
   . . . . . . . . . .
    . . . . . . . . .
   . . . . . . . . . .
  . . . . . . . . . . .
 . . . . . . . . . . . .
. . . . . . . . . . . . .
         X X X X
          X X X
           X X
            X

However, in this implementation we will use the following internal
representation:

 0123456789012345678
0###################
1#####O#############
2#####OO############
3#####OOO###########
4#####OOOO##########
5#.............#####
6##............#####
7###...........#####
8####..........#####
9#####.........#####
0#####..........####
1#####...........###
2#####............##
3#####.............#
4##########XXXX#####
5###########XXX#####
6############XX#####
7#############X#####
8###################

*/

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


//   memset(m_board, P_space, sizeof(m_board));
//
//   for (int y=0; y<CY_SIZE; ++y)
//   {
//      m_board[y][0]         = P_invalid;   // Left border
//      m_board[y][CX_SIZE-2] = P_invalid;   // Right border
//   }
//
//   for (int x=0; x<CX_SIZE; ++x)
//   {
//      m_board[0][x]         = P_invalid;   // Top border
//      m_board[CY_SIZE-2][x] = P_invalid;   // Bottom border
//   }
//
//   m_board[1][5] = P_O;
//   m_board[2][5] = P_O;
//   m_board[2][6] = P_O;
//   m_board[3][5] = P_O;
//   m_board[3][6] = P_O;
//   m_board[3][7] = P_O;
//   m_board[4][5] = P_O;
//   m_board[4][6] = P_O;
//   m_board[4][7] = P_O;
//   m_board[4][8] = P_O;
//
//   m_board[14][10] = P_X;
//   m_board[14][11] = P_X;
//   m_board[14][12] = P_X;
//   m_board[14][13] = P_X;
//   m_board[15][11] = P_X;
//   m_board[15][12] = P_X;
//   m_board[15][13] = P_X;
//   m_board[16][12] = P_X;
//   m_board[16][13] = P_X;
//   m_board[17][13] = P_X;

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
            case P_X :
               os << "X "; break;
            case P_O :
               os << "O "; break;
            case P_space :
               os << ". "; break;
            case P_invalid :
               os << "  "; break;
         }
      }
      os << std::endl;
   }

   return os;
}

