#include <algorithm>
#include "ai.h"
#include "trace.h"

const int MAX_VALUE = 999;

int CAI::getValue(int depth)
{
   std::pair<int, int> scorePair = m_board.getScorePair();

   int diff = scorePair.first-scorePair.second;
   int retVal = depth&1 ? diff : -diff;
   TRACE(3*depth+6, "getValue : " << retVal << std::endl);
   return retVal;
} // int CAI::getValue()


int CAI::search(int alpha, int beta, int depth)
{
   TRACE_FUNCTION(3*depth+3, "search");
   TRACE(3*depth+3, "alpha=" << alpha << ", beta=" << beta << ", depth=" << depth << std::endl);
   TRACE(3*depth+3, "");
   for (auto move : m_moveList)
   {
      TRACE(0, move);
   }
   TRACE(0, std::endl);

   if (depth >= m_maxDepth)
   {
      return getValue(depth);
   }

   enum EPiece piece = depth&1 ? P_O : P_X;
   std::vector<CMove> moves = m_board.getLegalMoves(piece);

   int bestVal = -MAX_VALUE;
   for (auto move : moves)
   {
      m_moveList.push_back(move);
      m_board.makeMove(move);
      int val = -search(-beta, -alpha, depth+1);
      m_board.undoMove(move);
      m_moveList.pop_back();

      if (val > bestVal)
      {
         bestVal = val;
      }

      // Now comes the part specific for alpha-beta pruning:
      // Since we are only interested, if another
      // move is better, we update our lower bound.
      if (val > alpha)
      {
         alpha = val;
      }
      // Now we check if the window has been closed.
      // If so, then stop the search.
      if (alpha >= beta)
      {
         // This is fail-soft, since we are returning the value best_val,
         // which might be outside the window.
         break;
      }
   }

   TRACE(3*depth+3, "===> " << bestVal << std::endl);
   return bestVal;

} // int CAI::search(int alpha, int beta, int depth) const

CMove CAI::getMove()
{
   TRACE_FUNCTION(0, "getMove")

   CMove bestMove;
   int bestVal = -MAX_VALUE;
   m_moveList.clear();

   std::vector<CMove> moves = m_board.getLegalMoves(P_O);
   for (auto move : moves)
   {
      m_moveList.push_back(move);
      m_board.makeMove(move);
      int val = -search(-MAX_VALUE, MAX_VALUE, 0);
      m_board.undoMove(move);
      m_moveList.pop_back();

      if (val > bestVal)
      {
         bestVal = val;
         bestMove = move;
      }
   }

   TRACE(0, "===> " << bestMove << std::endl);
   return bestMove;
} // CMove CAI::getMove() const
