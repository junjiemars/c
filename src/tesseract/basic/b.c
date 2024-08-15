#include "_tesseract_.h"

void test_read (const char *);

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <image-path>\n", argv[0]);
      return 0;
    }
  const char *filename = argv[1];
  test_read (filename);

  return 0;
}

void
test_read (const char *filename)
{
  PIX *img = 0;
  TessBaseAPI *api = 0;
  char *text = 0;

  if (0 == (img = pixRead (filename)))
    {
      perror ("!panic, read image failed, caused by");
      goto clean_exit;
    }

  api = TessBaseAPICreate ();
  if (0 != TessBaseAPIInit3 (api, 0, "eng"))
    {
      perror ("!panic, init tesseract failed, caused by");
      goto clean_exit;
    }

  TessBaseAPISetImage2 (api, img);

  if (0 != TessBaseAPIRecognize (api, 0))
    {
      perror ("!panic, recognize failed, caused by");
      goto clean_exit;
    }

  if (0 == (text = TessBaseAPIGetUTF8Text (api)))
    {
      perror ("!panic, get text failed, caused by");
      goto clean_exit;
    }
  fputs ("text\n----------\n", stdout);
  fputs (text, stdout);
  fputs ("----------\n", stdout);

clean_exit:
  if (text)
    {
      TessDeleteText (text);
    }
  if (api)
    {
      TessBaseAPIEnd (api);
      TessBaseAPIDelete (api);
    }
  if (img)
    {
      pixDestroy (&img);
    }
}
