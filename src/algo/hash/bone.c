#include "../_algo_.h"
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>

#if !defined(M) || ((M + 0) < 1)
#define M 20
#endif

#if !defined(N) || ((N + 0) < (M - 3))
#define N (M + 3)
#endif

#define H(x) ((x) % N + 1)
#define HE(x) (hash_table[(x)])
#define EMPTY 0

#define RD_NUM 0
#define RD_STR 1

#ifndef FN_RD
#define FN_RD RD_NUM
#endif

#define LOC_LINEAR 0
#define LOC_QUADRATIC 1
#define LOC_DOUBLE 2
#define LOC_CHAIN 3

#ifndef FN_LOC
#define FN_LOC LOC_LINEAR
#endif

#define PE(f) (probe_table[(f)])

typedef struct Node
{
  unsigned num;
  unsigned freq;
  int used;
  char str[32];
  int alpha;
  struct Node *next;
} Node;

typedef int (*FnRead) (FILE *, Node *);
typedef int (*FnProbe) (unsigned);

int insert_table (Node *, unsigned *, FnProbe);
int search_table (unsigned, Node **);
int delete_entry (unsigned);
int read_number (FILE *, Node *);
int read_string (FILE *, Node *);
int probe_linear (unsigned);
int probe_quadratic (unsigned);
int probe_double_hashing (unsigned);
int probe_chain (unsigned);
unsigned get_relative_prime (unsigned);
unsigned str_to_num (char const *, unsigned);
int alpha_order (char const *);
void dump_table (void);
static void usage (char const *);

Node *hash_table;

FnRead read_table[] = {
  read_number, /* RD_NUM */
  read_string,
  (FnRead)0,
};

FnProbe probe_table[] = {
  probe_linear, /* LOC_LINEAR */
  probe_quadratic, probe_double_hashing, probe_chain, (FnProbe)0,
};

static struct option longopts[] = {
  { "help", no_argument, 0, 'h' },
  { 0, optional_argument, 0, 'M' },
  { 0, optional_argument, 0, 'N' },
  { "read", optional_argument, 0, 'r' },
  { "search", optional_argument, 0, 's' },
  { "unlink", optional_argument, 0, 'u' },
  { "dump", no_argument, 0, 'd' },
  { 0, 0, 0, 0 },
};

static FILE *opt_file = NULL;
static char *opt_search = NULL;
static int opt_dump = 0;
static int opt_fn_read = RD_NUM;
static int opt_ht_m = M;
static int opt_ht_n = N;

int
main (int argc, char **argv)
{
  int rc, ch;
  unsigned int i = 0;
  Node node = { 0 };

  while ((ch = getopt_long (argc, argv, "hr:M:N:s:u:d", longopts, 0)) != -1)
    {
      switch (ch)
        {
        case 'd':
          opt_dump = 1;
          break;
        case 'M':
          opt_ht_m = atoi (optarg);
					if (opt_ht_m < 1)
						{
						}
          break;
        case 'N':
          opt_ht_n = atoi (optarg);
					if (opt_ht_n < opt_ht_m - 3)
						{
							opt_ht_n = opt_ht_m + 3;
						}
          break;
        case 'i':
          opt_file = fopen (optarg, "r");
          if (!opt_file)
            {
              perror ("!panic");
              goto clean_exit;
            }
          break;
        case 'r':
          if (strcmp ("number", optarg) == 0)
            {
              opt_fn_read = RD_NUM;
            }
          else if (strcmp ("string", optarg) == 0)
            {
              opt_fn_read = RD_STR;
            }
          else
            {
              fprintf (stderr, "!panic, invalid -r argument: %s\n", optarg);
              goto clean_exit;
            }
          break;
        case 's':
          opt_search = optarg;
          break;
        default:
          usage (argv[0]);
          goto clean_exit;
        }
    }

  if (optind < argc)
    {
      fprintf (stderr, "file:%s\n", argv[optind]);
      opt_file = fopen (argv[optind], "r");
      if (!opt_file)
        {
          perror ("!panic");
          goto clean_exit;
        }
    }
  else
    {
      opt_file = stdin;
    }

	hash_table = calloc (1, sizeof (Node) * (opt_ht_n + 1))
  memset (hash_table, EMPTY, sizeof (hash_table));

  while ((rc = read_table[opt_fn_read](opt_file, &node)) != EOF)
    {
      if (rc == 1)
        {
          if (insert_table (&node, &i, *probe_table[FN_LOC]))
            {
              perror ("!panic");
              break;
            }
        }
    }

  dump_table ();

clean_exit:
  return 0;
}

