#include "_hash_.h"
#include <errno.h>
#include <nbits.h>

#if !defined(HASH_MAX) || (HASH_MAX < 1)
#define HASH_MAX 64
#endif

#if !defined(HASH_N) || (HASH_N < HASH_MAX - 3)
#define HASH_N (HASH_MAX + 3)
#endif

#define HASH_NONE NULL
#define hash_loc(x) ((x) % HASH_N + 1)

static void dump_table (int ninsert);
static void free_table (void);

static char const *hash_table[HASH_N + 1] = { 0 };

int
insert (char const *ss)
{
  char const **s1;
  unsigned long h;
  static int n = 0;
  h = hash_loc (hash (ss));
  s1 = &hash_table[h];
  while (*s1 != HASH_NONE && strcmp (*s1, ss) != 0)
    {
      h = hash_loc (h);
      s1 = &hash_table[h];
    }
  if (n >= HASH_MAX)
    {
      return EOVERFLOW;
    }
  *s1 = ss;
  n++;
  return 0;
}

char const *
search (char const *ss)
{
  char const **s1;
  unsigned long h;
  h = hash_loc (hash (ss));
  s1 = &hash_table[h];
  while (*s1 != HASH_NONE && strcmp (*s1, ss) != 0)
    {
      h = hash_loc (h);
      s1 = &hash_table[h];
    }
  return *s1;
}

void
print_hash (const char *name, const char *ss, unsigned long hash)
{
  printf ("%s\n------------\n%s -> %16lu\n" BPRI64 "\n", name, ss, hash,
          BIT64 ((uint64_t)hash));
}

void
test_hash (FILE *in)
{
  int rc;
  int n = 0;
  char ss[64];

  while (fscanf (in, "%s", ss) == 1)
    {
      rc = insert (strdup (ss));
      n++;
      if (rc)
        {
          perror (NULL);
          break;
        }
    }
  fclose (in);
  dump_table (n);
  free_table ();
}

void
dump_table (int ninsert)
{
  int distinct = 0;
  size_t total = sizeof (hash_table) / sizeof (hash_table[0]);
  for (size_t i = 0; i < total; i++)
    {
      if (hash_table[i] != HASH_NONE)
        {
          printf ("%zu: %s\n", i, hash_table[i]);
          distinct++;
        }
    }
  printf ("------------\ntable (%d,%d)/%zu\n", distinct, ninsert, total);
}

void
free_table (void)
{
  for (char const **ss = hash_table; *ss != HASH_NONE; ss++)
    {
      free ((void *)*ss);
      *ss = HASH_NONE;
    }
}
