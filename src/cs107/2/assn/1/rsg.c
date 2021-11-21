#include "_cs107_.h"
#include <nio.h>


/* #include "definition.h" */
/* #include "production.h" */

/* typedef struct */
/* { */

/* } production; */
/* void production_free(production*); */
/* production production_copy(production*); */

/* #define P */
/* #include <str.h> */
/* #define T production */
/* #include <vec.h> */

/* typedef struct */
/* { */
/*   (void *)(FILE *) def; */
/*   str nonterminal; */
/*   vec_production possible_expansions; */

/* } definition; */


#define P
#include <str.h>
#define T str
#include <vec.h>

static void read_grammar(FILE *infile, vec_str *grammar);
static void def(FILE *infile);

/* static void get_random_production(void); */


/* static vec_str phrases; */


void
read_grammar(FILE *infile, vec_str *grammar)
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
          goto clean_exit;
        }
      /* fputc('{', infile); */

      def(infile);
      /* getline(infile, uselessText, '{'); */
      /* if (infile.eof()) return;  // true? we encountered EOF before we saw a '{': no more productions! */
      /* infile.putback('{'); */
      /* Definition def(infile); */
      /* grammar[def.getNonterminal()] = def; */
    }

 clean_exit:
  free(useless_text);
}

void
def(FILE *infile)
{
  char    *useless_text;
  size_t   len;

  useless_text = NULL;
  len = 0;
  while (true)
    {
      getline(&useless_text, &len, infile);
      if (strcmp(useless_text, "}") != 0)
        {
          fprintf(stdout, "%s", useless_text);
        }
      else
        {
          break;
        }
      if (feof(infile))
        {
          break;
        }
    }

  free(useless_text);
}

/* void */
/* get_random_production(void) */
/* { */
/* } */


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
  /* _unused_(definition); */
  /* _unused_(get_random_production); */
  /* _unused_(phrases); */

  /* grammar = set_str_init(); */
  /* read_grammar(grammar_file, &grammar); */
  /* fprintf(stderr, "The grammar file called \"%s\" contains %d definitions.", */
  /*         argv[1], grammar.size()); */

  fclose(grammar_file);
  return 0;
}
