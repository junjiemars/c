#include "_cio_.h"

static void out_file_attr(const FILE*, const char*);


int
main(void)
{
  /* int  rc; */

  fprintf(stdout, "stdin = %d, stdout = %d, stderr = %d\n",
          fileno(stdin), fileno(stdout), fileno(stderr));

  /* rc = fgetc(stdin); */
  fprintf(stderr, "to stderr\n");

  out_file_attr(stdin, _str_(stdin));
  out_file_attr(stdout, _str_(stdout));
  out_file_attr(stderr, _str_(stderr));

	return 0;
}

void
out_file_attr(const FILE * fp, const char *name)
{
  printf("\nFILE (%p)\n------------\n", fp);

#if (DARWIN)
  printf("%s->_flags = %d\n"
         "%s->_blksize = %u\n"
         "%s->_offset = %lld\n",
         name, fp->_flags,
         name, fp->_blksize,
         name, fp->_offset);

#endif  /* DARWIN */
}
