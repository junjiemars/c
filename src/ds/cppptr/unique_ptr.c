#include "unique_ptr.h"
#include <nore.h>
#include <stddef.h>
#include <stdlib.h>

UniquePtr *
new_unique_ptr (void *ptr, void (*free_ptr) (void *))
{
  UniquePtr *p;
  if ((p = calloc (1, sizeof (UniquePtr))) == NULL)
    {
      return NULL;
    }
  p->free_ptr = free_ptr;
  p->ptr = ptr;
  return p;
}

void
free_unique_ptr (UniquePtr *p)
{
  if (p)
    {
      if (p->ptr)
        {
          p->free_ptr ((void *)p->ptr);
        }
      p->ptr = NULL;
      p->free_ptr = NULL;
    }
}

UniquePtr *
unique_ptr_move (UniquePtr *dst, UniquePtr *src)
{
  free_unique_ptr (dst);
  if (dst && src)
    {
      *dst = *src;
      src->ptr = NULL;
      src->free_ptr = NULL;
      return dst;
    }
  return NULL;
}
