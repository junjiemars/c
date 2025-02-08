#include "unique_ptr.h"
#include <stddef.h>

UniquePtr
new_unique_ptr (void *datum, void (*free_datum) (void *))
{
  UniquePtr ptr = {
    .datum = datum,
    .free_datum = free_datum,
  };
  return ptr;
}

void
free_unique_ptr (UniquePtr *ptr)
{
  if (ptr)
    {
      if (ptr->datum)
        {
          ptr->free_datum ((void *)ptr->datum);
        }
      ptr->datum = NULL;
      ptr->free_datum = NULL;
    }
}

UniquePtr *
unique_ptr_move (UniquePtr *dst, UniquePtr *src)
{
  free_unique_ptr (dst);
  if (dst && src)
    {
      *dst = *src;
      src->datum = NULL;
      src->free_datum = NULL;
      return dst;
    }
  return NULL;
}
