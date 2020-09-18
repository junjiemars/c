%{
#include "_flex_.h"
%}

%%
username  printf( "%s", getlogin() );


%%
int
main(int argc, char **argv) {
  if (argc > 1) {
    yyin = fopen(argv[1], "r");
  } else {
    yyin = stdin;
  }
  
  yylex();
	return 0;
}
