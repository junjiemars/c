#include "ast.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_TABLE_MAX 60
#define N_VAR_TABLE (VAR_TABLE_MAX + 4)

#define FUN_TABLE_MAX 60
#define N_FUN_TABLE (FUN_TABLE_MAX + 4)

extern void yyerror (char const *);

typedef double (*FunPtr) (double);

static unsigned long hash (char const *);
static void put_var_table (char const *name, Ast *ast);
static FunPtr lookup_ast_fun (char const *name);
static double fact (double);

static Ast *var_table[N_VAR_TABLE + 1];
static FunPtr fun_table[N_FUN_TABLE + 1];
static double var_e = (double)M_E;
static double var_pi = (double)M_PI;

Ast *
new_ast (AstNodeType type, void *val, Ast *lhs, Ast *rhs)
{
  Ast *ast;
  if (!(ast = calloc (1, sizeof (Ast))))
    {
      perror (NULL);
    }
  ast->type = type;
  if (val != NULL)
    {
      ast->val = *(double *)val;
    }
  ast->lhs = lhs;
  ast->rhs = rhs;
  return ast;
}

Ast *
new_ast_val (double val)
{
  Ast *ast = new_ast (ANT_NUM, &(val), NULL, NULL);
  return ast;
}

Ast *
new_ast_var (char const *name, Ast *rhs)
{
  Ast *ast;
  rhs->val = eval_ast (rhs);
  ast = new_ast (ANT_VAR, &rhs->val, NULL, rhs);
  put_var_table (name, ast);
  return ast;
}

Ast *
new_ast_fun (char const *name, Ast *rhs)
{
  Ast *ast;
  FunPtr fptr;
  char err[BUFSIZ] = { 0 };
  rhs->val = eval_ast (rhs);
  ast = new_ast (ANT_FUN, &rhs->val, NULL, rhs);
  ast->val = NAN;
  fptr = lookup_ast_fun (name);
  if (fptr == NULL)
    {
      snprintf (err, BUFSIZ, "invalid fun: %s", name);
      yyerror (err);
      ast->errnum = ENOENT;
      return ast;
    }
  ast->val = fptr (rhs->val);
  return ast;
}

void
free_ast (Ast *ast)
{
  switch (ast->type)
    {
    case ANT_VAR:
      if (ast->rhs)
        {
          free (ast->rhs);
          ast->rhs = NULL;
        }
      break;
    case ANT_FUN:
      free_ast (ast->rhs);
      break;
    case ANT_ADD:
    case ANT_SUB:
    case ANT_MUL:
    case ANT_DIV:
    case ANT_MOD:
    case ANT_POW:
      free_ast (ast->rhs);
    case ANT_FAC:
    case ANT_NEG:
      if (ast->lhs)
        {
          free_ast (ast->lhs);
          ast->lhs = NULL;
        }
    case ANT_NUM:
      free (ast);
      ast = NULL;
      break;
    }
}

Ast *
lookup_ast_var (char const *name)
{
  unsigned long h = hash (name);
  Ast *ast = var_table[h];
  char err[BUFSIZ] = { 0 };
  if (ast == NULL)
    {
      ast = new_ast (ANT_VAR, NULL, NULL, NULL);
      snprintf (err, BUFSIZ, "invalid var: %s", name);
      yyerror (err);
      ast->errnum = ENOENT;
      ast->val = NAN;
    }
  return ast;
}

FunPtr
lookup_ast_fun (char const *name)
{
  unsigned long h = hash (name);
  FunPtr fptr = fun_table[h];
  return fptr;
}

double
eval_ast (Ast *ast)
{
  double val;
  switch (ast->type)
    {
    case ANT_NUM:
      val = ast->val;
      break;
    case ANT_VAR:
      val = ast->val;
      break;
    case ANT_FUN:
      val = ast->val;
      break;
    case ANT_ADD:
      val = eval_ast (ast->lhs) + eval_ast (ast->rhs);
      break;
    case ANT_SUB:
      val = eval_ast (ast->lhs) - eval_ast (ast->rhs);
      break;
    case ANT_MUL:
      val = eval_ast (ast->lhs) * eval_ast (ast->rhs);
      break;
    case ANT_DIV:
      val = eval_ast (ast->lhs) / eval_ast (ast->rhs);
      break;
    case ANT_MOD:
      val = fmod (eval_ast (ast->lhs), eval_ast (ast->rhs));
      break;
    case ANT_FAC:
      val = fact (eval_ast (ast->rhs));
      break;
    case ANT_POW:
      val = pow (eval_ast (ast->lhs), eval_ast (ast->rhs));
      break;
    case ANT_NEG:
      val = -eval_ast (ast->rhs);
      break;
    }
  return val;
}

void
init_sym_table (void)
{
  memset (var_table, 0, sizeof (var_table));
  memset (fun_table, 0, sizeof (fun_table));

  /* variable table */
  var_table[hash ("e")] = new_ast (ANT_VAR, &var_e, NULL, NULL);
  var_table[hash ("PI")] = var_table[hash ("π")]
      = new_ast (ANT_VAR, &var_pi, NULL, NULL);

  /* function table */
  fun_table[hash ("atan")] = atan;
  fun_table[hash ("ceil")] = ceil;
  fun_table[hash ("cos")] = cos;
  fun_table[hash ("exp")] = exp;
  fun_table[hash ("fabs")] = fabs;
  fun_table[hash ("floor")] = floor;
  fun_table[hash ("ln")] = log;
  fun_table[hash ("log")] = log10;
  fun_table[hash ("round")] = round;
  fun_table[hash ("sin")] = sin;
  fun_table[hash ("sqrt")] = sqrt;
  fun_table[hash ("tan")] = tan;
}

void
free_sym_table (void)
{
  for (int i = 0; i < sizeof (var_table) / sizeof (*var_table); i++)
    {
      if (var_table[i])
        {
          free (var_table[i]);
          var_table[i] = NULL;
        }
    }
  for (int i = 0; i < sizeof (fun_table) / sizeof (*fun_table); i++)
    {
      if (fun_table[i])
        {
          free (fun_table[i]);
          fun_table[i] = NULL;
        }
    }
}

void
put_var_table (char const *name, Ast *ast)
{
  unsigned long h = hash (name);
  var_table[h] = ast;
}

unsigned long
hash (char const *str)
{
  unsigned long h;
  unsigned long w = 3;
  for (h = 0; *str; str++)
    {
      h += w * (*str);
      w += 2;
    }
  return h % N_VAR_TABLE + 1;
}

double
fact (double d)
{
  long n = (long)d;
  double acc = 1;
  while (n > 1)
    {
      acc *= n--;
    }
  return acc;
}
