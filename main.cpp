#include <ncurses.h>
#include "board.h"

static CMove getPlayerMove(const CBoard& board)
{
   CMove move;
   while (true)   // Loop until player enters a legal move.
   {
      board.getMove(move);
      if (board.isMoveLegal(move))
         break;
      mvprintw(21, 20, "Illegal move.");
   }
   return move;
} // static CMove getPlayerMove(const CBoard& board)


int main()
{
   CBoard board;

   initscr();
   cbreak();               // Disable line buffering
   keypad(stdscr, TRUE);   // Enable keypad
   noecho();               // Disable keyboard echo
   curs_set(0);            // Disable cursor

   while (true)   // Loop until game over.
   {
      CMove move = getPlayerMove(board);
      board.makeMove(move);
   }

   endwin();

   return 0;
} // int main()

