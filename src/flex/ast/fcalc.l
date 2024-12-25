%option noyywrap
%{
#include "ast.h"
#include "fcalc.tab.h"
#include <stdlib.h>

extern void yyerror (char const *);

%}

/* float exponent */
number	([Ee][-+]?[0-9]+)

%%

 /* operator */
"=" |
"|" |
"+" |
"-" |
"*" |
"/" |
"%" |
"!" |
"^" |
"(" |
")"     { return yytext[0]; }

 /* function */
"atan"  { yylval.name = "atan";  return FUN; }
"ceil"  { yylval.name = "ceil";  return FUN; }
"cos"   { yylval.name = "cos";   return FUN; }
"exp"   { yylval.name = "exp";   return FUN; }
"fabs"  { yylval.name = "fabs";  return FUN; }
"floor" { yylval.name = "floor"; return FUN; }
"ln"    { yylval.name = "ln";    return FUN; }
"log"   { yylval.name = "log";   return FUN; }
"round" { yylval.name = "round"; return FUN; }
"sin"   { yylval.name = "sin";   return FUN; }
"sqrt"  { yylval.name = "sqrt";  return FUN; }
"tan"   { yylval.name = "tan";   return FUN; }

 /* name */
"e" { yylval.name = "e"; return VAR; }
"π" |
"PI" { yylval.name = "PI"; return VAR; }
[a-z][a-z0-9]* { yylval.name = strdup (yytext); return SYM; }

 /* number */
[0-9]+"."[0-9]*{number}? |
"."?[0-9]+{number}? { yylval.val = atof (yytext); return NUM; }

\n      { return EOL; }
[ \t]   { /* ignore white space */ }
.	      { yyerror(yytext); }

%%
