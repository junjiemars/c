#ifndef _UNIQUE_PTR_H_
#define _UNIQUE_PTR_H_

typedef struct UniquePtr
{
  void *ptr;
  void (*free_ptr) (void *);
} UniquePtr;

#define unique_ptr_ref(p, t) ((p) ? (t *)(p)->ptr : NULL)

UniquePtr *new_unique_ptr (void *ptr, void (*free_ptr) (void *));
void free_unique_ptr (UniquePtr *p);
UniquePtr *unique_ptr_move (UniquePtr *dst, UniquePtr *src);

#endif /* _UNIQUE_PTR_H_ */
