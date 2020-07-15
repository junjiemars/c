#include "_lang_.h"
#include <locale.h>
#include <stdio.h>
#include <time.h>


void print_stuff(void);
void test_locale(const char*);

void
print_stuff(void) {
  static char text[128];
  time_t t = time(0);
  
  printf("%.2f\n", 1.2);
  
  strftime(text, sizeof(text), "%A, %B %d, %Y(%x)\n", localtime(&t));
  puts(text);
}

void
test_locale(const char *locale) {
  printf("LC_ALL=%s:\n----------\n", locale);
  setlocale(LC_ALL, locale);
  print_stuff();
}

int
main(void) {
  test_locale("C");
  test_locale("POSIX");
  test_locale("en_US");
  test_locale("zh_CN");
  test_locale("zh_HK");

  return 0;
}
