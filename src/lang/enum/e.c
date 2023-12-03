#include "_lang_.h"
#include <stdio.h>

enum
{
  RED,
  GREEN,
  BLUE,
};

enum order
{
  first,
  second,
  third,
};

typedef enum
{
  one,
  two,
  three
} number_t;

#define CORVID_MAP(XX)                                                        \
  XX (101, BEGIN, "BEGIN")                                                    \
  XX (101, MAGPIE, "Including the black and white Eurasian magpie")           \
  XX (102, RAVEN,                                                             \
      "A raven is one of several larger-bodied "                              \
      "species of the genus Corvus")                                          \
  XX (103, JAY,                                                               \
      "Jays are several species of medium-sized, "                            \
      "usually colorful and noisy")                                           \
  XX (104, END, "END")

enum corvid
{
#define XX(num, name, string) CORVID_##name = num ,
  CORVID_MAP (XX)
#undef XX
};

int
main (void)
{
  printf ("RED = %i, sizeof(RED) = %zu\n", RED, sizeof (RED));
  printf ("GREEN = %i, sizeof(GREEN) = %zu\n", GREEN, sizeof (GREEN));
  printf ("BLUE = %i, sizeof(BLUE) = %zu\n", BLUE, sizeof (BLUE));

  printf ("sizeof(enum order) = %zu\n", sizeof (enum order));

  number_t n = three;
  printf ("three = %i, sizeof(number_t) = %zu\n", n, sizeof (number_t));

  for (int i = CORVID_BEGIN; i < CORVID_END; i++)
    {
      printf ("corvid#: %i\n", i);
    }

  return 0;
}
