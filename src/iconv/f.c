#include <_iconv_.h>
#include <string.h>


#define BUF_SIZE 64

void test_utf8_to_gb18030(const char *dst_file, const char *src_file);

void
test_utf8_to_gb18030(const char *dst_file, const char *src_file) {
  FILE *dst = 0, *src = 0;
  iconv_t cd = (iconv_t) -1;
  char in_buf[BUF_SIZE], out_buf[BUF_SIZE];
  size_t n;

  dst = fopen(dst_file, "wb");
  if (!dst) {
    perror("!panic");
    goto clean_exit;
  }
  src = fopen(src_file, "rb");
  if (!src) {
    perror("!panic");
    goto clean_exit;
  }

  cd = iconv_open("GB18030", "UTF-8");
  if ((iconv_t) -1 == cd) {
    perror("!panic");
    goto clean_exit;
  }

  while (0 < (n = fread(in_buf, sizeof(char), BUF_SIZE, src))) {
    char *in, *out;
    size_t in_len, out_len;
    in = &in_buf[0];
    out = &out_buf[0];
    in_len = n;
    out_len = BUF_SIZE;
    size_t cn = iconv(cd, &in, &in_len, &out, &out_len);
    if ((size_t) -1 == cn) {
      perror("!panic, iconv failed");
      fseek(src, -1, SEEK_CUR);
      if (ferror(src)) {
        perror("!panic, fread failed");
        goto clean_exit;
      }
      continue;
    }
    fwrite(out_buf, sizeof(char), out_len, dst);
    if (ferror(dst)) {
      perror("!panic, fwrite failed");
      goto clean_exit;
    }
  }

  if (ferror(src)) {
    perror("!panic, fread failed");
  }
  
 clean_exit:
  if (-1 == iconv_close(cd)) {
    perror("!panic");
  }
  if (dst) {
    fclose(dst);
  }
  if (src) {
    fclose(src);
  }
}


int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  if (argc < 3) {
    printf("where the dst file and src file\n");
    return 0;
  }

  const char *dst_file = argv[1];
  const char *src_file = argv[2];
  
  test_utf8_to_gb18030(dst_file, src_file);
  
  return 0;
}
