#include "_stdio_.h"

static void out_file_attr(const FILE*, const char*);


int
main(void)
{
  fprintf(stdout, "stdin = %d, stdout = %d, stderr = %d\n",
          fileno(stdin), fileno(stdout), fileno(stderr));

  fgetc(stdin);
  fprintf(stderr, "to stderr\n");

  out_file_attr(stdin, _str_(stdin));
  out_file_attr(stdout, _str_(stdout));
  out_file_attr(stderr, _str_(stderr));

	return 0;
}

void
out_file_attr(const FILE * fp, const char *name)
{
  printf("\n%s (FILE @%p)\n------------\n", name, fp);

#if (DARWIN)
  printf("_flags = %d\n"
         "_blksize = %u\n"
         "_offset = %lld\n",
         fp->_flags,
         fp->_blksize,
         fp->_offset);

#elif (LINUX)
  printf("_flags = %u\n"
         "_IO_buf_end - _IO_buf_base = (%ld)\n"
         "_offset = %ld\n",
         fp->_flags,
         fp->_IO_buf_end - fp->_IO_buf_base,
         fp->_offset);


#endif  /* DARWIN */
}
