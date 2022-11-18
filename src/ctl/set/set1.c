#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <set.h>

#define P
#define T double
#include <set.h>


#define P
#include <str.h>
#define T str
#include <set.h>


typedef struct
{
  uint8_t*  data;
  size_t    size;
} image;

void   image_free(image *);
image  image_copy(image *);
#define T image
#include <set.h>


static int  compare_int(int *a, int *b);
static int  compare_double(double *a, double *b);
static int  compare_str(str *a, str *b);
static int  compare_image(image *a, image *b);

static image  image_init(size_t);
static image  image_read(void);

static void  test_set_int(void);
static void  test_set_double(void);
static void  test_set_str(void);
static void  test_set_image(void);


int
main(void)
{
  test_set_int();
  test_set_double();
  test_set_str();
  test_set_image();
}


int
compare_int(int* a, int* b)
{
  return (*a) > (*b);
}

int
compare_double(double *a, double *b)
{
  return (*a) > (*b);
}

int
compare_str(str *a, str *b)
{
  return strcmp(str_c_str(a), str_c_str(b)) > 0;
}

int
compare_image(image *a, image *b)
{
  return (*a->data > *b->data) && (a->size > b->size);
}

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

void image_free(image* self)
{
  free(self->data);
  self->data = NULL;
  self->size = 0;
}

image image_copy(image* self)
{
  image copy = image_init(self->size);
  for(size_t i = 0; i < copy.size; i++)
    {
      copy.data[i] = self->data[i];
    }
  return copy;
}


void
test_set_int(void)
{
  int  d[]  =  {9, 1, 8, 3, 4};

  set_int a = set_int_init(compare_int);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      set_int_insert(&a, d[i]);
    }

  printf("set<int>\n------------\n");

  foreach(set_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  set_int_free(&a);
}

void
test_set_double(void)
{
  double  d[]  =  {9.0, 1.0, 8.0, 3.0, 4.0};

  set_double a = set_double_init(compare_double);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      set_double_insert(&a, 9);
    }

  printf("set<double>\n------------\n");

  foreach(set_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  set_double_free(&a);
}

void
test_set_str(void)
{
  char  *d[]  =  {"9a", "1a", "8a", "3a", "4a"};

  set_str a = set_str_init(compare_str);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      set_str_insert(&a, str_init(d[i]));
    }

  printf("set<str>\n------------\n");

  foreach(set_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  set_str_free(&a);
}

void
test_set_image(void)
{
  set_image a = set_image_init(compare_image);

  for(size_t i = 0; i < 5; i++)
    {
      set_image_insert(&a, image_read());
    }

  printf("set<image>\n------------\n");

  foreach(set_image, &a, it)
    {
      printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size);
    }

  set_image b = set_image_copy(&a);

  set_image_free(&a);
  set_image_free(&b);
}
