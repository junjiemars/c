#include "_tesseract_.h"
#include <stdio.h>
#include <string.h>

void
test_out_pdf(const char *infile, const char* outbase, int timeout) {
  TessBaseAPI *api = 0;
  TessResultRenderer *renderer = 0;
  const char *datadir = 0;

  api = TessBaseAPICreate();
	if(0 != TessBaseAPIInit3(api, 0, "eng")) {
    perror("!panic, init tesseract failed, caused by");
    goto clean_exit;
  }

  datadir = TessBaseAPIGetDatapath(api);
  if (0 == datadir) {
    perror("!panic, get data path failed, caused by");
    goto clean_exit;
  }
  
  renderer = TessPDFRendererCreate(outbase, datadir, 0);
  if (0 == renderer) {
    perror("!panic, create renderer failed, caused by");
    goto clean_exit;
  }
  
  BOOL ok = TessBaseAPIProcessPages(api, infile, 0, timeout, renderer);
  if (ok) {
    fprintf(stdout, "... output pdf successed\n");
  }

 clean_exit:
	if (api) {
    TessBaseAPIEnd(api);
    TessBaseAPIDelete(api);
  }
}

int
main(int argc, char **argv) {
  if (argc < 4) {
    fprintf(stdout, "where input image and output base located\n");
    return 0;
  }
  const char *infile = argv[1];
  const char *outbase = argv[2];
  int timeout = 5000;
  sscanf(argv[3], "%i", &timeout);
  
  test_out_pdf(infile, outbase, timeout);
  return 0;
}
