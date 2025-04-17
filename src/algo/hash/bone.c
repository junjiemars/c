#include <_algo_.h>
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

#define H(x) ((x) % opt_ht_n + 1)
#define H2(x, n) ((x) % (n) + 1)
#define HE(x) (hash_table[(x)])
#define EMPTY 0

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
typedef unsigned (*FnProbe) (unsigned);

int insert_table (Node *, unsigned *, FnProbe);
int search_table (unsigned, unsigned *, Node **);
int unlink_entry (unsigned, unsigned *);
int read_number (FILE *, Node *);
int read_string (FILE *, Node *);
unsigned read_key (char const *);
unsigned probe_linear (unsigned);
unsigned probe_quadratic (unsigned);
unsigned probe_double_hashing (unsigned);
unsigned probe_chain (unsigned);
unsigned get_relative_prime (unsigned);
unsigned str_to_num (char const *);
int alpha_order (char const *);
void dump_table (void);
void print_entry (unsigned, Node const *);
static void usage (char const *);

Node *hash_table;

static struct option longopts[] = {
  { "help", no_argument, 0, 'h' },
  { "least", optional_argument, 0, 'M' },
  { "upper", optional_argument, 0, 'N' },
  { "read", optional_argument, 0, 'r' },
  { "probe", optional_argument, 0, 'p' },
  { "search", optional_argument, 0, 's' },
  { "unlink", optional_argument, 0, 'u' },
  { 0, 0, 0, 0 },
};

static FILE *opt_file = NULL;
static char *opt_search = NULL;
static char *opt_unlink = NULL;
static FnRead opt_fn_read = read_number;
static FnProbe opt_fn_probe = probe_linear;
static unsigned opt_ht_m = M;
static unsigned opt_ht_n = N;

int
main (int argc, char **argv)
{
  int rc;
  int ch;
  unsigned loc = 0;
  unsigned key;
  Node node = { 0 };

  while ((ch = getopt_long (argc, argv, "hr:M:N:p:s:u:", longopts, 0)) != -1)
    {
      switch (ch)
        {
        case 'M':
          opt_ht_m = (unsigned)atol (optarg);
          break;
        case 'N':
          opt_ht_n = (unsigned)atol (optarg);
          break;
        case 'p':
          if (strcmp ("linear", optarg) == 0)
            {
              opt_fn_probe = probe_linear;
            }
          else if (strcmp ("quadratic", optarg) == 0)
            {
              opt_fn_probe = probe_quadratic;
            }
          else if (strcmp ("double", optarg) == 0)
            {
              opt_fn_probe = probe_double_hashing;
            }
          else if (strcmp ("chain", optarg) == 0)
            {
              opt_fn_probe = probe_chain;
            }
          else
            {
              fprintf (stderr, "!invalid -p argument: %s\n", optarg);
              goto clean_exit;
            }
          break;
        case 'r':
          if (strcmp ("number", optarg) == 0)
            {
              opt_fn_read = read_number;
            }
          else if (strcmp ("string", optarg) == 0)
            {
              opt_fn_read = read_string;
            }
          else
            {
              fprintf (stderr, "!invalid -r argument: %s\n", optarg);
              goto clean_exit;
            }
          break;
        case 's':
          opt_search = optarg;
          break;
        case 'u':
          opt_unlink = optarg;
          break;
        default:
          usage (argv[0]);
          goto clean_exit;
        }
    }

  if (opt_ht_m < 1)
    {
      opt_ht_m = M;
    }
  if (opt_ht_n < opt_ht_m - 3)
    {
      opt_ht_n = opt_ht_m + 3;
    }

  opt_file = stdin;
  if (optind < argc)
    {
      opt_file = fopen (argv[optind], "r");
      if (!opt_file)
        {
          perror ("!panic");
          goto clean_exit;
        }
    }

  if (!(hash_table = calloc (1, sizeof (Node) * (opt_ht_n + 1))))
    {
      perror ("!panic");
      goto clean_exit;
    }

  while ((rc = opt_fn_read (opt_file, &node)) != EOF)
    {
      if (rc == 1)
        {
          if (insert_table (&node, &loc, opt_fn_probe))
            {
              perror ("!panic");
							break;
            }
        }
    }

  if (opt_search)
    {
      Node *found;
      key = read_key (opt_search);
      if (search_table (key, &loc, &found))
        {
          fprintf (stderr, "#key %u found\n", key);
          print_entry (loc, found);
        }
      else
        {
          fprintf (stderr, "!key %u no found\n", key);
        }
    }

  if (opt_unlink)
    {
      key = read_key (opt_unlink);
      if (unlink_entry (key, &loc))
        {
          fprintf (stderr, "#key %u at %u unlinked\n", key, loc);
        }
      else
        {
          fprintf (stderr, "!key %u unlink failed\n", key);
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
  int num = 1;
  char buf[BUFSIZ];

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
      num = str_to_num (node->str);
    }

  node->num = num;
  return rc;
}

unsigned
read_key (char const *ss)
{
  if (opt_fn_read == read_number)
    {
      return (unsigned)atol (ss);
    }
  else
    {
      return str_to_num (ss);
    }
}

int
insert_table (Node *node, unsigned *n, FnProbe probe)
{
  int loc;
  Node *one;

  loc = probe (node->num);

  if (*n >= opt_ht_m)
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
      if (opt_fn_read == read_string)
        {
          one->alpha = alpha_order (node->str);
          strncpy (one->str, node->str, sizeof (one->str) - 1);
        }
    }
  else
    {
      if (opt_fn_probe == probe_chain)
        {
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
              if (opt_fn_read == read_string)
                {
                  cur->alpha = alpha_order (node->str);
                  strncpy (cur->str, node->str, sizeof (cur->str) - 1);
                }
            }
          one = cur;
        }
    }

  one->freq++;

  return 0;
}

