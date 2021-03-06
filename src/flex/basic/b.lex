%{
#include <nore.h>
int count = 0;
%}

%%
red|blue { printf("{%s}", yytext); count++; }

%%

int
main(int argc, char **argv)
{
  if (argc > 1)
    {
      yyin = fopen(argv[1], "r");
    }
  else
    {
      yyin = stdin;
    }
  
  yylex();
	return 0;
}
