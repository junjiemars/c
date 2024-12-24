%{
#include <stdio.h>
#include <math.h>
#include "ast.h"

extern int yylex ();
void yyerror (char const *);

%}

%union {
  double val;
  Ast *ast;
}

%token <val> NUM
%token EOL
%nterm <ast> exp

%left '-' '+'
%left '*' '/'

%precedence '='
%precedence NEG

%%

fnseq:
  %empty
| fnseq line
;

line:
  EOL
| exp EOL {
  printf ("= %.19g\n", eval_ast ($1));
  free_ast ($1);
}
| error EOL { yyerrok; }
;

exp:
  NUM                { $$ = new_ast_val ($1);                  }
| exp '+' exp        { $$ = new_ast (ANT_ADD, NULL, $1, $3);   }
| exp '-' exp        { $$ = new_ast (ANT_SUB, NULL, $1, $3);   }
| exp '*' exp        { $$ = new_ast (ANT_MUL, NULL, $1, $3);   }
| exp '/' exp        { $$ = new_ast (ANT_DIV, NULL, $1, $3);   }
| '-' exp  %prec NEG { $$ = new_ast (ANT_NEG, NULL, NULL, $2); }
| '(' exp ')'        { $$ = $2;                                }
;

%%

#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
  if (argc > 1 && strcmp ("--trace", argv[1]) == 0)
    {
#if (YYDEBUG)
      yydebug = 1;
#endif
    }
  return yyparse ();
}

void
yyerror (char const *ss)
{
  fprintf (stderr, "!panic, %s\n", ss);
}
