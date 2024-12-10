%{
#include "_flex_.h"
%}

DIGIT    [0-9]

%%

{DIGIT}+ {
  printf ("%s /* An integer: (%i) */", yytext, atoi (yytext));
}

{DIGIT}+"."{DIGIT}* {
  printf ("%s /* An float: (%lf) */", yytext, atof (yytext));
}

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

  yylex();
	return 0;
}
