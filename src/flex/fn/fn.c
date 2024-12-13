#include "fn.h"
#include <stdlib.h>
#include <string.h>

SymbolTable *
putsym (char const *name, int sym_type)
{
  SymbolTable *rs = (SymbolTable *)malloc (sizeof (SymbolTable));
  rs->name = strdup (name);
  rs->type = sym_type;
  rs->value.var = 0;
  rs->next = sym_table;
  sym_table = rs;
  return rs;
}

SymbolTable *
getsym (char const *name)
{
  for (SymbolTable *p = sym_table; p; p = p->next)
    {
      if (strcmp (p->name, name) == 0)
        {
          return p;
        }
    }
  return NULL;
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
