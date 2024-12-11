%{
#include <stdio.h>
#include <math.h>

int yylex (void);
void yyerror (char const *);

%}

%define api.value.type {long double}

%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG
%right '^'

%%

infixseq: %empty
| infixseq line
;

line: '\n'
| exp '\n' { printf ("= %.20Lg\n", $1); }
| error '\n' { yyerrok; }
;

exp: NUM
| exp '+' exp { $$ = $1 + $3; }
| exp '-' exp { $$ = $1 - $3; }
| exp '*' exp { $$ = $1 * $3; }
| exp '/' exp { $$ = $1 / $3; }
| '-' exp %prec NEG { $$ = -$2; }
| exp '^' exp { $$ = powl ($1, $3); }
| '(' exp ')' { $$ = $2; }
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
  else if (c == '')
    {
      exit (0);
    }
  else
    {
      return c;
    }
}
