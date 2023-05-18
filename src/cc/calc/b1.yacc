%{

#include "_cc_.h"
#include "b1.h"
#include <stdio.h>

  int yylex (void);
  void yyerror (char *);

%}

%union
{
  int i_val;
  char s_idx;
}

%token INTEGER

%%

program:
         fn            { exit (0); }
         ;

fn:
   fn stmt             {  }
   | /* NULL */
   ;

stmt:
     ';'                  { $$ = op (';', 2, NULL, NULL); }
     | expr ';'           { $$ = $1; }
     | PRINT expr ';'     { $$ = op (PRINT, 1 $2); }
     | '{' stmt_list '}'  { $$ = $2; }
     ;

stmt_list:
          stmt {}
          | stmt_list stmt {}
          ;

expr:
       INTEGER                { $$ = con ($1); }
     | VARIABLE               { $$ = id ($1);  }
     | expr '+' INTEGER       { $$ = $1 + $3;  }
     | expr '-' INTEGER       { $$ = $1 - $3;  }
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
