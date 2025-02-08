#include "shared_ptr.h"
#include <nore.h>
#include <stddef.h>
#include <stdlib.h>

SharedPtr *
new_shared_ptr (void *ptr, void (*free_ptr) (void *))
{
  SharedPtr *p;
  if ((p = calloc (1, sizeof (SharedPtr))) == NULL)
    {
      return NULL;
    }
  p->free_ptr = free_ptr;
  if ((p->ptr = ptr) != NULL)
    {
      atomic_init (&p->refs, 1);
    }
  return p;
}

void
free_shared_ptr (SharedPtr *p)
{
  if (p)
    {
      free ((void *)p);
    }
}

SharedPtr *
shared_ptr_copy (SharedPtr *src)
{
  if (src)
    {
      atomic_fetch_add (&src->refs, 1);
    }
  return src;
}

void
shared_ptr_drop (SharedPtr *p)
{
  if (p && atomic_fetch_sub (&p->refs, 1) == 1)
    {
      p->free_ptr ((void *)p->ptr);
      p->ptr = NULL;
    }
}

int
shared_ptr_count (SharedPtr const *p)
{
  if (p)
    {
      return atomic_load (&p->refs);
    }
  return 0;
}
