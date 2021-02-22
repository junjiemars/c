#include "_lang_.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

char *to_asctime(const time_t *epoch);

char*
to_asctime(const time_t *epoch) 
{
  char *c = ctime(epoch);
  if (!c)
    {
      perror(0);
    }
  return c;
}

int
main(int argc, char **argv) 
{
  time_t epoch;
  if (argc < 2) 
    {
      epoch = 0;
      if ((time_t) -1 == time(&epoch))
        {
          perror(0);
          return 1;
        }
      printf("%lu\n", epoch);
      return 0;
    }

  if (0 == strncmp("-", argv[1], sizeof(int)))
    {
      _unused_(fscanf(stdin, "%lu", (unsigned long*) &epoch));
      printf("%s", to_asctime(&epoch));      
      return 0;
    }

  sscanf(argv[1], "%lu", (unsigned long*) &epoch);
  printf("%s", to_asctime(&epoch));

  return 0;
}
