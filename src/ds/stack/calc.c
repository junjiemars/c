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
static int
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
precedence(int c) {
  switch (c) {
  case '^': return 3;
  case '*':
  case '/': return 2;
  case '+':
  case '-': return 1;
  default: return 0;
  }
}

int
isop(int c) {
  switch (c) {
  case '^':
  case '*':
  case '/':
  case '+':
  case '-': return 1;
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

void
postfix(stack_s *const expr, char *const buf) {
  stack_s *s = stack_new(0, 8, sizeof(int));
  int i, t, c, v;

  while (EOF != (t = token())) {
    if (isdigit(t)) {
      i = 0;
      buf[i++] = t;
      while (isdigit(c = _getc_())) {
        buf[i++] = c;
      }
      buf[i] = 0;
      _ungetc_(c, _stdin_);
      sscanf(&buf[0], "%i", &v);
      stack_push(expr, &v);
    } else if ('(' == t) {
      stack_push(s, &t);
    } else if (')' == t) {
      while ('(' != *(int*)(stack_pop(s, &c))) {
        stack_push(expr, &c);
      }
    } else {
      while (!stack_empty(s)
             && precedence(*(char*)(stack_peek(s, &c))) >= precedence(t)) {
        stack_pop(s, &c);
        stack_push(expr, &c);
      }
      stack_push(s, &t);
    }
  }

  while (!stack_empty(s)) {
    stack_pop(s, &c);
    stack_push(expr, &c);
  }

  stack_free(s);
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

  stack_s *expr = stack_new(0, 8, sizeof(int));
  postfix(expr, expr_buf);

  int v;
  while (!stack_empty(expr)) {
    stack_pop(expr, &v);
    if (isop(v)) {
      printf("%c ", v);
    } else {
      printf("%i ", v);
    }
  }
  putchar('\n');

  stack_free(expr);
  return 0;
}
