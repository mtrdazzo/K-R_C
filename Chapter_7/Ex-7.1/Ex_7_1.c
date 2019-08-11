#include <stdbool.h>
#include "Ex_7_1.h"

/* to_lower: return lowercase l */
int to_lower(int l)
{
  return (l - 'A' + 'a');
}

/* to_upper: return uppercase l */
int to_upper(int l)
{
  return (l - 'a' + 'A');
}

/* is_upper: return true if l is uppercase */
bool is_upper(int l)
{
  return (l >= 'A' && l <= 'Z');
}

/* is_lower: return true if l is lowercase */
bool is_lower(int l)
{
  return (l >= 'a' && l <= 'z');
}
