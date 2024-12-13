%{
#include <stdio.h>
#include <math.h>
#include "fn.h"

int yylex (void);
void yyerror (char const *);

%}

%define api.value.type union
/* %define parse.error detailed */

%token <double> NUM
%token <SymbolTable*> VAR FUN
%nterm <double> exp

%precedence '='
%left '-' '+'
%left '*' '/'
%left '%'
%left '!'
%right '^'
%precedence NEG

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
| exp '%' exp        { $$ = fmod ($1, $3);              }
| exp '!'            { $$ = fact ($1);                  }
| exp '^' exp        { $$ = pow ($1, $3);               }
| '-' exp  %prec NEG { $$ = -$2;                        }
| '(' exp ')'        { $$ = $2;                         }
;

%%

#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

struct Var
{
  char const *name;
  long double var;
};

struct Var const vars[] = {
  { "e",  2.71828182845904523536028747135266250L },
  { "PI", 3.14159265358979323846264338327950288L },
  { 0, 0.0 }
};

struct Fun
{
  char const *name;
  FunPtr *fun;
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
main (int argc, char **argv)
{
  if (argc > 1 && strcmp ("--trace", argv[1]) == 0)
    {
#if (YYDEBUG)
      yydebug = 1;
#endif
    }
  init_sym_table ();
  return yyparse ();
}

void
init_sym_table (void)
{
  sym_table = NULL;
  for (int i = 0; vars[i].name; i++)
    {
      SymbolTable *p = putsym (vars[i].name, VAR);
      p->value.var = vars[i].var;
    }
  for (int i = 0; funs[i].name; i++)
    {
      SymbolTable *p = putsym (funs[i].name, FUN);
      p->value.fun = funs[i].fun;
    }
}

int
yylex (void)
{
  int c;

  while ((c = getchar ()) == ' ' || c == '\t')
    {
      /* void */
    }

  if (c == EOF)
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
