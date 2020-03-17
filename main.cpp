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

//static CMove getAIMove(const CAI& ai, const CBoard& board)
//{
//   CBoard thisBoard(board);
//
//   CMove bestMove;
//   int bestVal = -9999;
//
//   std::vector<CMove> moves = thisBoard.getLegalMoves(P_O);
//   for (auto move : moves)
//   {
//      thisBoard.makeMove(move);
//      int val = -ai.getValue(-9999, 9999, 0);
//      thisBoard.undoMove(move);
//
//      if (val > bestVal)
//      {
//         bestVal = val;
//         bestMove = move;
//      }
//   }
//
//   return bestMove;
//} // static CMove getAIMove()
//

int main(int argc, char **argv)
{
   CBoard board;

   CAI ai(board);
   ai.setMaxDepth(0);

   int c;
   while ((c = getopt(argc, argv, "t:h")) != -1)
   {
      switch (c)
      {
#ifdef ENABLE_TRACE
         case 't' : gpTrace = new CTrace(optarg); break;
#else
         case 't' : std::cout << "Trace not supported" << std::endl; return 1;
#endif
         case 'h' :
         default : {
                      std::cout << "Options:" << std::endl;
                      std::cout << "-t <file> : Trace search to file" << std::endl;
                      std::cout << "-h        : Show this message" << std::endl;
                      exit(1);
                   }
      }
   }

   initscr();
   cbreak();               // Disable line buffering
   keypad(stdscr, TRUE);   // Enable keypad
   noecho();               // Disable keyboard echo
   curs_set(0);            // Disable cursor

   TRACE("Starting trace" << std::endl);

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

