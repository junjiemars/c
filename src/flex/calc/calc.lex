%{
#include "calc.tab.h"
extern void yyerror (char *);
%}

%%

"+"          { return ADD; }
"-"          { return SUB; }
"*"          { return MUL; }
"/"          { return DIV; }
"|"          { return ABS; }
[+-]?[0-9]+  { yylval = atoi (yytext); return NUM; }
\n           { return EOL; }
[ \t]*       { /* ignore whitespace */ }
.            { yyerror (yytext); }

%%
