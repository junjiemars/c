#include "_stdio_.h"


/*
 * 1. Direct IO is supported by `fread(3)' and `fwrite(3)'
 *
 *
 */


#define NAME_SIZE 16
#define MAX 16
#define PANIC "!panic"

typedef struct sassy_s
{
  char    name[NAME_SIZE];
  int     age;
  char    gender;
  double  allowance;
} sassy_s;

static void in(const char *path, sassy_s *ss, size_t *nss, size_t max);
static void out(const char *path, const sassy_s *ss, size_t nss);

static void test_in(const char *path);
static void test_out(const char *path);


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "where the sassy file located?\n");
      return 1;
    }

  test_out(argv[1]);
  test_in(argv[1]);

  return 0;
}


void
in(const char *path, sassy_s *ss, size_t *nss, size_t max)
{
  FILE *in = fopen(path, "rb");
  if (!in)
    {
      perror(PANIC);
      return;
    }

  size_t n = 0;
  *nss = 0;

  while (*nss < max)
    {
      n = fread(ss, sizeof(sassy_s), 1, in);

      if (ferror(in))
        {
          perror(PANIC);
          goto clean_exit;
        }

      if (n != 1)
        {
          if (feof(in))
            {
              goto clean_exit;
            }
          fprintf(stderr, "!panic, read %zu/%i failed\n", n, 1);
          goto clean_exit;
        }

      ss++;
      *nss += 1;
    }

 clean_exit:
  fclose(in);
}

void
out(const char *path, const sassy_s *ss, const size_t nss)
{
  FILE *out = fopen(path, "ab");
  if (!out)
    {
      perror(PANIC);
      return;
    }

  size_t n = fwrite(ss, sizeof(sassy_s), nss, out);

  if (ferror(out))
    {
      perror(path);
      goto clean_exit;
    }

  if (n < nss)
    {
      fprintf(stderr, "!panic, write %zu/%zu failed\n", n, nss);
    }

 clean_exit:
  fclose(out);
}

void
test_out(const char *path)
{
  sassy_s ss[] =
    {
      {
        .name = {"Anne"},
        .age = 0x11,
        .gender = 'F',
        .allowance = 11.22,
      },
      {
        .name = {"Bourn"},
        .age = 0x22,
        .gender = 'M',
        .allowance = 22.33,
      },
      {
        .name = {"Caton"},
        .age = 0x33,
        .gender = 'M',
        .allowance = 33.44,
      },
    };

  out(path, ss, sizeof(ss)/sizeof(*ss));
}

void
test_in(const char *path)
{
  sassy_s *ss;
  size_t nss = 0;

  ss = malloc(sizeof(sassy_s) * MAX);
  if (!ss)
    {
      perror(PANIC);
      return;
    }

  in(path, ss, &nss, MAX);

  for (size_t i = 0; i < nss; i++)
    {
      fprintf(stdout,
              "No.%zu\n"
              "----\n"
              "name:%s\n"
              "age:%d\n"
              "gender:%c\n"
              "allowance:%lf\n",
              i+1,
              ss[i].name,
              ss[i].age,
              ss[i].gender,
              ss[i].allowance);
    }

  free(ss);
}
