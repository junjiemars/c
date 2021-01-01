#include <_io_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if (MSVC)
#  include <io.h>
#  define F_OK 0
#  define access _access
#else
#  include <unistd.h>
#endif


#define NUM_LEN 8
#define NAME_LEN 16

#define OUT_FMT                                 \
  "> No.%d found\n"                             \
  "------------\n"                              \
  "  num: %s\n"                                 \
  " name: %s\n"                                 \
  "stock: %d\n"                                 \
  "price: %lf\n"                                \
  "------------\n"

#define PANIC "!panic"

typedef struct record_s
{
  char num[NUM_LEN];
  char name[NAME_LEN];
  int stock;
  double price;
} record_s;

typedef struct index_s
{
  char num[NUM_LEN];
  int idx;
} index_s;

typedef int (*outbin_fn)(const record_s *record, long *offset, FILE *out);
typedef int (*outidx_fn)(const record_s *record, long offset, FILE *out);

void create_empty_file(const char *path);

/* read record from plain text file */
void read_records(const char *inpath, size_t max,
                  const char *binpath, outbin_fn outbin_fn,
                  const char *idxpath, outidx_fn outidx_fn);

/*
 * Return 0 if find RS in IN success, otherwise 1.
 * If success the OFFSET is the position from the start of IN.
 */
int find_record(const record_s *rs, long *offset, FILE *in);

/*
 * Return 0 if find IS in IN success, otherwise 1.
 * If success the OFFSET is the postion from the start of IN.
 */
int find_index(index_s *const is, long *offset, FILE *in);

/*
 * Return 0 if merge success, otherwise 1.
 */
int merge_bin(const record_s *rs, long *offset, FILE *stream);

/*
 * Return 0 if merge success, otherwise 1.
 */
int merge_idx(const record_s *rs, long offset, FILE *stream);

/*
 * Seek RS by OFFSET in STREAM.
 */
int seek_record(long offset, record_s *rs, FILE *stream);

void test_find(const char *binpath,
               const char *idxpath,
               const char *num);

void
create_empty_file(const char *path)
{
  if (EOF == access(path, F_OK))
    {
      FILE *f = fopen(path, "wb");
      fclose(f);
    }
}

void
read_records(const char *inpath, size_t max,
             const char *binpath, outbin_fn outbin_fn,
             const char *idxpath, outidx_fn outidx_fn)
{
  FILE *in = 0, *outbin = 0, *outidx = 0;

  in = fopen(inpath, "r");
  if (!in)
    {
      perror(PANIC);
      goto clean_exit;
    }

  create_empty_file(binpath);
  outbin = fopen(binpath, "rb+");
  if (!outbin)
    {
      perror(PANIC);
      goto clean_exit;
    }

  create_empty_file(idxpath);
  outidx = fopen(idxpath, "rb+");
  if (!outidx)
    {
      perror(PANIC);
      goto clean_exit;
    }

  record_s ss;
  size_t n = 0;
  memset(&ss, 0, sizeof(record_s));

  while (4 == fscanf(in, "%s %s %d %lf",
                     ss.num,
                     ss.name,
                     &ss.stock,
                     &ss.price))
    {
      long offset = 0;
      if (outbin_fn(&ss, &offset, outbin))
        {
          goto clean_exit;
        }
      if (outidx_fn(&ss, offset, outidx))
        {
          goto clean_exit;
        }

      if (++n >= max)
        {
          fprintf(stdout, PANIC
                  ", exceed the max read limit: %zu(%zu bytes)\n",
                  max, max * sizeof(record_s));
          goto clean_exit;
        }
    }

 clean_exit:
  if (in)
    {
      fclose(in);
    }
  if (outbin)
    {
      fclose(outbin);
    }
  if (outidx)
    {
      fclose(outidx);
    }
}

int
find_record(const record_s *rs, long *offset, FILE *in)
{
  int ret = EXIT_FAILURE;
  clearerr(in);

  fseek(in, 0, SEEK_SET);
  if (ferror(in))
    {
      perror(PANIC);
      goto clean_exit;
    }

  record_s ss;
  int n = 0;

  while (1 == fread(&ss, sizeof(record_s), 1, in))
    {
      if (0 == strncmp(ss.num, rs->num, NUM_LEN))
        {
          *offset = n*sizeof(record_s);
          ret = EXIT_SUCCESS;
          goto clean_exit;
        }
      n++;
    }

 clean_exit:
  clearerr(in);
  return ret;
}