int
search_table (unsigned key, unsigned *loc, Node **found)
{
  *loc = opt_fn_probe (key);
  *found = NULL;
  if (HE (*loc).used && HE (*loc).num == key)
    {
      *found = &HE (*loc);
      return 1;
    }
  if (opt_fn_probe == probe_chain)
    {
      for (Node *cur = HE (*loc).next; cur; cur = cur->next)
        {
          if (cur->used && cur->num == key)
            {
              *found = cur;
              return 1;
            }
        }
    }
  return 0;
}

int
unlink_entry (unsigned key, unsigned *loc)
{
  *loc = opt_fn_probe (key);
  Node *found;

  if (HE (*loc).used && HE (*loc).num == key)
    {
      found = &HE (*loc);
      if (opt_fn_probe != probe_chain)
        {
          found->used = EMPTY;
        }
      else
        {
          Node *next = found->next;
          if (next)
            {
              found->num = next->num;
              found->freq = next->freq;
              found->used = next->used;
              found->alpha = next->alpha;
              found->next = next->next;
              strncpy (found->str, next->str, sizeof (found->str) - 1);
              free (next);
            }
        }
      return 1;
    }

  if (opt_fn_probe == probe_chain)
    {
      Node *pre, *cur;
      for (pre = &HE (*loc), cur = pre->next; cur; pre = cur, cur = cur->next)
        {
          if (cur->used && cur->num == key)
            {
              pre->next = cur->next;
              free (cur);
              return 1;
            }
        }
    }
  return 0;
}

unsigned
probe_linear (unsigned key)
{
  static unsigned rp = EMPTY;
  unsigned loc = H (key);

  if (rp == EMPTY)
    {
      rp = get_relative_prime (opt_ht_n);
    }

  while (HE (loc).used && HE (loc).num != key)
    {
      loc = H (loc + rp);
    }

  return loc;
}

unsigned
probe_quadratic (unsigned key)
{
  int i = 0;
  unsigned loc = H (key);
  while (HE (loc).used && HE (loc).num != key)
    {
      i++;
      loc = loc + 2 * i + 3 * i * i;
      /* keep loc in [1,N] */
      while (loc > opt_ht_n)
        {
          loc -= opt_ht_n;
        }
    }
  return loc;
}