int
read_number (FILE *stream, Node *node)
{
  int rc = fscanf (stream, "%u", &node->num);
  if (rc == 0)
    {
      int c;
      for (c = getc (stream); c != EOF && !isdigit (c); c = getc (stream))
        {
          /* void */
        }
      if (c == EOF)
        {
          return EOF;
        }
      ungetc (c, stream);
    }
  return rc;
}

int
read_string (FILE *stream, Node *node)
{
  int rc;
  int h = 1;
  char buf[BUFSIZ];

  assert (sizeof (node->str) < BUFSIZ && "buf should larger than node->str");

  if ((rc = fscanf (stream, "%s", &buf[0])) == 1)
    {
      for (char *s1 = buf; *s1; s1++)
        {
          if (!isalpha (*s1))
            {
              return 0;
            }
        }
      strncpy (node->str, buf, sizeof (node->str) - 1);
      h = str_to_num (node->str, h);
    }

  node->num = h;
  return rc;
}

int
insert_table (Node *node, unsigned *n, FnProbe probe)
{
  int loc;
  Node *one;

  loc = probe (node->num);

  if (*n >= M)
    {
      errno = EOVERFLOW;
      return EOF;
    }

  one = &HE (loc);

  if (!one->used)
    {
      (*n)++;
      one->num = node->num;
      one->used = 1;
      if (opt_fn_read == RD_STR)
        {
          one->alpha = alpha_order (node->str);
          strncpy (one->str, node->str, sizeof (one->str) - 1);
        }
    }
  else
    {
#if (FN_LOC == LOC_CHAIN)
      Node *cur, *pre;
      for (pre = cur = one; cur; pre = cur, cur = cur->next)
        {
          if (cur->used && cur->num == node->num)
            {
              break;
            }
        }
      if (!cur)
        {
          cur = calloc (1, sizeof (Node));
          if (!cur)
            {
              return EOF;
            }
          pre->next = cur;
          cur->num = node->num;
          cur->used = 1;
          if (opt_fn_read == RD_STR)
            {
              cur->alpha = alpha_order (node->str);
              strncpy (cur->str, node->str, sizeof (cur->str) - 1);
            }
        }
      one = cur;
#endif
    }

  one->freq++;

  return 0;
}

int
search_table (unsigned key, Node **found)
{
  int loc = PE (FN_LOC) (key);
  *found = NULL;
  if (HE (loc).used && HE (loc).num == key)
    {
      *found = &HE (loc);
      return 1;
    }
#if (FN_LOC == LOC_CHAIN)
  Node *cur;
  for (cur = HE (loc).next; cur; cur = cur->next)
    {
      if (cur->used && cur->num == key)
        {
          *found = cur;
          return 1;
        }
    }
#endif
  return 0;
}

int
delete_entry (unsigned key)
{
  Node *found;
  if (search_table (key, &found))
    {
      found->used = EMPTY;
      return 1;
    }
#if (FN_LOC == LOC_CHAIN)
  Node *pre, *cur;
  int loc = PE (FN_LOC) (key);
  for (pre = &HE (loc), cur = pre->next; cur; pre = cur, cur = cur->next)
    {
      if (cur->used && cur->num == key)
        {
          pre->next = cur->next;
          free (cur);
          return 1;
        }
    }
#endif
  return 0;
}

int
probe_linear (unsigned key)
{
  static unsigned rp = EMPTY;
  int loc = H (key);

  if (rp == EMPTY)
    {
      rp = get_relative_prime (N);
    }

  while (HE (loc).used && HE (loc).num != key)
    {
      loc = H (loc + rp);
    }

  return loc;
}

