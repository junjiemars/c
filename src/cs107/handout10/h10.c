#include "_cs107_.h"
#include <string.h>

typedef struct rubble
{
  int betty;
  char barney[4];
  struct rubble *bammbamm;
} rubble;

typedef struct
{
  short *wilma[2];
  short fred[2];
  rubble dino;
} flintstone;

void
layout()
{
  rubble      *simpsons;
  flintstone   jetsons[4];

  simpsons = &jetsons[0].dino;
  jetsons[1].wilma[3] = (short *) &simpsons;
  strcpy(simpsons[2].barney, "Bugs Bunny");
  ((flintstone *) (jetsons->fred))->dino.bammbamm = simpsons;
  *(char **) jetsons[4].fred = simpsons->barney + 4;
}

int
main(void)
{
  layout();
}

/* eof */
