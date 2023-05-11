#include "_cc_.h"
#include "cc_calc_b1.h"

extern int yylex (void);
extern void yyerror (char const *);

int
main (void)
{
  yyloc.first_line = yyloc.last_line = 1;
  yyloc.first_column = yyloc.last_column = 0;
  return yyparse ();
}

int
yylex (void)
{
  int c;

  /* Skip white space. */
  while ((c = getchar ()) == ' ' || c == '\t')
    ++yylloc.last_column;

  /* Step. */
  yylloc.first_line = yylloc.last_line;
  yylloc.first_column = yylloc.last_column;

  /* Process numbers. */
  if (isdigit (c))
    {
      yylval = c - '0';
      ++yylloc.last_column;
      while (isdigit (c = getchar ()))
        {
          ++yylloc.last_column;
          yylval = yylval * 10 + c - '0';
        }
      ungetc (c, stdin);
      return NUM;
    }

  /* Return end-of-input. */
  if (c == EOF)
    return YYEOF;

  /* Return a single char, and update location. */
  if (c == '\n')
    {
      ++yylloc.last_line;
      yylloc.last_column = 0;
    }
  else
    ++yylloc.last_column;
  return c;
}

void
yyerror (char const *ss)
{
  fprintf (stderr, "!panic: %s\n", ss);
}
