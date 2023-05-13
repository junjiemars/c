%{
#include "_cc_.h"
#include <stdio.h>

/* #ifndef YYSTYPE */
/* #define YYSTYPE int */
/* #endif */

/* #define INTEGER 258 */
/* extern YYSTYPE yylval; */


  int yylex (void);
  void yyerror (char *);

%}

%token INTEGER

%%

program:
         program expr '\n'        { printf ("%d\n", $2); }
         |
         ;

expr:
         INTEGER                  { $$ = $1; }
         | expr '+' INTEGER       { $$ = $1 + $3; }
         | expr '-' INTEGER       { $$ = $1 - $3; }
         ;



%%


void
yyerror (char *s)
{
  fprintf (stderr, "%s\n", s);
}

int
main (void)
{
  yyparse ();
  return 0;
}
