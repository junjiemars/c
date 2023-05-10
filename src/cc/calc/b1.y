%{
  #include <math.h>
  #include <stdio.h>
  int yylex (void);
  void yyerror (char const *);
%}

%define api.value.type {double}
%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG
%right '^'

%%
input:
  %empty
| input line
;

line:
  '\n'
  | exp '\n' { printf ("\t%.10g\n", $1); }
;

exp:
  NUM
| exp '+' exp          { $$ = $1 + $3;      }
| exp '-' exp          { $$ = $1 - $3;      }
| exp '*' exp          { $$ = $1 * $3;      }
| exp '/' exp          { $$ = $1 / $3;      }
| '-' exp %prec NEG    { $$ = -$2;          }
| exp '^' exp          { $$ = pow ($1, $3); }
| '(' exp ')'          { $$ = $2;           }
;
%%
