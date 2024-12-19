%{
#include <pthread.h>

typedef struct WcState
{
  int n_char;
  int n_word;
  int n_line;
  char *path;
  FILE *file;
  pthread_t tid;
} WcState;

%}

%option reentrant
%option extra-type="WcState *"

WORD [^ \t\v\r\n\f]
LINE \n
CHAR .
%%

{WORD}+ {
  ++yyextra->n_word;
  yyextra->n_char += yyget_leng (yyscanner);
}

{LINE} {
  ++yyextra->n_line;
  ++yyextra->n_char;
}

{CHAR} {
  ++yyextra->n_char;
}

%%

#include <locale.h>

static void *wc (void *);

int
main (int argc, char **argv)
{
  WcState *wcs;

  wcs = calloc (argc, sizeof (WcState));
  if (!wcs)
    {
      perror (NULL);
      return 1;
    }

  if (argc > 1)
    {
      int n_char = 0;
      int n_word = 0;
      int n_line = 0;

      for (int i = 1; i < argc; i++)
        {
          wcs[i].path = argv[i];
          wcs[i].file = fopen (wcs[i].path, "r");
          pthread_create (&wcs[i].tid, NULL, wc, &wcs[i]);
        }

      for (int i = 1; i < argc; i++)
        {
          pthread_join (wcs[i].tid, 0);
          printf ("%8d%8d%8d %s\n", wcs[i].n_line, wcs[i].n_word,
                  wcs[i].n_char, wcs[i].path);
          n_char += wcs[i].n_char;
          n_word += wcs[i].n_word;
          n_line += wcs[i].n_line;
        }
      printf ("%8d%8d%8d total\n", n_line, n_word, n_char);
    }
  else
    {
      wcs[0].path = "";
      wcs[0].file = stdin;
      wc (&wcs[0]);
    }

  return 0;
}

void *
wc (void *arg)
{
  yyscan_t scanner;
  WcState *wcs = (WcState *)arg;

  yylex_init_extra (wcs, &scanner);
  yyset_in (wcs->file, scanner);
  yylex (scanner);
  yylex_destroy (scanner);

  if (wcs->path[0] != '\0')
    {
      fclose (wcs->file);
    }

  pthread_exit (0);
}
