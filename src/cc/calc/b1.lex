%{

#include "_cc_.h"
#include "b1_yacc.tab.h"

%}

%%

[a-z]            {
                   yylval.s_idx = *yytext - 'a';
                   return VARIABLE;
                 }

[0-9]+           {
                    yylval.i_val = atoi (yytext);
                    return INTEGER;
                 }

.                yyerror ("!panic: unknow character");

%%

int
yywrap (void)
{
  return 1;
}
