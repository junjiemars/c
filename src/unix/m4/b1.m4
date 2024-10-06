# https://www.gnu.org/software/m4/manual/m4.html
# https://wolfram.schneider.org/bsd/7thEdManVol2/m4/m4.pdf

define(stdio_h, `#include <stdio.h>')
define(N, 100)
define(M, N)
define(`N', 200)

stdio_h
static void foo(void);

int main(void) {
  printf("`M'=%d, `N'=\n", M, N);
}

undefine(`N')
void foo(void) {
  printf("`N'=%d\n", N);
}

changequote([,])
/* [M] = M? */

changequote(`,')

/* `M' = M? */

ifdef(`unix', `define(UNIX_TIME, 1970)', `define(UNIX_TIME, 1234)')
`UNIX_TIME' = UNIX_TIME

define(bump, $1 = $1 + 1)
bump(x)

define(cat, $1$2$3$4$5$6$7$8$9)
`UNIX_TIME'=cat(U, N, I, X, _, TIME)
