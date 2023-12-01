#ifndef _CTL_H_
#define _CTL_H_

#include <assert.h>
#include <ncstd.h>
#include <stdio.h>
#include <str.h>
#include <string.h>

int compare_int (int *, int *);
int equal_int (int *, int *);
size_t hash_int (int *);

int compare_double (double *, double *);
int equal_double (double *, double *);
size_t hash_double (double *);

int compare_str (str *, str *);
int equal_str (str *, str *);
size_t hash_str (str *);

typedef struct
{
  uint8_t *data;
  size_t size;
} image;

image image_copy (image *);
image image_init (size_t);
image image_read (void);
void image_free (image *);

int compare_image (image *, image *);
int equal_image (image *, image *);
size_t hash_image (image *);

#endif /* _CTL_H_ */
