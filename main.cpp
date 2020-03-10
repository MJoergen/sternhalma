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

   board.print();
   CSquare sq = board.getSquare();

   endwin();

   return 0;
}

