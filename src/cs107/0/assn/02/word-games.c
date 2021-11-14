#include "_cs107_.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define P
#include <str.h>
#define T str
#include <vec.h>


static void load_words(vec_str *words, const char *where);
static void play_word_games(const vec_str *words);
static bool is_legitimate_response(const str *response);
static void list_words_containing(const vec_str *words, const str *letters);
static bool word_contains_all_letters(const str *word, const str *letters);


void
load_words(vec_str *words, const char *w)
{
  FILE  *f;
  int    n;
  str    s;

  f = fopen(w, "r");
  if (!f)
    {
      perror(NULL);
      return;
    }

  while (EOF != (n = fgetc(f)))
    {
      s = str_init("");
      while ('\n' != n)
        {
          str_append(&s, (const char *) &n);
          n = fgetc(f);
          if (EOF == n)
            {
              vec_str_push_back(words, s);
              goto clean_exit;
            }
        }
      vec_str_push_back(words, s);
    }

 clean_exit:
  fclose(f);
}


void
play_word_games(const vec_str *words)
{
  int n;
  str response;
  
  while (true)
    {
      printf("Please enter a string of characters: ");
      response = str_init("");

      if (0 == (n = fgetc(stdin)))
        {
          printf("<exit>");
          break;
        }

      while (n != '\n')
        {
          str_append(&response, (const char *) &n);
          n = fgetc(stdin);
        }
      printf("<%s>\n", response.value);
      
      if (is_legitimate_response(&response))
        {
          list_words_containing(words, (const str*) &response);
        }
      else
        {
          printf("We didn't like one or more of those characters. "
                 "Let's try that again\n");
        }
    }
}


bool
is_legitimate_response(const str *response)
{
  size_t  i;
  for (i = 0; i < response->size; i++)
    {
      if (!isalpha(response->value[i]) || !islower(response->value[i]))
        {
          return false;
        }
    }
  
  return true;
}


void
list_words_containing(const vec_str *words, const str *letters)
{
  str header;

  header = str_init("The following English words contain all of ");
  str_append(&header, "the letters in \"");
  str_append(&header, letters->value);
  str_append(&header, "\"");

  printf("%s\n------------\n", str_c_str(&header));
  /* string divider(header.size(), '-'); */

  foreach(vec_str, (vec_str *) words, it)
    {
      if (word_contains_all_letters(it.ref, letters))
        {
          printf("   %s\n", str_c_str(it.ref));
        }
    }
  printf("\n");
}

bool
word_contains_all_letters(const str *word, const str *letters) 
{
  size_t i;

  for (i = 0; i < letters->size; i++)
    {
      if (str_find((str *) word, letters->value))
        {
          return false;
        }
    }
  
  return true;
}


int
main(int argc, char **argv)
{
  const char *ss = 0;

  if (argc < 2)
    {
      fprintf(stderr, "where is words file\n");
    }
  ss = (const char *) argv[1];

  vec_str words = vec_str_init();
  load_words(&words, ss);
  play_word_games((const vec_str *) &words);

  vec_str_free(&words);

  return 0;
}
