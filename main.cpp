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

   while (true)   // Loop over entire game
   {
      CMove move;
      while (true)   // Loop until player enters a legal move
      {
         board.getMove(move);
         if (board.isMoveLegal(move))
            break;
         mvprintw(21, 20, "Illegal move.");
      }
      board.makeMove(move);
   }

   endwin();

   return 0;
}