unsigned
probe_double_hashing (unsigned key)
{
	static unsigned rp = EMPTY;
  unsigned loc, loc2;

	if (rp == EMPTY)
		{
			rp = get_relative_prime (opt_ht_n);
		}
	loc = H (key);
	loc2 = H2 (key, rp);

  while (HE (loc).used && HE (loc).num != key)
    {
      loc += loc2;
      if (loc > opt_ht_n)
        {
          loc -= opt_ht_n;
        }
    }
  return loc;
}

unsigned
probe_chain (unsigned key)
{
  unsigned loc = H (key);
  return loc;
}

unsigned
get_relative_prime (unsigned n)
{
  for (unsigned x = n - 2; x > 1; x--)
    {
      if ((x & 1) == 1 && (n / x) * x != n)
        {
          return x;
        }
    }
  return (n - 1);
}

unsigned
str_to_num (char const *ss)
{
  int w = 3;
  int n = 1;
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
  unsigned cnt = 0;
  char *read_name, *probe_name;
  unsigned total = opt_ht_n;

  assert (hash_table && "hash_table should not be NULL");

  for (unsigned i = 0; i < total; i++)
    {
      if (hash_table[i].used)
        {
          cnt++;
        }
    }

  if (opt_fn_read == read_number)
    {
      read_name = _str_ (read_numer);
    }
  else if (opt_fn_read == read_string)
    {
      read_name = _str_ (read_string);
    }
  else
    {
      read_name = "XXX";
    }

  if (opt_fn_probe == probe_linear)
    {
      probe_name = _str_ (probe_linear);
    }
  else if (opt_fn_probe == probe_quadratic)
    {
      probe_name = _str_ (probe_quadratic);
    }
  else if (opt_fn_probe == probe_double_hashing)
    {
      probe_name = _str_ (probe_double_hashing);
    }
  else if (opt_fn_probe == probe_chain)
    {
      probe_name = _str_ (probe_chain);
    }
  else
    {
      probe_name = "XXX";
    }

  fprintf (stderr, "hash_table %u/(M%u,N%u) %s %s\n------------\n", cnt,
           opt_ht_m, total, read_name, probe_name);

  if (opt_fn_read == read_number)
    {
      fprintf (stderr, "%4s %6s %4s\n", "idx", "num", "freq");
    }
  else
    {
      fprintf (stderr, "%4s %6s %4s %5s %-32s\n", "idx", "num", "freq",
               "alpha", "str");
    }

  for (unsigned i = 0; i < total; i++)
    {
      Node const *n = &hash_table[i];
      if (n->used)
        {
          print_entry (i, n);
          if (opt_fn_probe == probe_chain)
            {
              for (Node *cur = n->next; cur; cur = cur->next)
                {
                  if (cur->used)
                    {
                      print_entry (i, cur);
                    }
                }
            }
        }
    }
}

void
print_entry (unsigned loc, Node const *node)
{
  if (opt_fn_read == read_number)
    {
      printf ("%4u %6u %4d\n", loc, node->num, node->freq);
    }
  else
    {
      printf ("%4u %6u %4d %5d %-32s\n", loc, node->num, node->freq,
              node->alpha, node->str);
    }
}

void
usage (char const *p)
{
  printf ("Usage %s [options ...] [file]\n", p);
  printf ("  -h, --help          this help text\n");
  printf ("  -r, --read          read [number|string], default is number\n");
  printf ("  -M                  effective least bounds of hash table, "
          "default is %d\n",
          M);
  printf ("  -N                  upper bounds of hash table, "
          "default is %d\n",
          N);
  printf ("  -p, --probe         probe [linear|quadratic|double|chain], "
          "default is %s\n",
          "linear");
  printf ("  -s, --search        search entry in hash table\n");
  printf ("  -u, --unlink        unlink entry in hash table\n");
}
