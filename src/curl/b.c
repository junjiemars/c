#include <_curl_.h>
#include <stdio.h>

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
  CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
  if (CURLE_OK != code) {
    perror("!panic");
    return code;
  }

  curl_version_info_data *ver = curl_version_info(CURLVERSION_NOW);
  if (ver) {
    printf("curl current version: %s\n", ver->version);
  }
  
  CURL *curl = curl_easy_init();
  if (!curl) {
    perror("!panic");
    return 1;
  }
  curl_easy_setopt(curl, CURLOPT_URL, "https://curl.haxx.se");
  curl_easy_perform(curl);
  
  curl_easy_cleanup(curl);
  return 0;
}
