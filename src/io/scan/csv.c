#include <_io_.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef struct salary_s {
  int num;
  int age;
  float salary;
  char name[64];
} salary_s;

int
main(int argc, char **argv) {
  if (argc < 1) {
    fprintf(stdout, "where the csv file located?\n");
    return 0;
  }

  const char *fmt = "%d,%d,%f,%s\n";
  FILE *in = 0;
  int n = 0;
  salary_s ss;
  memset(&ss, 0, sizeof(salary_s));
  
  in = fopen(argv[1], "r");
  if (!in) {
    perror("#panic");
    return 1;
  }

  while (!feof(in) && (4 == (n = fscanf(in, fmt,
                                        &ss.num,
                                        &ss.age,
                                        &ss.salary,
                                        ss.name)))) {
    fprintf(stdout, fmt,
            ss.num,
            ss.age,
            ss.salary,
            ss.name);
  }
  if (ferror(in)) {
    perror("!panic");
    return 1;
  }
  
  fclose(in);
  return 0;
}
