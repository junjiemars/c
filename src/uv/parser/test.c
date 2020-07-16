#include "_uv_.h"
#include "parser/http_parser.h"
#include <stdlib.h>

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  http_parser *parser = malloc(sizeof(http_parser));
  http_parser_init(parser, HTTP_REQUEST);
  free(parser);

  return 0;
}
