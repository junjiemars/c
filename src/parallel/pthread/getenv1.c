#include "_parallel_.h"
#include <limits.h>
#include <pthread.h>

/*
 * `getenv1' is an thread-safe emulation of `getenv'.
 *
 */

#define N_THREAD 4

extern char **environ;
static pthread_key_t env_key;
static pthread_once_t env_once = PTHREAD_ONCE_INIT;
static char *N_NAME[N_THREAD] = {
  "USER",
  "SHELL",
  "TERM",
};

static char *getenv1 (const char *);
static void init ();
static void *race (void *);
static void drop (void *);

int
main (void)
{
  int retval;
  pthread_t tids[N_THREAD];

  for (int i = 0; i < N_THREAD; i++)
    {
      pthread_create (&tids[i], NULL, race, N_NAME[i]);
    }

  for (int i = 0; i < N_THREAD; i++)
    {
      pthread_join (tids[i], (void **)&retval);
    }

  fprintf (stdout, "LANG=%s\n", getenv1 ("LANG"));

  pthread_key_delete (env_key);

  return 0;
}

char *
getenv1 (const char *name)
{
  char *buf;

  if (!name)
    {
      return NULL;
    }

  pthread_once (&env_once, init);
  buf = pthread_getspecific (env_key);
  if (!buf)
    {
      buf = malloc (ARG_MAX);
      pthread_setspecific (env_key, buf);
    }

  for (char **p = environ; *p != NULL; p++)
    {
      size_t n = strnlen (name, ARG_MAX);
      if (strncmp (*p, name, n) == 0)
        {
          strncpy (buf, *p, strnlen (*p, ARG_MAX));
          return &buf[n + 1];
        }
    }

  return NULL;
}

void
init (void)
{
  int rc;

  rc = pthread_key_create (&env_key, drop);
  if (rc)
    {
      exit (rc);
    }
}

void *
race (void *arg)
{
  char *val;
  const char *name = arg;
  if (name)
    {
      val = getenv1 (name);
      fprintf (stdout, "%s=%s\n", name, val);
    }
  return arg;
}

void
drop (void *arg)
{
  char *buf = arg;
  if (buf)
    {
      free (buf);
    }
}
