%{
#include <stdio.h>
#include "lang.h"

extern int yylex ();
void yyerror (char const *, ...);

%}

%union {
  double val;
  char *name;
  Ast *ast;
}

%token <val> NUM
%token EOL
%token <name> VAR FUN SYM

%left '-' '+' '*' '/' '%' '!'
%right FUN '^' '|'

%token LET

%precedence '='
%precedence NEG

%type <ast> stmt exp

%start langseq

%%

langseq:
  %empty
| langseq stmt EOL {
  printf ("= %.19g\n", eval_ast ($2));
  free_ast ($2);
}
| langseq LET SYM '=' stmt EOL { new_ast_var ($3, $5); }
| langseq error EOL { yyerrok; }
;

stmt:
  stmt ';' { $$ = $1; }
| exp      { $$ = $1; }
;

exp:
  NUM                { $$ = new_ast_val ($1);                  }
 /* | VAR '=' exp        { $$ = new_ast_var ($1, $3);              } */
 /* | SYM '=' exp        { $$ = new_ast_var ($1, $3);              } */
| VAR                { $$ = lookup_ast_var ($1);               }
| SYM                { $$ = lookup_ast_var ($1);               }
| '|' exp '|'        { $$ = new_ast (ANT_ABS, NULL, NULL, $2); }
| exp '+' exp        { $$ = new_ast (ANT_ADD, NULL, $1, $3);   }
| exp '-' exp        { $$ = new_ast (ANT_SUB, NULL, $1, $3);   }
| exp '*' exp        { $$ = new_ast (ANT_MUL, NULL, $1, $3);   }
| exp '/' exp        { $$ = new_ast (ANT_DIV, NULL, $1, $3);   }
| exp '%' exp        { $$ = new_ast (ANT_MOD, NULL, $1, $3);   }
| exp '!'            { $$ = new_ast (ANT_FAC, NULL, NULL, $1); }
| exp '^' exp        { $$ = new_ast (ANT_POW, NULL, $1, $3);   }
| '-' exp  %prec NEG { $$ = new_ast (ANT_NEG, NULL, NULL, $2); }
| '(' exp ')'        { $$ = $2;                                }
| FUN '(' exp ')'    { $$ = new_ast_fun ($1, $3);              }
| SYM '(' exp ')'    { $$ = new_ast_fun ($1, $3);              }
;

%%

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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
yyerror (char const *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);
  fprintf (stderr, "!panic, ");
  vfprintf (stderr, fmt, ap);
  va_end (ap);
  fprintf (stderr, "\n");
}
