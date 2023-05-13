%{

#include "_cc_.h"
#include "t4_yacc.tab.h"

  void yyerror (char *);


%}

%%

[a-z]            {
                   yylval = *yytext - 'a';
                   return VARIABLE;
                 }


[0-9]+           {
                   yylval = atoi (yytext);
                   return INTEGER;
                 }

[-+()=*/\n]      {  return *yytext; }

[ \t]            ;

.                { yyerror ("!panic: invalid character"); }

%%


int
yywrap (void)
{
  return 1;
}
