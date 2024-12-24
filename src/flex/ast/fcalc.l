%option noyywrap
%{
#include "ast.h"
#include "fcalc.tab.h"
#include <stdlib.h>

extern void yyerror (char const *);

%}

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"(" |
")"     { return yytext[0]; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.val = atof (yytext); return NUM; }
\n      { return EOL; }
[ \t]*  { /* ignore white space */ }
.	      { yyerror(yytext); }

%%
