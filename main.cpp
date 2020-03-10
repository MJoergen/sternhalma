#include <iostream>
#include <ncurses.h>
#include "board.h"

int main()
{
   CBoard board;

   initscr();
   cbreak();               // Disable line buffering
   keypad(stdscr, TRUE);   // Enable keypad
   noecho();               // Disable keyboard echo
   curs_set(0);            // Disable cursor

   while (true)
   {
      CMove move;
      board.getMove(move);
      board.makeMove(move);
   }

   endwin();

   return 0;
}

