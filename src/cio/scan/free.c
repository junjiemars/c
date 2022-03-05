#include <_cio_.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "where the free txt located?\n");
      return 1;
    }

  int n = 0;
  int sum = 0;
  int num = 0;

  FILE *in = fopen(argv[1], "r");
  if (!in)
    {
      perror("!panic");
      return 1;
    }

  while (1 == (fscanf(in, "%d", &num)))
    {
      n += 1;
      sum += num;
    }

  if (ferror(in))
    {
      perror("!panic");
      goto clean_exit;
    }

  if (!feof(in))
    {
      fprintf(stderr, "!panic, meet a non-number.");
    }
  else
    {
      fprintf(stdout, "N: %d\n", n);
      fprintf(stdout, "sum: %d\n", sum);
      fprintf(stdout, "average: %3.2f\n", sum*1.0f/n);
    }

 clean_exit:
  fclose(in);
  return 0;
}
