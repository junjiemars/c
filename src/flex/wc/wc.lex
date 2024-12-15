%{
#include <stdio.h>

int n_char = 0;
int n_word = 0;
int n_line = 0;

%}

WORD [^ \t\v\r\n\f]
EOL  \n

%%

{WORD}+ { ++n_word; n_char += strlen (yytext); }
{EOL}   { ++n_line; ++n_char; }
.       { ++n_char; }

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

  yylex ();

  printf ("%8d%8d%8d %s\n", n_line, n_word, n_char,
          (argc > 1 ? argv[1] : ""));

  return 0;
}
