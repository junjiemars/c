#include "_iconv_.h"
#include <string.h>


static void  test_utf8_to_gb18030(void);


int
main(void)
{
  test_utf8_to_gb18030();

  return 0;
}


void
test_utf8_to_gb18030(void)
{
  iconv_t   cd;
  char     *inbuf  =  "A中文正体abc123";
  char      outbuf[BUFSIZ], *poutbuf;
  size_t    inbuflen, outbuflen, n;

  if ((cd = iconv_open("GB18030", "UTF-8")) == (iconv_t) -1)
    {
      perror(NULL);
      return;
    }

  inbuflen = strlen(inbuf);
  outbuflen = BUFSIZ;
  poutbuf = &outbuf[0];

  if ((n = iconv(cd, &inbuf, &inbuflen, &poutbuf, &outbuflen)) == (size_t) -1)
    {
      perror(NULL);
      goto clean_exit;
    }

  printf("utf8 -> gb18030: %s\n", outbuf);

 clean_exit:
  if (iconv_close(cd) == -1)
    {
      perror(NULL);
    }
}
