#include "fn.h"
#include <stdlib.h>
#include <strings.h>

symrec *
putsym (char const *name, int sym_type)
{
  symrec *rs = (symrec *)malloc (sizeof (symrec));
  rs->name = strdup (name);
  rs->type = sym_type;
  rs->value.var = 0;
  rs->next = sym_table;
  sym_table = rs;
  return rs;
}

symrec *
getsym (char const *name)
{
  for (symrec *p = sym_table; p; p = p->next)
    {
      if (strcmp (p->name, name) == 0)
        {
          return p;
        }
    }
  return NULL;
}
