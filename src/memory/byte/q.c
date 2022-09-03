#include "_memory_.h"
#include <float.h>
#include <string.h>


#if defined(BIT8_SUF)
#  undef BIT8_SUF
#endif
#define BIT8_SUF  "\n"



typedef union
{
  float     f;
  uint32_t  u;
  struct
  {
    uint32_t sign:      1;      /* (u & 0x007fffff) */
    uint32_t exponent:  8;      /* ((u & 0x07800000) >> 23) */
    uint32_t mantissa: 23;      /* (u >> 31) */
  } layout;
} ufloat32_t;


static void inspect_int(const char*, const char*, const char*);
static void inspect_float(const char*, const char*, const char*);


int
main(int argc, char **argv)
{
  const char  *opt_type;
  const char  *opt_val;
  const char  *opt_radix;

  if (argc < 4)
    {
      printf("usage: <type> <value> <radix>\n");
      return 0;
    }


  opt_type = argv[1];
  opt_val = argv[2];
  opt_radix = argv[3];

  if (strcmp(opt_type, "int") == 0)
    {
      inspect_int(opt_type, opt_val, opt_radix);
    }
  else if (strcmp(opt_type, "float") == 0)
    {
      inspect_float(opt_type, opt_val, opt_radix);
    }

  return 0;
}

void
inspect_int(const char *t, const char *v, const char *r)
{
  int  rc;
  int  val;

  printf("%s: %s\n------------\n", t, v);

  rc = sscanf(v, "%i", &val);
  if (rc < 1)
    {
      perror(NULL);
      return;
    }

  if (strcmp(r, "2") == 0)
    {
      printf(BPRI8, BIT8(val));
    }
  else if (strcmp(r, "16") == 0)
    {
      printf("%x\n", val);
    }
  else if (strcmp(r, "A") == 0)
    {
      printf(BPRI8, BIT8(val));
      printf("%x\n", val);
    }

}

void
inspect_float(const char *t, const char *v, const char *r)
{
  int         rc;
  ufloat32_t  val;

  printf("%s: %s\n------------\n", t, v);

  rc = sscanf(v, "%f", (float*) &val);
  if (rc < 1)
    {
      perror(NULL);
      return;
    }

  if (strcmp(r, "2") == 0)
    {
      printf(BPRI32, BIT32(val.u));
    }
  else if (strcmp(r, "16") == 0)
    {
      printf("%x\n", val.u);
    }
  else if (strcmp(r, "A") == 0)
    {
      printf(BPRI32, BIT32(val.u));
      printf("%x\n", val.u);
    }
}
