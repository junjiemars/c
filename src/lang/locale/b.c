#include "_lang_.h"
#include <locale.h>
#include <time.h>


void print_LC_ALL(void);
void test_setlocale(const char*);
void test_LC_ALL(void);

void
print_LC_ALL(void)
{
  static char text[128];
  time_t t = time(0);

  printf("%.3f\n", 31415.9265354);

  strftime(text, sizeof(text), "%A, %B, %d, %Y(%x)\n", localtime(&t));
  puts(text);
}

void
test_setlocale(const char *locale)
{
  char *curr;
  setlocale(LC_ALL, locale);
  curr = setlocale(LC_ALL, NULL);
  printf("LC_ALL=%s\n----------\n", curr);
  print_LC_ALL();
}

int
main(int argc, char **argv)
{
  char *locale = "";
  if (argc > 1)
    {
      locale = argv[1];
    }
  test_setlocale(locale);
  return 0;
}
