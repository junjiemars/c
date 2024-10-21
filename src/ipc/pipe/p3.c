#include <_ipc_.h>

#define _PAGER_ "${PAGER:-/usr/bin/less}"

int
main (int argc, char **argv)
{
  char buf[BUFSIZ];
  size_t n_read;
  char *command;
  FILE *fpin, *fpout;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <command>\n", argv[0]);
      exit (1);
    }
  command = argv[1];

  if ((fpin = popen (command, "r")) == NULL)
    {
      perror (NULL);
      exit (1);
    }

  if ((fpout = popen (_PAGER_, "w")) == NULL)
    {
      perror (NULL);
      exit (1);
    }

  while ((n_read = fread (buf, sizeof (char), BUFSIZ, fpin)) > 0)
    {
      fwrite (buf, sizeof (char), n_read, fpout);
    }
  if (ferror (fpin))
    {
      fprintf (stderr, "fread error: %s\n", strerror (errno));
      exit (1);
    }

  if (pclose (fpout) == -1)
    {
      fprintf (stderr, "pclose error: %s\n", strerror (errno));
      exit (1);
    }

  exit (0);
}
