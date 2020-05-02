#include <_io_.h>
#include <stdio.h>
#include <string.h>

#define NUM_LEN 7
#define OUT_FMT "No.%d found\n----\nnum: %s\nname: %s\nstock: %d\nprice: %lf\n"

typedef struct record_s {
  char num[NUM_LEN];
  char name[25];
  int stock;
  double price;
} record_s;

typedef struct index_s {
  char num[NUM_LEN];
  int idx;
} index_s;

void
out_records(const char *inpath, const char *binpath, const char *idxpath) {
  FILE *in = 0, *outbin = 0, *outidx = 0;
  in = fopen(inpath, "r");
  if (!in) {
    perror("!panic");
    return;
  }
  outbin = fopen(binpath, "wb");
  if (!outbin) {
    perror("!panic");
    goto clean_exit;
  }
  outidx = fopen(idxpath, "wb");
  if (!outidx) {
    perror("!panic");
    goto clean_exit;
  }
  
  record_s ss = {};
  index_s is = {};

  int n = 0;
  while (4 == fscanf(in, "%s %s %d %lf",
                     ss.num,
                     ss.name,
                     &ss.stock,
                     &ss.price)) {
    if (1 != fwrite(&ss, sizeof(record_s), 1, outbin)) {
      perror("!panic");
      goto clean_exit;
    }
    strncpy(is.num, ss.num, NUM_LEN);
    is.idx = n;
    if (1 != fwrite(&is, sizeof(index_s), 1, outidx)) {
      perror("!panic");
      goto clean_exit;
    }
    n++;
  }
  
 clean_exit:
  fclose(outidx);
  fclose(outbin);
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
  fprintf(stdout, OUT_FMT,
          n, ss.num, ss.name, ss.stock, ss.price);

 clean_exit:
  fclose(in);
}

void
find_record(const char *binpath, const char *idxpath, const char *num) {
  FILE *idx = 0, *bin = 0;
  idx = fopen(idxpath, "rb");
  if (!idx) {
    perror("!panic");
    return;
  }
  bin = fopen(binpath, "rb");
  if (!bin) {
    perror("!panic");
    goto clean_exit;
  }

  index_s is = {};
  record_s ss = {};

  while (1 == fread(&is, sizeof(index_s), 1, idx)) {
    if (0 == strncmp(num, is.num, NUM_LEN)) {
      if (0 == fseek(bin, (is.idx)*sizeof(record_s), SEEK_SET)) {
        if (1 == fread(&ss, sizeof(record_s), 1, bin)) {
          fprintf(stdout, OUT_FMT,
                  is.idx, ss.num, ss.name, ss.stock, ss.price);
          goto clean_exit;
        }
      } 
    }
  }

  if (ferror(idx)) {
    perror("!panic");
  }
  if (feof(idx)) {
    fprintf(stdout, "!no found\n----\n");
  }

 clean_exit:
  fclose(idx);
  fclose(bin);
}


int
main(int argc, char **argv) {
  if (argc < 4) {
    fprintf(stderr, "where the records.txt/records.bin/records.idx located?\n");
    return 0;
  }

  const char *txt = argv[1];
  const char *bin = argv[2];
  const char *idx = argv[3];

  out_records(txt, bin, idx);
  
  seek_record(bin, 1);
  seek_record(bin, 3);
  seek_record(bin, 10);

  find_record(bin, idx, "PKL070");
  find_record(bin, idx, "DKP080");
  
  return 0;
}
