#ifndef FN_H
#define FN_H

#include "../_flex_.h"

typedef double (Fn) (double);

typedef struct SymbolTable
{
  char *name;
  int type;
  union
  {
    double var;
    Fn *fun;
  } value;
  struct SymbolTable *next;
} SymbolTable;

extern SymbolTable *sym_table;

SymbolTable *putsym (char const *name, int sym_type);
SymbolTable *getsym (char const *name);

#endif
