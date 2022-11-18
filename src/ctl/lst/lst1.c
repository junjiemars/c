#include "_ctl_.h"
#include <stdio.h>
#include <assert.h>


#define P
#define T int
#include <lst.h>

#define P
#define T double
#include <lst.h>


#define P
#include <str.h>
#define T str
#include <lst.h>


typedef struct
{
  uint8_t*  data;
  size_t    size;
} image;

void   image_free(image *);
image  image_copy(image *);
#define T image
#include <lst.h>


static int  compare_int(int *a, int *b);
static int  compare_double(double *a, double *b);
static int  compare_str(str *a, str *b);
static int  compare_image(image *a, image *b);

static image  image_init(size_t);
static image  image_read(void);

static void  test_lst_int(void);
static void  test_lst_double(void);
static void  test_lst_str(void);
static void  test_lst_image(void);


int
main(void)
{
  test_lst_int();
  test_lst_double();
  test_lst_str();
  test_lst_image();
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
test_lst_int(void)
{
  lst_int a = lst_int_init();

  assert(lst_int_empty(&a));

  lst_int_push_back(&a, 9);
  lst_int_push_back(&a, 1);
  lst_int_push_back(&a, 8);
  lst_int_push_back(&a, 3);
  lst_int_push_back(&a, 4);

  assert(a.size == 5);

  lst_int_sort(&a, compare_int);

  printf("lst<int>\n------------\n");
  foreach(lst_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  lst_int_free(&a);
}

void
test_lst_double(void)
{
  lst_double a = lst_double_init();

  lst_double_push_back(&a, 9);
  lst_double_push_back(&a, 1);
  lst_double_push_back(&a, 8);
  lst_double_push_back(&a, 3);
  lst_double_push_back(&a, 4);

  lst_double_sort(&a, compare_double);

  printf("lst<double>\n------------\n");
  foreach(lst_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  lst_double_free(&a);
}

void
test_lst_str(void)
{
  lst_str a = lst_str_init();

  lst_str_push_back(&a, str_init("9aaa"));
  lst_str_push_back(&a, str_init("1aaa"));
  lst_str_push_back(&a, str_init("8aaa"));
  lst_str_push_back(&a, str_init("3aaa"));
  lst_str_push_back(&a, str_init("4aaa"));

  lst_str_sort(&a, compare_str);

  printf("lst<str>\n------------\n");
  foreach(lst_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  lst_str_free(&a);
}

void
test_lst_image(void)
{
  lst_image a = lst_image_init();
  for(size_t i = 0; i < 5; i++)
    {
      lst_image_push_back(&a, image_read());
    }
  lst_image_sort(&a, compare_image);

  printf("lst<image>\n------------\n");
  foreach(lst_image, &a, it)
    {
      printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size);
    }

  lst_image b = lst_image_copy(&a);
  lst_image_free(&a);
  lst_image_free(&b);
}
