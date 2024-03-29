#include "_cc_.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define BSIZE          128
#define MAX_TOKEN_LEN  32
#define MAX_TOKEN_NUM  32
#define EOS            '\0'


enum token_t
  {
    IDENTIFIER  =  256,
    QUALIFIER,
    TYPE
  };

struct token_s
{
	int type;
	char string[MAX_TOKEN_LEN];
};


int           lookahead(void);
void          pushback(void);
void          _vsprintf_(char *, ...);
void          get_token(void);
void          on_first_identifier(void);
void          on_function_args(void);
void          on_array(void);
void          on_pointer(void);
void          on_declarator(void);
enum token_t  classify_string(void);


static struct token_s  stack[MAX_TOKEN_NUM];
static struct token_s  token;

static char   inbuf[BSIZE];
static char  *inptr;
static char   outbuf[BSIZE*2];
static char  *outptr;
static int    top  =  -1;

#define pop      stack[top--]
#define push(s)  stack[++top]  =  (s)


int
lookahead(void)
{
	if (EOS == *inptr || inptr >= inbuf + BSIZE - 1)
    {
      return EOF;
    }
	return *inptr++;
}

void
pushback(void)
{
	if (inbuf < inptr)
    {
      inptr--;
    }
}

void
_vsprintf_(char *fmt, ...)
{
  int      len;
	va_list  args;

	va_start(args, fmt);
  len = vsprintf(outptr, fmt, args);
	outptr += len;
	va_end(args);
}

void
get_token(void)
{
	char  *p  =  token.string;

	while (isblank(*p = (char)lookahead()))
    {
      /* void */
    }

	if (isalnum(*p))
    {
      while (isalnum(*++p = (char)lookahead()))
        {
          /* void */
        }

      pushback();
      *p = EOS;
      token.type = classify_string();
      return;
    }

	if ('*' == *p)
    {
      strcpy(token.string, "pointer to");
      token.type = '*';
      return;
    }

	token.string[1] = EOS;
	token.type = *p;
	return;
}

enum token_t
classify_string(void)
{
	char *s = token.string;
	if (0 == strcmp(s, "const")) return QUALIFIER;
	if (0 == strcmp(s, "volatile")) return QUALIFIER;
	if (0 == strcmp(s, "char")) return TYPE;
	if (0 == strcmp(s, "signed")) return TYPE;
	if (0 == strcmp(s, "unsigned")) return TYPE;
	if (0 == strcmp(s, "short")) return TYPE;
	if (0 == strcmp(s, "int")) return TYPE;
	if (0 == strcmp(s, "long")) return TYPE;
	if (0 == strcmp(s, "float")) return TYPE;
	if (0 == strcmp(s, "double")) return TYPE;
	if (0 == strcmp(s, "struct")) return TYPE;
	if (0 == strcmp(s, "union")) return TYPE;
	if (0 == strcmp(s, "enum")) return TYPE;
	if (0 == strcmp(s, "void")) return TYPE;
 	return IDENTIFIER;
}

void
on_first_identifier(void)
{
	get_token();
	while (IDENTIFIER != token.type)
    {
      push(token);
      get_token();
      /* error: no identifier found, such as cast case */
    }
	_vsprintf_("declare %s as ", token.string);
	get_token();
}

void
on_array(void)
{
	while ('[' == token.type)
    {
      _vsprintf_("%s ", "array");
      get_token();
      if (isdigit(token.string[0]))
        {
          _vsprintf_("0..%d ", atoi(token.string)-1);
          get_token();
        }
      get_token();
      _vsprintf_("%s ", "of");
    }
}

void
on_function_args(void)
{
	while ('(' == token.type)
    {
      _vsprintf_("function ");
      char buf[MAX_TOKEN_LEN*4];
      int idx = 0;
      char c;
      int depth = 0;
      buf[idx++] = '(';
    nested:
      while (')' != (c = (char)lookahead()))
        {
          if ('(' == c) depth++;
          buf[idx++] = c;
        }
      if (depth)
        {
          depth--;
          buf[idx++] = ')';
          goto nested;
        }
      buf[idx++] = ')';
      buf[idx++] = EOS;
      pushback();
      if (0 != strcmp("()", buf))
        {
          _vsprintf_("%s ", buf);
        }
      get_token();
    }
	get_token();
	_vsprintf_("returning ");
}

void
on_pointer(void)
{
	while ('*' == stack[top].type)
    {
      _vsprintf_("%s ", pop.string);
    }
}

void
on_declarator(void)
{
	switch (token.type)
    {
    case '[':
      on_array();
      break;
    case '(':
      on_function_args();
      break;
    }
	on_pointer();
	while (top >= 0)
    {
      if ('(' == stack[top].type)
        {
          (void)pop;
          get_token();
          on_declarator();
        } else
        {
          _vsprintf_("%s ", pop.string);
        }
    }
}

int main(int argc, char **argv)
{
	if (argc > 1)
    {
      strcpy(inbuf, argv[1]);
      inptr = inbuf;
      outptr = outbuf;
      on_first_identifier();
      on_declarator();
      _vsprintf_("%s", "\n");
      fprintf(stdout, "%s", outbuf);
    }

	return 0;
}
