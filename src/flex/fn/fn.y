%{
#include <stdio.h>
#include <math.h>
#include "fn.h"

int yylex (void);
void yyerror (char const *);

%}

%define api.value.type union
%token <double> NUM
%token <symrec*> VAR FUN
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
| exp '\n'   { printf ("%.10g\n", $1); }
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

int
main (void)
{
  return yyparse ();
}

int
yylex (void)
{
  return 0;
}

void
yyerror (char const *ss)
{
  fprintf (stderr, "!panic, %s\n", ss);
}
