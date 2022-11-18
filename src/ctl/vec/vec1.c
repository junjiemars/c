#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <vec.h>

#define P
#define T double
#include <vec.h>


#define P
#include <str.h>
#define T str
#include <vec.h>


typedef struct
{
  uint8_t*  data;
  size_t    size;
} image;

void   image_free(image *);
image  image_copy(image *);
#define T image
#include <vec.h>


static int  compare_int(int *a, int *b);
static int  compare_double(double *a, double *b);
static int  compare_str(str *a, str *b);
static int  compare_image(image *a, image *b);

static image  image_init(size_t);
static image  image_read(void);

static void  test_vec_int(void);
static void  test_vec_double(void);
static void  test_vec_str(void);
static void  test_vec_image(void);


int
main(void)
{
  test_vec_int();
  test_vec_double();
  test_vec_str();
  test_vec_image();
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
test_vec_int(void)
{
  vec_int a = vec_int_init();

  vec_int_push_back(&a, 9);
  vec_int_push_back(&a, 1);
  vec_int_push_back(&a, 8);
  vec_int_push_back(&a, 3);
  vec_int_push_back(&a, 4);

  vec_int_sort(&a, compare_int);

  printf("vec<int>\n------------\n");
  foreach(vec_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  vec_int_free(&a);
}

void
test_vec_double(void)
{
  vec_double a = vec_double_init();

  vec_double_push_back(&a, 9);
  vec_double_push_back(&a, 1);
  vec_double_push_back(&a, 8);
  vec_double_push_back(&a, 3);
  vec_double_push_back(&a, 4);

  vec_double_sort(&a, compare_double);

  printf("vec<double>\n------------\n");
  foreach(vec_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  vec_double_free(&a);
}

void
test_vec_str(void)
{
  vec_str a = vec_str_init();

  vec_str_push_back(&a, str_init("9aaa"));
  vec_str_push_back(&a, str_init("1aaa"));
  vec_str_push_back(&a, str_init("8aaa"));
  vec_str_push_back(&a, str_init("3aaa"));
  vec_str_push_back(&a, str_init("4aaa"));

  vec_str_sort(&a, compare_str);

  printf("vec<str>\n------------\n");
  foreach(vec_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  vec_str_free(&a);
}

void
test_vec_image(void)
{
  vec_image a = vec_image_init();
  for(size_t i = 0; i < 5; i++)
    {
      vec_image_push_back(&a, image_read());
    }
  vec_image_sort(&a, compare_image);

  printf("vec<image>\n------------\n");
  foreach(vec_image, &a, it)
    {
      printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size);
    }

  vec_image b = vec_image_copy(&a);
  vec_image_free(&a);
  vec_image_free(&b);
}
