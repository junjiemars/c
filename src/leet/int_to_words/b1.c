#include "d.h"


int int_to_words_sr(int num, char *ss, int n)
{
  static char *s10[] =
    {
      "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
      "Nine", "Ten"
    };
  static char *s20[] =
    {
      "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
      "Nine", "Ten",
      "Eleven", "Twelve",
      "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen",
      "Nineteen"
    };
  static char *g20[] =
    {
      "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty",
      "Ninety"
    };

  if (num == 0)
    {
      n = sprintf(ss, "%s", s10[0]);
      return n;
    }

  for (int d; num > 0;)
    {
      if ((d = num / 1000000000) > 0)
        {
          num -= d * 1000000000;
          n = int_to_words_sr(d, ss, n);
          n += sprintf(&ss[n], " Billion");
        }
      else if ((d = num / 1000000) > 0)
        {
          num -= d * 1000000;
          n = int_to_words_sr(d, ss, n);
          n += sprintf(&ss[n], " Million");
        }
      else if ((d = num / 1000) > 0)
        {
          num -= d * 1000;
          n = int_to_words_sr(d, ss, n);
          n += sprintf(&ss[n], " Thousand");
        }
      else if ((d = num / 100) > 0)
        {
          num -= d * 100;
          n += sprintf(&ss[n], "%s%s Hundred", n > 0 ? " " : "", s10[d]);
        }
      else if ((d = num / 10) >= 2)
        {
          num -= d * 10;
          n += sprintf(&ss[n], "%s%s", n > 0 ? " " : "", g20[d-2]);
        }
      else if ((d = num) > 10)
        {
          num -= d;
          n += sprintf(&ss[n], "%s%s", n > 0 ? " " : "", s20[d]);
        }
      else
        {
          num -= d;
          n += sprintf(&ss[n], "%s%s", n > 0 ? " " : "", s10[d]);
        }
    }
  return n;
}


char * int_to_words(num)
{
  char  *ss  =  calloc(256, sizeof(char));
  int n = int_to_words_sr(num, ss, 0);
  (void) n;
  return ss;
}
