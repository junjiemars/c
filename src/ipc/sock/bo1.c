#include "_ipc_.h"

int
main (int argc, char **argv)
{
  uint32_t num;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <number>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  sscanf (argv[1], "%10x", &num);

  assert (ntohl (htonl (num)) == num);
  assert (htonl (ntohl (num)) == num);

  printf ("htonl = 0x%0x\n", htonl (num));
  printf ("htons = 0x%0x\n", htons ((uint16_t)num));
  printf ("ntohl = 0x%0x\n", ntohl (num));
  printf ("ntohs = 0x%0x\n", ntohs ((uint16_t)num));

  exit (EXIT_SUCCESS);
}
