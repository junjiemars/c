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

 /* operator */
"=" |
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
"atan"  { yylval.name = strdup (yytext); return FUN; }
"ceil"  { yylval.name = strdup (yytext); return FUN; }
"cos"   { yylval.name = strdup (yytext); return FUN; }
"exp"   { yylval.name = strdup (yytext); return FUN; }
"fabs"  { yylval.name = strdup (yytext); return FUN; }
"floor" { yylval.name = strdup (yytext); return FUN; }
"ln"    { yylval.name = strdup (yytext); return FUN; }
"log"   { yylval.name = strdup (yytext); return FUN; }
"round" { yylval.name = strdup (yytext); return FUN; }
"sin"   { yylval.name = strdup (yytext); return FUN; }
"sqrt"  { yylval.name = strdup (yytext); return FUN; }
"tan"   { yylval.name = strdup (yytext); return FUN; }

 /* name */
[a-z][a-z0-9]* { yylval.name = strdup (yytext); return VAR; }

 /* number */
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.val = atof (yytext); return NUM; }

\n      { return EOL; }
[ \t]*  { /* ignore white space */ }
.	      { yyerror(yytext); }

%%
