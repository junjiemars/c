#include "d.h"

int
roman_to_int(const char *s)
{
  static int r[1+'X']  =
    {
      ['I']            =  1,
      ['V']            =  5,
      ['X']            =  10,
      ['L']            =  50,
      ['C']            =  100,
      ['D']            =  500,
      ['M']            =  1000,
    };

  int n = 0;

  for (int i = 0; s[i] != 0; i++)
    {
      if (r[(int) s[i]] < r[(int) s[i+1]])
        {
          n -= r[(int) s[i]];
        }
      else
        {
          n += r[(int) s[i]];
        }
    }

  return n;
}

char *
int_to_roman(int num)
{
  static char *I[] =
    {
      "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"
    };
  static char *X[] =
    {
      "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"
    };
  static char *C[] =
    {
      "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"
    };
  static char *M[] = {"", "M", "MM", "MMM"};

  char *ss = calloc(16, sizeof(char));

  sprintf(ss, "%s%s%s%s",
          M[num/1000],
          C[(num%1000)/100],
          X[(num%100)/10],
          I[num%10]);

  return ss;
}
