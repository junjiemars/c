#include <_ds_.h>
#include <stack.h>
#include <queue.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_EXPR 128

#if NDEBUG
#  define _getc_ getchar
#  define _ungetc_ ungetc
#  define _stdin_ stdin
#else
#  define _stdin_ 0
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
#endif /* NDEBUG */

static char expr_buf[MAX_EXPR];

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
  int c;
  while (EOF != (c = _getc_())) {
    if (' ' == c) {
      continue;
    }
    if ('\0' == c || c == '=') {
      return EOF;
    }
    return c;
  }
  return EOF;
}

void
postfix(queue_s *const expr, char *const buf) {
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
      queue_enq(expr, &v);
    } else if ('(' == t) {
      stack_push(s, &t);
    } else if (')' == t) {
      stack_pop(s, &c);
      while ('(' != c) {
        queue_enq(expr, &c);
        stack_pop(s, &c);
      }
    } else {
      stack_peek(s, &c);
      while (!stack_empty(s) && precedence(c) >= precedence(t)) {
        stack_pop(s, &c);
        queue_enq(expr, &c);
        stack_peek(s, &c);
      }
      stack_push(s, &t);
    }
  }

  while (!stack_empty(s)) {
    stack_pop(s, &c);
    queue_enq(expr, &c);
  }

  stack_free(s);
}

int
expt(int b, int n, int acc) {
  if (n < 1) return acc;
  return expt(b, n-1, acc*b);
}

int
eval(queue_s *const expr) {
  stack_s *op = stack_new(0, 8, sizeof(int));
  int v, a, b, c;
  while (!queue_empty(expr)) {
    queue_deq(expr, &v);
    if (isop(v)) {
        stack_pop(op, &b);
        stack_pop(op, &a);
        switch (v) {
        case '^': c = expt(a, b, 1); break;
        case '+': c = a + b; break;
        case '-': c = a - b; break;
        case '*': c = a * b; break;
        case '/': c = a / b; break;
        }
      stack_push(op, &c);
    } else {
      stack_push(op, &v);
    }
  }
  stack_pop(op, &v);
  stack_free(op);
  return v;
}

void
test_expt(void) {
  printf("expt: %i^%i = %i\n", 2, 3, expt(2, 3, 1));
}

void
test_postfix() {
  printf("postfix: ");
  _str_in_i_ = 0;

  queue_s *expr = queue_new(0, 8, sizeof(int));
  postfix(expr, expr_buf);

  int v;
  while (!queue_empty(expr)) {
    queue_deq(expr, &v);
    if (isop(v)) {
      printf("%c ", v);
    } else {
      printf("%i ", v);
    }
  }
  putchar('\n');

  queue_free(expr);  
}

void
test_eval(void) {
  printf("eval: ");
  _str_in_i_ = 0;

  queue_s *expr = queue_new(0, 8, sizeof(int));
  postfix(expr, expr_buf);

  int v = eval(expr);
  printf("%i\n", v);

  queue_free(expr);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);


#if NDEBUG
  queue_s *expr = queue_new(0, 8, sizeof(int));
  postfix(expr, expr_buf);
  int v = eval(expr);
  printf(" %i\n", v);
  queue_free(expr);

#else
  if (argc < 2) {
    printf("where the expression?\n");
    return 0;
  }
  memcpy(_str_in_, argv[1], strlen(argv[1])+1);

  /* test_expt(); */
  printf("expr: %s\n", _str_in_);

  test_postfix();
  test_eval();

#endif

  return 0;
}
