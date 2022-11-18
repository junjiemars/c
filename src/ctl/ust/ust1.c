#include "_ctl_.h"
#include <stdio.h>


#define P
#define T int
#include <ust.h>

#define P
#define T double
#include <ust.h>


#define P
#include <str.h>
#define T str
#include <ust.h>


/* typedef struct */
/* { */
/*   uint8_t*  data; */
/*   size_t    size; */
/* } image; */

/* void   image_free(image *); */
/* image  image_copy(image *); */
/* #define T image */
/* #include <ust.h> */


static size_t  int_hash(int *);
static int     int_equal(int *, int *);

static size_t  double_hash(double *);
static int     double_equal(double *, double *);

static size_t  str_hash(str *);
static int     str_equal(str *, str *);


/* static image  image_init(size_t); */
/* static image  image_read(void); */

static void  test_ust_int(void);
static void  test_ust_double(void);
static void  test_ust_str(void);
/* static void  test_ust_image(void); */


int
main(void)
{
  test_ust_int();
  test_ust_double();
  test_ust_str();
  /* test_ust_image(); */
}

size_t
int_hash(int *a)
{
  return (size_t) *a;
}

int
int_equal(int *a, int *b)
{
  return *a == *b;
}

size_t
double_hash(double *a)
{
  return (size_t) *a;
}

int
double_equal(double *a, double *b)
{
  return *a == *b;
}

size_t
str_hash(str *a)
{
  size_t   h  =  0;
  char    *s  =  str_c_str(a);

  while (*s)
    {
      h += *s++;
    }
  return h;
}

int
str_equal(str *a, str *b)
{
  return strcmp(str_c_str(a), str_c_str(b));
}

/* image */
/* image_init(size_t size) */
/* { */
/*   image self = */
/*     { */
/*       .data = malloc(sizeof(*self.data) * size), */
/*       .size = size */
/*     }; */
/*   return self; */
/* } */

/* image */
/* image_read(void) */
/* { */
/*   image im = image_init(rand() % 65536); */
/*   for(size_t i = 0; i < im.size; i++) */
/*     { */
/*       im.data[i] = rand() % UINT8_MAX; */
/*     } */
/*   return im; */
/* } */

/* void image_free(image* self) */
/* { */
/*   free(self->data); */
/*   self->data = NULL; */
/*   self->size = 0; */
/* } */

/* image image_copy(image* self) */
/* { */
/*   image copy = image_init(self->size); */
/*   for(size_t i = 0; i < copy.size; i++) */
/*     { */
/*       copy.data[i] = self->data[i]; */
/*     } */
/*   return copy; */
/* } */


void
test_ust_int(void)
{
  int  d1[]  =  {9, 1, 8, 3, 4};

  ust_int a = ust_int_init(int_hash, int_equal);

  for (size_t i = 0; i < _nof_(d1); i++)
    {
      ust_int_insert(&a, d1[i]);
    }

  printf("ust<int>\n------------\n");

  foreach(ust_int, &a, it)
    {
      printf("%d\n", *it.ref);
    }

  ust_int_free(&a);
}

void
test_ust_double(void)
{
  double  d[]  =  {9.0, 1.0, 8.0, 3.0, 4.0};

  ust_double a = ust_double_init(double_hash, double_equal);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      ust_double_insert(&a, 9);
    }

  printf("ust<double>\n------------\n");

  foreach(ust_double, &a, it)
    {
      printf("%lf\n", *it.ref);
    }

  ust_double_free(&a);
}

void
test_ust_str(void)
{
  char  *d[]  =  {"9a", "1a", "8a", "3a", "4a"};

  ust_str a = ust_str_init(str_hash, str_equal);

  for (size_t i = 0; i < _nof_(d); i++)
    {
      ust_str_insert(&a, str_init(d[i]));
    }

  printf("ust<str>\n------------\n");

  foreach(ust_str, &a, it)
    {
      printf("\"%s\"\n", str_c_str(it.ref));
    }

  ust_str_free(&a);
}

/* void */
/* test_ust_image(void) */
/* { */
/*   ust_image a = ust_image_init(); */

/*   for(size_t i = 0; i < 5; i++) */
/*     { */
/*       ust_image_insert(&a, image_read()); */
/*     } */

/*   printf("ust<image>\n------------\n"); */

/*   foreach(ust_image, &a, it) */
/*     { */
/*       printf("\"{ %d, %zu }\"\n", *it.ref->data, it.ref->size); */
/*     } */

/*   ust_image b = ust_image_copy(&a); */

/*   ust_image_free(&a); */
/*   ust_image_free(&b); */
/* } */
