#include <_io_.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sassy_s {
  char name[16];
  int age;
  char gender;
  double allowance;
} sassy_s;

void
in(const char *path, sassy_s *ss, const size_t len) {
  FILE *i = fopen(path, "rb");
  if (!i) {
    perror("!panic");
    return;
  }

  size_t n = fread(ss, sizeof(sassy_s), len, i);
  if (n < len) {
    fprintf(stderr, "read %zu/%zu\n", n, len);
  }
  
  fclose(i);
}

void
out(const char *path, const sassy_s *ss, const size_t len) {
  FILE *o = fopen(path, "wb");
  if (!o) {
    perror("!panic");
    return;
  }

  size_t n = fwrite(ss, sizeof(sassy_s), len, o);
  if (n < len) {
    fprintf(stderr, "!write %zu/%zu\n", n, len);
  }

  fclose(o);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  if (argc < 2) {
    fprintf(stderr, "where the sassy file located?\n");
    return 0;
  }

  size_t n = 2;
  sassy_s *ss = malloc(sizeof(sassy_s)*2*n);
  strncpy(ss[0].name, "Anne", 16-1);
  ss[0].age = 0x11;
  ss[0].gender = 'F';
  ss[0].allowance = 11.22;
  strncpy(ss[1].name, "Bourn", 16-1);
  ss[1].age = 0x22;
  ss[1].gender = 'M';
  ss[1].allowance = 22.33;
  
  out(argv[1], ss, n);
  in(argv[1], &ss[n], n);

  for (size_t i = n; i < 2*n; i++) {
    fprintf(stdout,
            "No.%zu\n----\nname:%s\nage:%d\ngender:%c\nallowance:%lf\n",
            i,
            ss[i].name,
            ss[i].age,
            ss[i].gender,
            ss[i].allowance);
  }
  
  free(ss);
  return 0;
}
