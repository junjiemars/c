%{
#include "_cc_.h"
#include <stdlib.h>
#include "t3_yacc.tab.h"

void yyerror (char *);

%}


%%

[0-9]+           {
                   yylval = atoi (yytext);
                   return INTEGER;
                 }

[-+\n]           return *yytext;

[ \t]            ;              /* ignore whitespace */

.                yyerror ("!panic: invalid character");

%%

int
yywrap (void)
{
  return 1;
}
