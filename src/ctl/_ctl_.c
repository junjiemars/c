#include "_ctl_.h"

#if (DARWIN && CLANG)
#  pragma clang diagnostic ignored "-Wunused-variable"
#endif


int
compare_int(int *a, int *b)
{
  return *a > *b;
}

int
equal_int(int *a, int *b)
{
  return *a == *b;
}

size_t
hash_int(int *a)
{
  return *a;
}


int
compare_double(double *a, double *b)
{
  return *a > *b;
}

int
equal_double(double *a, double *b)
{
  return *a == *b;
}

size_t
hash_double(double *a)
{
  return (size_t) *a;
}

int
compare_str(str *a, str *b)
{
  return strcmp(str_c_str(a), str_c_str(b)) > 0;
}

int
equal_str(str *a, str *b)
{
  return strcmp(str_c_str(a), str_c_str(b)) == 0;
}

size_t
hash_str(str *a)
{
	size_t   h;
  char    *s  =  str_c_str(a);

	for (h = 0; *s; s++)
    {
      h = *s + 31 * h;
    }
	return h % 1024;
}


/* image */

image
image_init(size_t size)
{
  image self =
    {
      .data = malloc(sizeof(*self.data) * size),
      .size = size
    };
  return self;
}

image
image_read(void)
{
  image im = image_init(rand() % 65536);
  for(size_t i = 0; i < im.size; i++)
    {
      im.data[i] = rand() % UINT8_MAX;
    }
  return im;
}

void image_free(image *self)
{
  free(self->data);
  self->data = NULL;
  self->size = 0;
}

image image_copy(image *self)
{
  image copy = image_init(self->size);
  for(size_t i = 0; i < copy.size; i++)
    {
      copy.data[i] = self->data[i];
    }
  return copy;
}

int
compare_image(image *a, image *b)
{
  return (*a->data > *b->data) && (a->size > b->size);
}

size_t
hash_image(image *a)
{
  return (size_t) (a->data[0] + a->size);
}

int
equal_image(image *a, image *b)
{
  while (a->data && (*a->data == *b->data))
    {
      a->data++, b->data++;
    }
  return *a->data - *b->data;
}


/* eof */
