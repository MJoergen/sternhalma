#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "board.h"
#include "ai.h"
#include "trace.h"

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


int main(int argc, char **argv)
{
   // Set default values
   int maxDepth = 0;

   int c;
   while ((c = getopt(argc, argv, "t:m:h")) != -1)
   {
      switch (c)
      {
#ifdef ENABLE_TRACE
         case 't' : gpTrace = new CTrace(optarg); break;
#else
         case 't' : std::cout << "Trace not supported" << std::endl; return 1;
#endif
         case 'm' : maxDepth = atoi(optarg); break;
         case 'h' :
         default : {
                      std::cout << "Options:" << std::endl;
                      std::cout << "-t <file> : Trace search to file" << std::endl;
                      std::cout << "-h        : Show this message" << std::endl;
                      exit(1);
                   }
      }
   }

   CBoard board;
   CAI ai(board);
   ai.setMaxDepth(maxDepth);

   initscr();
   cbreak();               // Disable line buffering
   keypad(stdscr, TRUE);   // Enable keypad
   noecho();               // Disable keyboard echo
   curs_set(0);            // Disable cursor

   TRACE(0, "Starting trace" << std::endl);

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

