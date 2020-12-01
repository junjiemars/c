#include <_algo_.h>

typedef struct s_merge
{
  void *base;
  size_t nel;
  size_t idx;
} merge_t;

void
merge(merge_t * const l, merge_t * const r, merge_t * const m,
      size_t width,
      int (*comp)(const void*lhs, const void *rhs))
{
  if ((l->idx == l->nel) && (r->idx == r->nel))
    {
      return;
    }
  else if (l->idx == l->nel)
    {
      size_t n = r->nel - r->idx;
      memcpy((char*)m->base + m->idx * width,
             (char*)r->base + r->idx * width,
             n * width);
      m->idx += n;
      m->nel += n;
      r->idx += n;
    }
  else if (r->idx == r->nel)
    {
      size_t n = l->nel - l->idx;
      memcpy((char*)m->base + m->idx * width,
             (char*)l->base + l->idx * width,
             n * width);
      m->idx += n;
      m->nel += n;
      l->idx += n;
    }
  else if (comp((char*)l->base + l->idx * width,
                (char*)r->base + r->idx * width) <= 0)
    {
      memcpy((char*)m->base + m->idx++ * width,
             (char*)l->base + l->idx++ * width,
             width);
      m->nel++;
    }
  else
    {
      memcpy((char*)m->base + m->idx++ * width,
             (char*)r->base + r->idx++ * width,
             width);
      m->nel++;
    }
  merge(l, r, m, width, comp);
}

void
test_merge_int(void)
{
  int al[] = {21, 28, 35, 40, 61, 75};
  int ar[] = {16, 25, 47, 54 };
  int am[sizeof(al)/sizeof(*al) + sizeof(ar)/sizeof(*ar)];
  merge_t l, r, m;
  l.base = &al[0];
  l.nel = sizeof(al)/sizeof(*al);
  l.idx = 0;
  r.base = &ar[0];
  r.nel = sizeof(ar)/sizeof(*ar);
  r.idx = 0;
  m.base = &am[0];
  m.nel = 0;
  m.idx = 0;

  printf("merge int array ...\n----------\n");
  list_array(al, sizeof(al)/sizeof(*al), sizeof(*al), print_int);
  list_array(ar, sizeof(ar)/sizeof(*ar), sizeof(*ar), print_int);
  printf("----------\n");
  
  merge(&l, &r, &m, sizeof(int), comp_int);

  list_array(am, sizeof(am)/sizeof(*am), sizeof(*am), print_int);
}

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

  test_merge_int();
  
	return 0;
}
