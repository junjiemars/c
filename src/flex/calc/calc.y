%{
#include <stdio.h>
extern int yylex (void);
extern FILE *yyin;
void yyerror (char *);
%}

%token NUM
%token ADD SUB MUL DIV ABS
%token EOL

%%

calcseq: /* void */
| calcseq exp EOL { printf ("= %d\n", $1); };

exp: factor
| exp ADD factor { $$ = $1 + $3; }
| exp SUB factor { $$ = $1 - $3; }
;

factor: term
| factor MUL term { $$ = $1 * $3; }
| factor DIV term { $$ = $1 / $3; }
;

term: NUM  { $$ = $1; }
| ABS term { $$ = $2 >= 0 ? $2 : - $2; }
;

%%

int
main (int argc, char **argv)
{
  if (argc > 1)
    {
      yyin = fopen (argv[1], "r");
    }
  else
    {
      yyin = stdin;
    }

  return yyparse ();
}

void
yyerror (char *s)
{
  fprintf (stderr, "!panic, %s\n", s);
}
