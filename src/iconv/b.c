#include <_iconv_.h>
#include <string.h>


#define BUF_SIZE 64

void test_utf8_to_gb18030(void);

void
test_utf8_to_gb18030(void) {
  iconv_t cd;
  char in_buf[] = "中文正体abc123";
  char out_buf[BUF_SIZE];
  char *in, *out;
  size_t in_len, out_len;
  size_t n;

  cd = iconv_open("GB18030", "UTF-8");
  if ((iconv_t) -1 == cd) {
    perror("!panic");
    goto clean_exit;
  }

  in_len = strlen(in_buf);
  out_len = BUF_SIZE;
  in = &in_buf[0];
  out = &out_buf[0];
  
  n = iconv(cd, &in, &in_len, &out, &out_len);
  if ((size_t) -1 == n) {
    perror("!panic");
    goto clean_exit;
  }
  printf("utf8 -> gb18030: %s\n", out_buf);

 clean_exit:
  if (-1 == iconv_close(cd)) {
    perror("!panic");
  }
}


int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  test_utf8_to_gb18030();
  
  return 0;
}