int
probe_quadratic (unsigned key)
{
  int i = 0;
  int loc = H (key);
  while (HE (loc).used && HE (loc).num != key)
    {
      i++;
      loc = loc + 2 * i + 3 * i * i;
      /* keep loc in [1,N] */
      while (loc > N)
        {
          loc -= N;
        }
    }
  return loc;
}

int
probe_double_hashing (unsigned key)
{
  int loc = H (key);
  int loc2 = H (key + 1);
  while (HE (loc).used && HE (loc).num != key)
    {
      loc += loc2;
      if (loc > N)
        {
          loc -= N;
        }
    }
  return loc;
}

int
probe_chain (unsigned key)
{
  int loc = H (key);
  return loc;
}

unsigned
get_relative_prime (unsigned n)
{
  for (unsigned x = 3; x < n; x++)
    {
      if ((n / x) * x != n)
        {
          return x;
        }
    }
  return (n - 1);
}

unsigned
str_to_num (char const *ss, unsigned base)
{
  int w = 3;
  int n = base;
  for (char const *p = ss; *p; w += 2, p++)
    {
      n += w * (*p);
    }
  return n;
}

int
alpha_order (char const *ss)
{
  if (ss[0] && isalpha (ss[0]))
    {
      return 1 + tolower (ss[0]) - 'a';
    }
  return 0;
}

void
dump_table (void)
{
  int cnt = 0;
  char *read_name, *probe_name;
  size_t total = sizeof (hash_table) / sizeof (hash_table[0]);

  for (size_t i = 0; i < total; i++)
    {
      if (hash_table[i].used)
        {
          cnt++;
        }
    }

  if (read_table[opt_fn_read] == read_number)
    {
      read_name = _str_ (read_numer);
    }
  else if (read_table[opt_fn_read] == read_string)
    {
      read_name = _str_ (read_string);
    }
  else
    {
      read_name = "X";
    }

  if (probe_table[FN_LOC] == probe_linear)
    {
      probe_name = _str_ (probe_linear);
    }
  else if (probe_table[FN_LOC] == probe_quadratic)
    {
      probe_name = _str_ (probe_quadratic);
    }
  else if (probe_table[FN_LOC] == probe_double_hashing)
    {
      probe_name = _str_ (probe_double_hashing);
    }
  else if (probe_table[FN_LOC] == probe_chain)
    {
      probe_name = _str_ (probe_chain);
    }
  else
    {
      probe_name = "X";
    }

  fprintf (stderr, "hash_table %d/(%d,%zu) %s %s\n------------\n", cnt, M,
           total, read_name, probe_name);
  fprintf (stderr, "%4s %6s %4s %5s %-32s\n", "idx", "num", "freq", "alpha",
           "str");

  for (size_t i = 0; i < total; i++)
    {
      Node const *n = &hash_table[i];
      if (n->used)
        {
          printf ("%4zu %6u %4d %5d %-32s\n", i, n->num, n->freq, n->alpha,
                  n->str);
#if (FN_LOC == LOC_CHAIN)
          for (Node *cur = n->next; cur; cur = cur->next)
            {
              if (cur->used)
                {
                  printf ("%4zu %6u %4d %5d %-32s\n", i, cur->num, cur->freq,
                          cur->alpha, cur->str);
                }
            }
#endif
        }
    }
}

void
usage (char const *p)
{
  printf ("Usage %s [options ...] [file]\n", p);
  printf ("  -h, --help          this help text\n");
  printf ("  -r, --read          read [number|string], default is number\n");
  printf (
      "  -M                  effective bounds of hash table, default is %d\n",
      M);
  printf ("  -N                  up bounds of hash table, default is %d\n", N);
  printf ("  -s, --search        search entry in hash table\n");
  printf ("  -u, --unlink        unlink entry in hash table\n");
  printf ("  -d, --dump          dump hash table to stdout\n");
}
