%{
#include <_flex_.h>
#include <stdio.h>
#include <stdlib.h>

enum yytokentype
{
  NUM = 258,
  ADD,
  SUB,
  MUL,
  DIV,
  ABS,
  EOL
};

int yylval;

%}

%%

"+"    { return ADD; }
"-"    { return SUB; }
"*"    { return MUL; }
"/"    { return DIV; }
"|"    { return ABS; }
[0-9]+ { return NUM; }
\n     { yylval = atoi (yytext); return EOL; }
[ \t]* { /* ignore whitespace */ }
.      { printf ("!panic, %c\n", *yytext); }

%%

/* int */
/* main (int argc, char **argv) */
/* { */
/*   int tok; */

/*   if (argc > 1) */
/*     { */
/*       yyin = fopen (argv[1], "r"); */
/*     } */
/*   else */
/*     { */
/*       yyin = stdin; */
/*     } */

/*   while ((tok = yylex ())) */
/*     { */
/*       printf ("%d", tok); */
/*       if (tok == NUM) */
/*         { */
/*           printf (" = %d\n", yylval); */
/*         } */
/*       else */
/*         { */
/*           printf ("\n"); */
/*         } */
/*     } */
/* } */
