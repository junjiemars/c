#include <_io_.h>
#include <stdio.h>

#include <getopt.h>

void
usage() {
  printf("usage: wc [-cl] [file ...]\n");
}

int 
main(int argc, char **argv) {
  int opt_count_bytes = 1;
  int opt_count_lines = 1;
  char *opt_filename = 0;

  int ch;
  while (-1 != (ch = getopt(argc, argv, "cl"))) {
    switch (ch) {
      case 'c':
        opt_count_bytes = 1;
        break;
      case 'l':
        opt_count_lines = 1;
        break;
      default:
        if ('-' == optarg[0]) {
          printf("%s: illegal option -- %s", argv[0], optarg);
          usage();
          return 1;
        }
        opt_filename = optarg;
    }
  }

  
}
