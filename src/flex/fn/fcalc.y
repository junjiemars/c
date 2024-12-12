%{
#include <stdio.h>
#include <math.h>
#include "fn.h"

int yylex (void);
void yyerror (char const *);

%}

%define api.value.type union
%token <double> NUM
%token <SymbolTable*> VAR FUN
%nterm <double> exp

%precedence '='
%left '-' '+'
%left '*' '/'
%precedence NEG
%right '^'

%%

fnseq:
  %empty
| fnseq line
;

line:
  '\n'
| exp '\n'   { printf ("= %.19g\n", $1); }
| error '\n' { yyerrok;                }
;

exp:
  NUM
| VAR                { $$ = $1->value.var;              }
| VAR '=' exp        { $$ = $3; $1->value.var = $3;     }
| FUN '(' exp ')'    { $$ = $1->value.fun ($3);         }
| exp '+' exp        { $$ = $1 + $3;                    }
| exp '-' exp        { $$ = $1 - $3;                    }
| exp '*' exp        { $$ = $1 * $3;                    }
| exp '/' exp        { $$ = $1 / $3;                    }
| '-' exp  %prec NEG { $$ = -$2;                        }
| exp '^' exp        { $$ = pow ($1, $3);               }
| '(' exp ')'        { $$ = $2;                         }
;

%%

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

struct Fun
{
  char const *name;
  Fn *fun;
};

struct Fun const funs[] = {
  { "atan", atan },
  { "ceil", ceil },
  { "cos", cos },
  { "exp", exp },
  { "fabs", fabs },
  { "floor", floor },
  { "ln", log },
  { "log", log10 },
  { "round", round },
  { "sin", sin },
  { "sqrt", sqrt },
  { 0, 0 },
};

static void init_sym_table (void);

SymbolTable *sym_table;

int
main (void)
{
  init_sym_table ();
  return yyparse ();
}

void
init_sym_table (void)
{
  sym_table = NULL;
  for (int i = 0; funs[i].name; i++)
    {
      SymbolTable *p = putsym (funs[i].name, FUN);
      p->value.fun = funs[i].fun;
    }
}

int
yylex (void)
{
  int c = getchar ();

  while (c == ' ' || c == '\t')
    {
      c = getchar ();
    }

  if (c == EOF || c == '')
    {
      return YYEOF;
    }

  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
      if (scanf ("%lf", &yylval.NUM) != 1)
        {
          abort ();
        }
      return NUM;
    }

  if (isalpha (c))
    {
      static ptrdiff_t bufsize = 0;
      static char *symbuf = 0;
      ptrdiff_t i = 0;
      do
        {
          if (bufsize <= i)
            {
              bufsize = 2 * bufsize + 40;
              symbuf = realloc (symbuf, (size_t)bufsize);
            }
          symbuf[i++] = (char)c;
          c = getchar ();
        }
      while (isalnum (c));

      ungetc (c, stdin);
      symbuf[i] = '\0';

      SymbolTable *s = getsym (symbuf);
      if (!s)
        {
          s = putsym (symbuf, VAR);
        }
      yylval.VAR = s;
      return s->type;
    }

  return c;
}

void
yyerror (char const *ss)
{
  fprintf (stderr, "!panic, %s\n", ss);
}
