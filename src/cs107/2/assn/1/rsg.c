#include "_cs107_.h"
#include <nio.h>

#define P
#include <str.h>
#define T str
#include <set.h>

/* #include "definition.h" */
/* #include "production.h" */

static void read_grammar(FILE *infile, set_str *grammar);

void
read_grammar(FILE *infile, set_str *grammar)
{
  char    *useless_text;
  size_t   len;

  _unused_(infile);
  _unused_(grammar);

  useless_text = NULL;
  len = 0;
  while (true)
    {
      getdelim(&useless_text, &len, '{', infile);
      if (feof(infile))
        {
          return;
        }
      fputs("{", infile);
      /* getline(infile, uselessText, '{'); */
      /* if (infile.eof()) return;  // true? we encountered EOF before we saw a '{': no more productions! */
      /* infile.putback('{'); */
      /* Definition def(infile); */
      /* grammar[def.getNonterminal()] = def; */
    }
  free(useless_text);
}


int
main(int argc, char **argv)
{
  FILE *grammar_file;
  /* set_str grammar; */

  if (argc < 2)
    {
      fprintf(stderr, "You need to specify the name of a grammar file.\n"
              "Usage: rsg <path to grammar text file>\n");
      return 1;
    }

  grammar_file = fopen(argv[1], "r");
  if (!grammar_file)
    {
      fprintf(stderr, "Failed to open the file named \"%s\"."
              "Check to ensure the file exists.", argv[1]);
      return 2;
    }

  read_grammar(grammar_file, NULL);

  /* grammar = set_str_init(); */
  /* read_grammar(grammar_file, &grammar); */
  /* fprintf(stderr, "The grammar file called \"%s\" contains %d definitions.", */
  /*         argv[1], grammar.size()); */

  fclose(grammar_file);
  return 0;
}
