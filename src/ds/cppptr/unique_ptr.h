#ifndef _UNIQUE_PTR_H_
#define _UNIQUE_PTR_H_

#include <nore.h>

typedef struct UniquePtr
{
  void *datum;
  void (*free_datum) (void *);
} UniquePtr;

#define unique_ptr_ref(p, t) ((p) ? (t *)(p)->datum : NULL)

UniquePtr new_unique_ptr (void *, void (*free) (void *));
void free_unique_ptr (UniquePtr *);
UniquePtr *unique_ptr_move (UniquePtr *, UniquePtr *);

#endif /* _UNIQUE_PTR_H_ */
