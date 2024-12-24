#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ast *
new_ast (AstNodeType type, void *val, Ast *lhs, Ast *rhs)
{
  Ast *ast;
  if (!(ast = malloc (sizeof (Ast))))
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

void
free_ast (Ast *ast)
{
  switch (ast->type)
    {
    case ANT_ADD:
    case ANT_SUB:
    case ANT_MUL:
    case ANT_DIV:
      free_ast (ast->rhs);
    case ANT_NEG:
      if (ast->lhs)
        {
          free_ast (ast->lhs);
        }
    case ANT_NUM:
      free (ast);
      break;
    }
}

double
eval_ast (Ast *ast)
{
  double val;
  switch (ast->type)
    {
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
    case ANT_NEG:
      val = -eval_ast (ast->rhs);
      break;
    case ANT_NUM:
      val = ast->val;
      break;
    }
  return val;
}
