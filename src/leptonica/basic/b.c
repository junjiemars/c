#include <_leptonica_.h>


int
  main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);
  
  char *s, *d;
  PIX *pixs, *pixd;  

  if (argc < 3)
    {
      printf("please, specify input and output image path!\n");
      return 1;
    }

  s = argv[1];
  d = argv[2];

  pixs = pixRead(s);
  pixd = pixScale(pixs, 0.70, 0.70);
  pixWrite(d, pixd, IFF_PNG);
  pixDestroy(&pixs);
  pixDestroy(&pixd);

  return 0;
}
