%{
#include "_cc_.h"

  int yylineno;

%}

%%

^(.*)\n    printf ("%4d\t%s", yylineno++, yytext);

%%

int
yywrap (void)
{
  return 1;
}

int
main (void)
{
  yylex ();
  return 0;
}
