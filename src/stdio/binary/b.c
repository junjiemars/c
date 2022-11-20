#include "_stdio_.h"

#define NAME_SIZE  16


typedef struct rect_s
{
  char  name[NAME_SIZE];
  int   width;
  int   height;

} rect_s;


static void  out(const rect_s *, const char *);
static void  in(rect_s *, const char *);


int
main(int argc, char **argv)
{
  char    *pathname;
  rect_s   rect  =  {0};

  if (argc < 2)
    {
      fprintf(stderr, "usage: <pathname> [name] [width] [height]\n");
      exit(EXIT_FAILURE);
    }
  pathname = argv[1];

  if (argc < 5)
    {
      /* read from binary file */
      in(&rect, pathname);
    }
  else
    {
      strncpy(rect.name, argv[2], NAME_SIZE-1);
      rect.width = (int) strtol(argv[3], 0, 16);
      rect.height = (int) strtol(argv[4], 0, 16);

      /* write to binary file */
      out(&rect, pathname);
    }

  exit(EXIT_SUCCESS);
}


void
out(const rect_s *rect, const char *where)
{
  FILE *f = fopen(where, "w");
  if (!f)
    {
      perror(where);
      return;
    }

  size_t len = fwrite(rect, sizeof(*rect), 1, f);

  if (ferror(f))
    {
      perror(where);
      clearerr(f);
      goto clean_exit;
    }

  assert(len == 1);

 clean_exit:
  fclose(f);
}

void
in(rect_s *rect, const char *where)
{
  FILE *f = fopen(where, "r");
  if (!f)
    {
      perror(where);
      return;
    }

  size_t len = fread(rect, sizeof(*rect), 1, f);

  if (ferror(f))
    {
      perror(where);
      clearerr(f);
      goto clean_exit;
    }

  assert(len == 1);

  fprintf(stdout,"\
rect_s:{\n\
  name: \"%s\",\n\
  width:  0x%08x,\n\
  height: 0x%08x\n\
}\n", rect->name, rect->width, rect->height);

 clean_exit:
  fclose(f);
}
