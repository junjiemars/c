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
  _unused_(infile);
  _unused_(grammar);
  /* while (true) { */
  /*   string uselessText; */
  /*   getline(infile, uselessText, '{'); */
  /*   if (infile.eof()) return;  // true? we encountered EOF before we saw a '{': no more productions! */
  /*   infile.putback('{'); */
  /*   Definition def(infile); */
  /*   grammar[def.getNonterminal()] = def; */
  /* } */
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

  _unused_(read_grammar);

  /* grammar = set_str_init(); */
  /* read_grammar(grammar_file, &grammar); */
  /* fprintf(stderr, "The grammar file called \"%s\" contains %d definitions.", */
  /*         argv[1], grammar.size()); */

  fclose(grammar_file);
  return 0;
}