int
find_index(index_s *const is, long *offset, FILE *in)
{
  int ret = EXIT_FAILURE;
  clearerr(in);

  fseek(in, 0, SEEK_SET);
  if (ferror(in))
    {
      perror(PANIC);
      goto clean_exit;
    }

  index_s ss;
  int n = 0;

  while (1 == fread(&ss, sizeof(index_s), 1, in))
    {
      if (0 == strncmp(ss.num, is->num, NUM_LEN))
        {
          *offset = n*sizeof(index_s);
          is->idx = ss.idx;
          ret = EXIT_SUCCESS;
          goto clean_exit;
        }
      n++;
    }

 clean_exit:
  clearerr(in);
  return ret;
}

int
merge_bin(const record_s *rs, long *offset, FILE *inout)
{
  int ret = EXIT_FAILURE;

  if (find_record(rs, offset, inout))
    {
      fseek(inout, 0, SEEK_END);
      if (ferror(inout))
        {
          perror(PANIC);
          goto clean_exit;
        }

      *offset = ftell(inout);
      if (ferror(inout))
        {
          perror(PANIC);
          goto clean_exit;
        }
    }
  else
    {
      fseek(inout, *offset, SEEK_SET);
      if (ferror(inout))
        {
          perror(PANIC);
          goto clean_exit;
        }
    }

  if (1 != fwrite(rs, sizeof(*rs), 1, inout))
    {
      perror(PANIC);
      goto clean_exit;
    }
  ret = EXIT_SUCCESS;

 clean_exit:
  clearerr(inout);
  return ret;
}

int
merge_idx(const record_s *rs, long offset, FILE *inout)
{
  int ret = EXIT_FAILURE;
  index_s is;
  strncpy(&is.num[0], rs->num, NUM_LEN);
  is.idx = offset / sizeof(record_s);

  long offs = 0;
  if (find_index(&is, &offs, inout))
    {
      fseek(inout, 0, SEEK_END);
      if (ferror(inout))
        {
          perror(PANIC);
          goto clean_exit;
        }

      offs = ftell(inout);
      if (ferror(inout))
        {
          perror(PANIC);
          goto clean_exit;
        }
    }
  else
    {
      fseek(inout, offs, SEEK_SET);
      if (ferror(inout))
        {
          perror(PANIC);
          goto clean_exit;
        }
    }

  if (1 != fwrite(&is, sizeof(index_s), 1, inout))
    {
      perror(PANIC);
      goto clean_exit;
    }
  ret = EXIT_SUCCESS;

 clean_exit:
  clearerr(inout);
  return ret;
}

int
seek_record(long offset, record_s *rs, FILE *in)
{
  fseek(in, offset, SEEK_SET);
  if (ferror(in))
    {
      perror(PANIC);
      return EXIT_FAILURE;
    }

  if (1 != fread(rs, sizeof(record_s), 1, in))
    {
      perror(PANIC);
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

void
test_find(const char *binpath,
          const char *idxpath,
          const char *num)
{
  FILE *idx = 0, *bin = 0;

  idx = fopen(idxpath, "rb");
  if (!idx)
    {
      perror(PANIC);
      goto clean_exit;
    }
  bin = fopen(binpath, "rb");
  if (!bin)
    {
      perror(PANIC);
      goto clean_exit;
    }

  index_s is;
  record_s rs;
  long offset = 0;
  memset(&is, 0, sizeof(index_s));
  memset(&rs, 0, sizeof(record_s));
  strncpy(&is.num[0], num, NUM_LEN);

  fprintf(stdout, "\nfinding %s ...\n", num);
  if (find_index(&is, &offset, idx))
    {
      fprintf(stdout, "! Num.%s no found in %s\n------------\n",
              num, idxpath);
    }
  else
    {
      if (seek_record(is.idx*sizeof(record_s), &rs, bin))
        {
          fprintf(stdout, "! No.%zu no found in %s\n------------\n",
                  offset/sizeof(record_s), binpath);
        }
      else
        {
          fprintf(stdout, OUT_FMT,
                  is.idx+1, rs.num, rs.name, rs.stock, rs.price);
        }
    }

 clean_exit:
  if (idx)
    {
      fclose(idx);
    }
  if (bin)
    {
      fclose(bin);
    }
}


int
main(int argc, char **argv)
{
  if (argc < 5)
    {
      fprintf(stderr,
              "please, input max read limit and "
              "where records.txt/records.bin/records.idx located?\n");
      return 1;
    }

  size_t max = (size_t)atol(argv[1]);
  const char *txt = argv[2];
  const char *bin = argv[3];
  const char *idx = argv[4];

  read_records(txt, max,
               bin, merge_bin,
               idx, merge_idx);

  test_find(bin, idx, "PKL070");
  test_find(bin, idx, "GSF555");
  test_find(bin, idx, "AAPL");
  test_find(bin, idx, "GOOG");

  return 0;
}
