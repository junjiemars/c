#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <que.h>

#define P
#define T double
#include <que.h>


#define P
#include <str.h>
#define T str
#include <que.h>


typedef struct
{
  uint8_t*  data;
  size_t    size;
} image;

void   image_free(image *);
image  image_copy(image *);
#define T image
#include <que.h>

static image  image_init(size_t);
static image  image_read(void);

static void  test_que_int(void);
static void  test_que_double(void);
static void  test_que_str(void);
static void  test_que_image(void);


int
main(void)
{
  test_que_int();
  test_que_double();
  test_que_str();
  test_que_image();
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
test_que_int(void)
{
  que_int a = que_int_init();

  que_int_push(&a, 9);
  que_int_push(&a, 1);
  que_int_push(&a, 8);
  que_int_push(&a, 3);
  que_int_push(&a, 4);

  printf("que<int>\n------------\n");

  que_int_free(&a);
}

void
test_que_double(void)
{
  que_double a = que_double_init();

  que_double_push(&a, 9);
  que_double_push(&a, 1);
  que_double_push(&a, 8);
  que_double_push(&a, 3);
  que_double_push(&a, 4);

  printf("que<double>\n------------\n");

  que_double_free(&a);
}

void
test_que_str(void)
{
  que_str a = que_str_init();

  que_str_push(&a, str_init("9aaa"));
  que_str_push(&a, str_init("1aaa"));
  que_str_push(&a, str_init("8aaa"));
  que_str_push(&a, str_init("3aaa"));
  que_str_push(&a, str_init("4aaa"));

  printf("que<str>\n------------\n");

  que_str_free(&a);
}

void
test_que_image(void)
{
  que_image a = que_image_init();
  for(size_t i = 0; i < 5; i++)
    {
      que_image_push(&a, image_read());
    }

  printf("que<image>\n------------\n");

  que_image b = que_image_copy(&a);
  que_image_free(&a);
  que_image_free(&b);
}
