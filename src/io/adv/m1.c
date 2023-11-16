#include "_io_.h"

/*
 * Copy file using `mmap'
 *
 */

int
main (int argc, char **argv)
{
  int fsrc, fdst;
  char *psrc, *pdst;
  struct stat ss;

  if (argc < 3)
    {
      fprintf (stderr, "usage: %s <src> <dst>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  if ((fsrc = open (argv[1], O_RDONLY)) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (fstat (fsrc, &ss) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if ((fdst = open (argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  /* keep the same size */
  if (ftruncate (fdst, ss.st_size) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  psrc = mmap (0, ss.st_size, PROT_READ, MAP_PRIVATE, fsrc, 0);
  if (psrc == MAP_FAILED)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  /* must be MAP_SHARED */
  pdst = mmap (0, ss.st_size, PROT_WRITE, MAP_SHARED, fdst, 0);
  if (pdst == MAP_FAILED)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  /* close after mapped is ok */
  close (fsrc);
  close (fdst);

  memcpy (pdst, psrc, ss.st_size);

  /* unmap */
  munmap (psrc, ss.st_size);
  munmap (pdst, ss.st_size);

  exit (EXIT_SUCCESS);
}
