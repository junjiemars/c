#include <_curl_.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct memory_s {
  char *response;
  size_t size;
} memory_s;

static size_t
on_write(char *ptr, size_t size, size_t nitems, void *userdata) {
  size_t realsize = size * nitems;
  memory_s *m = (memory_s*)userdata;

  char *p = realloc(m->response, m->size+realsize+1);
  if (!p) {
    perror("!panic, realloc failed");
    return 0;
  }

  m->response = p;
  memcpy(&(m->response[m->size]), ptr, realsize);
  m->size += realsize;
  m->response[m->size] = 0;
  
  return realsize;
}

void
test_callback(const char *outfile) {
  CURL *curl = 0;
  CURLcode code = 0;
  char *errbuf = 0;
  FILE *out = 0;
  memory_s m;
  memset(&m, 0, sizeof(m));
  
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

  code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, on_write);
  if (code) {
    fprintf(stderr, "!panic, setopt CURLOPT_WRITEFUNCTION failed\n");
    goto clean_exit;
  }
  
  code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &m);
  if (code) {
    fprintf(stderr, "!panic, setopt CURLOPT_WRITEDATA failed\n");
    goto clean_exit;
  }

  code = curl_easy_perform(curl);
  if (code) {
    fprintf(stderr, "%s\n", errbuf);
  }

  if (!m.size) {
    fprintf(stderr, "!panic, response is 0\n");
    goto clean_exit;
  }
  
  out = fopen(outfile, "wb");
  if (!out) {
    perror("!panic, fopen failed");
    goto clean_exit;
  }
  fwrite((char*)&m.response[0],
         sizeof(char),
         m.size/sizeof(char),
         out);
  if (ferror(out)) {
    perror("!panic, write failed");
  }
  
 clean_exit:
  curl_easy_cleanup(curl);
  if (m.response) {
    free(m.response);
  }
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
  
  test_callback(outfile);
  
  return 0;
}
