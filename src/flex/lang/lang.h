#ifndef LANG_H
#define LANG_H

#include "../_flex_.h"

extern int yylineno;

typedef enum AstNodeType
{
  ANT_NUM = 0,
	ANT_SEQ,
  ANT_VAR,
  ANT_FUN,
  ANT_ABS,
  ANT_ADD,
  ANT_SUB,
  ANT_MUL,
  ANT_DIV,
  ANT_MOD,
  ANT_FAC,
  ANT_POW,
  ANT_NEG
} AstNodeType;

typedef struct Ast
{
  AstNodeType type;
  double val;
  int errnum;
  struct Ast *lhs;
  struct Ast *rhs;
} Ast;

void yyerror (char const *fmt, ...);

Ast *new_ast (AstNodeType type, void *val, Ast *lhs, Ast *rhs);
Ast *new_ast_val (double val);
Ast *new_ast_var (char const *name, Ast *rhs);
Ast *new_ast_fun (char const *name, Ast *rhs);
void free_ast (Ast *ast);
Ast *lookup_ast_var (char const *name);
double eval_ast (Ast *ast);
void init_sym_table (void);
void free_sym_table (void);

#endif /* LANG_H */
