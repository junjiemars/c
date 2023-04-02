#include "d.h"

int
roman_to_int(const char *s)
{
  int          i, n  =  0;
  const char  *c;

  for (c = s, i = 0; *c != 0; c++, i++)
    {
      switch (*c)
        {
        case 'I':
          n += 1;
          break;
        case 'V':
          n += 5;
          if ((i-1) >= 0 && s[i-1] == 'I')
            {
              n -= 2;
            }
          break;
        case 'X':
          n += 10;
          if ((i-1) >= 0 && s[i-1] == 'I')
            {
              n -= 2;
            }
          break;
        case 'L':
          n += 50;
          if ((i-1) >= 0 && s[i-1] == 'X')
            {
              n -= 20;
            }
          break;
        case 'C':
          n += 100;
          if ((i-1) >= 0 && s[i-1] == 'X')
            {
              n -= 20;
            }
          break;
        case 'D':
          n += 500;
          if ((i-1) >= 0 && s[i-1] == 'C')
            {
              n -= 200;
            }
          break;
        case 'M':
          n += 1000;
          if ((i-1) >= 0 && s[i-1] == 'C')
            {
              n -= 200;
            }
          break;
        }
    }
  return n;
}

char *
int_to_roman(int num)
{
  int    d  =  num;
  char  *s, *ss;

  if (d <= 0)
    {
      return 0;
    }
  ss = calloc(16, sizeof(char));

  for(s = ss; d > 0;)
    {
      if ((d - 1000) >= 0)
        {
          d -= 1000;
          *s++ = 'M';
        }
      else if ((d - 900) >= 0)
        {
          d -= 900;
          *s++ = 'C';
          *s++ = 'M';
        }
      else if ((d - 500) >= 0)
        {
          d -= 500;
          *s++ = 'D';
        }
      else if ((d - 400) >= 0)
        {
          d -= 400;
          *s++ = 'C';
          *s++ = 'D';
        }
      else if ((d - 100) >= 0)
        {
          d -= 100;
          *s++ = 'C';
        }
      else if ((d - 90) >= 0)
        {
          d -= 90;
          *s++ = 'X';
          *s++ = 'C';
        }
      else if ((d - 50) >= 0)
        {
          d -= 50;
          *s++ = 'L';
        }
      else if ((d - 40) >= 0)
        {
          d -= 40;
          *s++ = 'X';
          *s++ = 'L';
        }
      else if ((d - 10) >= 0)
        {
          d -= 10;
          *s++ = 'X';
        }
      else if ((d - 9) >= 0)
        {
          d -= 9;
          *s++ = 'I';
          *s++ = 'X';
        }
      else if ((d - 5) >= 0)
        {
          d -= 5;
          *s++ = 'V';
        }
      else if ((d - 4) >= 0)
        {
          d -= 4;
          *s++ = 'I';
          *s++ = 'V';
        }
      else if ((d - 1) >= 0)
        {
          d -= 1;
          *s++ = 'I';
        }
    }

  return ss;
}
