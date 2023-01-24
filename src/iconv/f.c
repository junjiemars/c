#include "_iconv_.h"


static void  test_utf8_to_gb18030(const char*, const char*);


int
main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "usage: <dst> <src>\n");
    exit(EXIT_FAILURE);
  }

  test_utf8_to_gb18030(argv[1], argv[2]);

  exit(EXIT_SUCCESS);
}

void
test_utf8_to_gb18030(const char *dst, const char *src)
{
  FILE     *fout  =  NULL, *fin = NULL;
  char      inbuf[BUFSIZ], outbuf[BUFSIZ];
  iconv_t   cd    =  (iconv_t) -1;
  size_t    n;

  if ((fout = fopen(dst, "wb")) == NULL)
    {
      perror(NULL);
      goto clean_exit;
    }

  if ((fin = fopen(src, "rb")) == NULL)
    {
      perror(NULL);
      goto clean_exit;
    }

  if ((cd = iconv_open("GB18030", "UTF-8")) == (iconv_t) -1)
    {
      perror(NULL);
      goto clean_exit;
    }

  while ((n = fread(inbuf, sizeof(*inbuf), BUFSIZ, fin)) > 0)
    {
      char    *in, *out;
      size_t   inlen, outlen;

      in = inbuf;
      out = outbuf;
      inlen = n;
      outlen = BUFSIZ;

      if (iconv(cd, &in, &inlen, &out, &outlen) == (size_t) -1)
        {
          perror(NULL);
          goto clean_exit;
        }

      fwrite(outbuf, sizeof(*outbuf), BUFSIZ - outlen, fout);

      if (ferror(fout))
        {
          perror(NULL);
          goto clean_exit;
        }

    }

  if (ferror(fin))
    {
      perror(NULL);
    }

  printf("... done\n");

 clean_exit:
  if (cd != (iconv_t) -1)
    {
      if (iconv_close(cd) == -1)
        {
          perror("! iconv_close failed");
        }
    }
  if (fout)
    {
      fclose(fout);
    }
  if (fin)
    {
      fclose(fin);
    }
}
