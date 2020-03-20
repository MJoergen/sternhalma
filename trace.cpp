
#include "trace.h"

#ifdef ENABLE_TRACE

std::ostream *gpTrace;

std::string spaces(int numSpaces)
{
   std::string s(numSpaces, ' ');
   return s;
}

#endif // ENABLE_TRACE

