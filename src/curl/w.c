#include <_curl_.h>
#include <stdio.h>
#include <stdlib.h>

void
test_write(const char *outfile) {
  CURL *curl = 0;
  CURLcode code = 0;
  char *errbuf = 0;
  FILE *out = 0;
  
  curl = curl_easy_init();
  if (!curl) {
    fprintf(stderr, "!panic, init failed\n");
    return;
  }

  errbuf = malloc(CURL_ERROR_SIZE);
  if (0 == errbuf) {
    perror("!panic, alloc memory for errbuf failed");
    goto clean_exit;
  }

  code = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
  if (code) {
    fprintf(stderr, "setopt CURLOPT_ERRORBUFFER failed\n");
    goto clean_exit;
  }
  
  code = curl_easy_setopt(curl, CURLOPT_URL, "https://curl.haxx.se");
  if (code) {
    fprintf(stderr, "!panic, setopt CURLOPT_URL failed\n");
    goto clean_exit;
  }
  
  out = fopen(outfile, "wb");
  if (!out) {
    perror("!panic, fopen failed");
    goto clean_exit;
  }

  code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
  if (code) {
    fprintf(stderr, "!panic, setopt CURLOPT_WRITEFUNCTION failed\n");
    goto clean_exit;
  }

  code = curl_easy_perform(curl);
  if (code) {
    fprintf(stderr, "%s\n", errbuf);
  }

 clean_exit:
  curl_easy_cleanup(curl);
  fclose(out);
}

int
main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "where the output file located\n");
    return 0;
  }
  
  CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
  if (CURLE_OK != code) {
    perror("!panic");
    return code;
  }

  const char *outfile = argv[1];
  
  test_write(outfile);
  
  return 0;
}
