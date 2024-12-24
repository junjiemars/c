#ifndef AST_H
#define AST_H

#include "../_flex_.h"

extern int yylineno;

typedef enum AstNodeType
{
  ANT_NUM = 0,
  ANT_ADD,
  ANT_SUB,
  ANT_MUL,
  ANT_DIV,
  ANT_NEG
} AstNodeType;

typedef struct Ast
{
  AstNodeType type;
  double val;
  struct Ast *lhs;
  struct Ast *rhs;
} Ast;

Ast *new_ast (AstNodeType type, void *val, Ast *lhs, Ast *rhs);
Ast *new_ast_val (double val);
void free_ast (Ast *ast);
double eval_ast (Ast *ast);

#endif /* AST_H */
