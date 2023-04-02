#include "d.h"

char *
longest_common_prefix(char **ss, int size)
{
  char *s = calloc(200, sizeof(char));

  if (ss == 0 || size <= 0)
    {
      return s;
    }

  for (int i = 0; i <= 200; i++)
    {
      char c = ss[0][i];

      if (c == 0)
        {
          return s;
        }

      for (int j = 1; j < size; j++)
        {
          if (ss[j][i] != c)
            {
              return s;
            }
        }

      s[i] = c;
    }

  return s;
}
