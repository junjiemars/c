%{
  int nchar, nword, nline;
%}

%%

\n            { nline++; nchar++; }
[^ \t\n]+     { nword++, nchar += yyleng; }
.             { nchar++; }


%%

int
yywrap (void)
{
  return 1;
}


int
main (void)
{
  yylex ();
  printf ("%d %d %d\n", nline, nword, nchar);
  return 0;
}
