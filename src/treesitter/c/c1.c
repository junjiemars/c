#include <stdio.h>
#include <strings.h>
#include <tree_sitter/api.h>

const TSLanguage *tree_sitter_c (void);

int
main (int argc, char **argv)
{
  char *src;

  src = malloc (BUFSIZ);
  if (src == NULL)
    {
      perror (NULL);
      return 1;
    }

  if (argc > 1)
    {
      strncpy (src, argv[1], BUFSIZ - 1);
    }
  else
    {
      fread (src, BUFSIZ, 1, stdin);
    }

  TSParser *parser = ts_parser_new ();
  ts_parser_set_language (parser, tree_sitter_c ());

  TSTree *tree = ts_parser_parse_string (parser, NULL, src, strlen (src));
  TSNode root_node = ts_tree_root_node (tree);
  char *str = ts_node_string (root_node);

  printf ("%s\n", str);

  free (src);
	free (str);
  ts_tree_delete (tree);
  ts_parser_delete (parser);

  return 0;
}
