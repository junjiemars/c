#include <_ds_.h>
#include <stack.h>
#include <stdio.h>
#include <ctype.h>

#if NDEBUG
#define _getc_ getchar
#define _ungetc_ ungetc
#define _stdin_ stdin
#else
#define MAX_EXPR 128
#define _stdin_ 0
static char _str_in_[MAX_EXPR];
static int _str_in_i_ = 0;
static char
_getc_() {
  if (MAX_EXPR == _str_in_i_) {
    return EOF;
  }
  return _str_in_[_str_in_i_++];
}

static
int
_ungetc_(int c, FILE* stream) {
  _unused_(stream);
  _str_in_i_--;
  return c;
}
#endif

static char expr_buf[1024];

int
precedence(char c) {
  switch (c) {
  case '(': return 0;
  case '+':
  case '-': return 3;
  case '*':
  case '/': return 5;
  default: return 0;
  }
}

char
token(void) {
  char c;
  while (EOF != (c = _getc_())) {
    if (' ' == c) {
      continue;
    }
    if ('\0' == c) {
      return EOF;
    }
    return c;
  }
  return EOF;
}

int
postfix(char *const expr) {
  int i = 0;
  stack_s *s = stack_new(0, sizeof(char));
  char t, c;

  while (EOF != (t = token())) {
    if (isdigit(t)) {
      expr[i++] = t;
      while (isdigit(c = _getc_())) {
        expr[i++] = c;
      }
      _ungetc_(c, _stdin_);
    } else if ('(' == t) {
      stack_push(s, &t);
    } else if (')' == t) {
      while ('(' != *(char*)(stack_pop(s, &c))) {
        expr[i++] = c;
      }
    } else {
      while (!stack_empty(s)
             && precedence(*(char*)(stack_peek(s, &c))) >= precedence(t)) {
        expr[i++] = *(char*)stack_pop(s, &c);
      }
      stack_push(s, &t);
    }
  }

  while (!stack_empty(s)) {
    expr[i++] = *(char*)stack_pop(s, &c);
  }
  return i;
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

#if !(NDEBUG)
  if (argc < 2) {
    printf("where the expression?\n");
    return 0;
  }

  memcpy(_str_in_, argv[1], strlen(argv[1])+1);
  printf("expr: %s\n", _str_in_);
#endif

  printf("postfix:\n");

  int n = postfix(expr_buf);

  for (int i = 0; i < n; i++) {
    printf("%c ", expr_buf[i]);
  }
  putchar('\n');
  
  return 0;
}
