#include <_io_.h>
#include <stdio.h>

typedef struct record_s {
  char num[7];
  char name[25];
  int stock;
  double price;
} record_s;

void
out_records(const char *inpath, const char *outpath) {
  FILE *in = 0, *out = 0;
  in = fopen(inpath, "r");
  if (!in) {
    perror("!panic");
    return;
  }
  out = fopen(outpath, "wb");
  if (!out) {
    perror("!panic");
    goto clean_exit;
  }
  
  record_s ss = {};
  while (4 == fscanf(in, "%s %s %d %lf",
                     ss.num,
                     ss.name,
                     &ss.stock,
                     &ss.price)) {
    if (1 != fwrite(&ss, sizeof(record_s), 1, out)) {
      perror("!panic");
      goto clean_exit;
    }
  }
  
 clean_exit:
  fclose(out);
  fclose(in);
}

void
seek_record(const char *path, const int n) {
  FILE *in = fopen(path, "rb");
  if (!in) {
    perror("!panic");
    return;
  }

  if (fseek(in, (n-1)*sizeof(record_s), SEEK_SET)) {
    if (ferror(in)) {
      perror("!panic");
    }
    goto clean_exit;
  }

  record_s ss = {};
  if (1 != fread(&ss, sizeof(record_s), 1, in)) {
    if (feof(in)) {
      fprintf(stderr, "No.%i no found\n----\n", n);
    } else if (ferror(in)) {
      perror("!panic");
    }
    goto clean_exit;
  }
  fprintf(stdout,
          "No.%d found\n----\nnum: %s\nname: %s\nstock: %d\nprice: %lf\n",
          n, ss.num, ss.name, ss.stock, ss.price);

 clean_exit:
  fclose(in);
}

int
main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "where the records.txt/records.bin located?\n");
    return 0;
  }

  out_records(argv[1], argv[2]);
  seek_record(argv[2], 1);
  seek_record(argv[2], 3);
  seek_record(argv[2], 10);
  
  return 0;
}
