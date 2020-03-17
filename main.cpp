#include <ncurses.h>
#include "board.h"
#include "ai.h"

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

   CAI ai(board);

   initscr();
   cbreak();               // Disable line buffering
   keypad(stdscr, TRUE);   // Enable keypad
   noecho();               // Disable keyboard echo
   curs_set(0);            // Disable cursor

   CMove move;
   std::pair<int, int> scorePair;
   while (true)   // Loop until game over.
   {
      move = getPlayerMove(board);
      board.makeMove(move);

      scorePair = board.getScorePair();
      if (scorePair.first == 0 || scorePair.second == 0)
         break;

      move = ai.getMove();
      board.makeMove(move);

      scorePair = board.getScorePair();
      if (scorePair.first == 0 || scorePair.second == 0)
         break;
   }

   board.print();
   if (scorePair.first == 0)
   {
      mvprintw(20, 20, "YOU WON!!!!       ");
      mvprintw(21, 20, "                  ");
   }
  
   if (scorePair.second == 0)
   {
      mvprintw(20, 20, "I WON!!!!         ");
      mvprintw(21, 20, "                  ");
   }
   refresh();
   getch();
  
   endwin();

   return 0;
} // int main()

