#ifndef _SHARED_H_
#define _SHARED_H_

#include <stdatomic.h>

typedef struct SharedPtr
{
  void *ptr;
  void (*free_ptr) (void *);
  atomic_int refs;
} SharedPtr;

#define shared_ptr_ref(p, t) ((p) ? (t *)(p)->ptr : NULL)

SharedPtr *new_shared_ptr (void *ptr, void (*free_ptr) (void *));
void free_shared_ptr (SharedPtr *p);
SharedPtr *shared_ptr_copy (SharedPtr *src);
void shared_ptr_drop (SharedPtr *p);
int shared_ptr_count (SharedPtr const *p);

#endif /* _SHARED_H_ */
