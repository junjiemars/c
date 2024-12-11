%{
#include <stdio.h>

int yylex (void);
void yyerror (char const *);
%}

%define api.value.type {long double}
%token NUM

%%

rpnseq: %empty
| rpnseq line
;

line: '\n'
| exp '\n' { printf ("= %.32Lg\n", $1); }
;

exp: NUM
| exp exp '+' { $$ = $1 + $2; }
| exp exp '-' { $$ = $1 + $2; }
| exp exp '*' { $$ = $1 * $2; }
| exp exp '/' { $$ = $1 / $2; }
;

%%

#include <ctype.h>
#include <stdlib.h>

int
main (void)
{
  return yyparse ();
}

void
yyerror (char const *ss)
{
  printf ("!panic, %s\n", ss);
}

int
yylex (void)
{
  int c = getchar ();
  /* skip whitespace */
  while (c == ' ' || c == '\t')
    {
      c = getchar ();
    }
  /* process number */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
      if (scanf ("%Lf", &yylval) != 1)
        {
          abort ();
        }
      return NUM;
    }
  /* end of rpnseq */
  else if (c == EOF)
    {
      return YYEOF;
    }
  else
    {
      return c;
    }
}
