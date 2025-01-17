#include "../_algo_.h"

/*
 * let N = count, M = device's width.
 * 1. loop cycles = floor(N/M) + mod(N, M)
 * 2.
 *
 * References:
 * 1. https://www.lysator.liu.se/c/duffs-device.html
 */

#if (GCC)
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif

void raw_send (char *to, char *from, int count);
void send (char *to, char *from, int count);
void send2 (char *to, char *from, int count);
static void show (char *p);

int
main (int argc, char *argv[])
{
  int n = 1;
  char to[32] = { 0 };
  char *from = "abcdefghijklmnopqrstuvwxyz";

  if (argc > 1)
    {
      n = atoi (argv[1]);
    }

  raw_send (to, from, n);
  show (to);
  fflush (stdout);
  memset (to, 0, _nof_ (to));

  send (to, from, n);
  show (to);
  fflush (stdout);
  memset (to, 0, _nof_ (to));

  send2 (to, from, n);
  show (to);
  fflush (stdout);
  memset (to, 0, _nof_ (to));

  memcpy (to, from, n);
  show (to);
  fflush (stdout);

  return 0;
}

void
raw_send (char *to, char *from, int count)
{
  do
    {
      *to++ = *from++;
    }
  while (--count > 0); /* count > 0 assumed */
}

void
send (char *to, char *from, int count)
{
  int n = (count + 7) / 8; /* count > 0 assumed */
  switch (count % 8)
    {
    case 0:
      do
        {
          *to++ = *from++;
        case 7:
          *to++ = *from++;
        case 6:
          *to++ = *from++;
        case 5:
          *to++ = *from++;
        case 4:
          *to++ = *from++;
        case 3:
          *to++ = *from++;
        case 2:
          *to++ = *from++;
        case 1:
          *to++ = *from++;
        }
      while (--n > 0);
    }
}

void
send2 (char *to, char *from, int count)
{
  int n = (count + 7) / 8; /* count > 0 assumed */
  switch (count % 8)
    {
    case 0:
      *to++ = *from++;
    case 7:
      *to++ = *from++;
    case 6:
      *to++ = *from++;
    case 5:
      *to++ = *from++;
    case 4:
      *to++ = *from++;
    case 3:
      *to++ = *from++;
    case 2:
      *to++ = *from++;
    case 1:
      *to++ = *from++;
    }
  while (--n > 0)
    {
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
    }
}

void
show (char *p)
{
  while (*p != 0)
    {
      printf ("%c, ", *p++);
    }
  printf ("\n");
}
