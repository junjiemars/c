#include "lang.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_TABLE_MAX 64
#define N_VAR_TABLE (VAR_TABLE_MAX + 3)

#define FUN_TABLE_MAX 64
#define N_FUN_TABLE (FUN_TABLE_MAX + 3)

extern void yyerror (char const *, ...);

typedef double (*FunPtr) (double);

typedef struct Var
{
  Ast *ast;
  int builtin;
} Var;

static unsigned long hash (char const *);
static FunPtr lookup_ast_fun (char const *name);
static double fact (double);

static Var var_table[N_VAR_TABLE + 1];
static FunPtr fun_table[N_FUN_TABLE + 1];
static double var_e = (double)M_E;
static double var_pi = (double)M_PI;

Ast *
new_ast (AstNodeType type, void *val, Ast *lhs, Ast *rhs)
{
  Ast *ast;
  int err;
  if (!(ast = calloc (1, sizeof (Ast))))
    {
      err = errno;
      yyerror ("cannot alloc memory");
      exit (err);
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
  unsigned long h = hash (name);
  Var *var = &var_table[h];
  if (var->builtin)
    {
      yyerror ("var is builtin: %s", name);
      return var->ast;
    }
  rhs->val = eval_ast (rhs);
  var->ast = new_ast (ANT_VAR, &rhs->val, NULL, rhs);
  return var->ast;
}

Ast *
new_ast_fun (char const *name, Ast *rhs)
{
  Ast *ast;
  FunPtr fptr;
  rhs->val = eval_ast (rhs);
  ast = new_ast (ANT_FUN, &rhs->val, NULL, rhs);
  ast->val = NAN;
  fptr = lookup_ast_fun (name);
  if (fptr == NULL)
    {
      yyerror ("fun is invalid: %s", name);
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
    case ANT_FUN:
      if (ast->rhs)
        {
          free_ast (ast->rhs);
          ast->rhs = NULL;
        }
      break;
    case ANT_ABS:
    case ANT_ADD:
    case ANT_SUB:
    case ANT_MUL:
    case ANT_DIV:
    case ANT_MOD:
    case ANT_POW:
      if (ast->rhs)
        {
          free_ast (ast->rhs);
          ast->rhs = NULL;
        }
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
  Var *var = &var_table[h];
  if (var->ast == NULL)
    {
      var->ast = new_ast (ANT_VAR, NULL, NULL, NULL);
      yyerror ("var is invalid: %s", name);
      var->ast->errnum = ENOENT;
      var->ast->val = NAN;
    }
  return var->ast;
}

FunPtr
lookup_ast_fun (char const *name)
{
  unsigned long h = hash (name);
  return fun_table[h];
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
    case ANT_ABS:
      val = fabs (eval_ast (ast->rhs));
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
  var_table[hash ("e")] = (Var){
    .ast = new_ast (ANT_VAR, &var_e, NULL, NULL),
    .builtin = 1,
  };
  var_table[hash ("PI")]
      = (Var){ .ast = new_ast (ANT_VAR, &var_pi, NULL, NULL), .builtin = 1 };

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
      if (var_table[i].ast)
        {
          free (var_table[i].ast);
          var_table[i].ast = NULL;
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

unsigned long
hash (char const *str)
{
  int c;
  unsigned long h;
  for (h = 0; (c = *str) != 0; str++)
    {
      h = h * 9 ^ c;
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
