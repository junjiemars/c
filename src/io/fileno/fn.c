#include "_io_.h"


int
main(int argc, char **argv) 
{
  FILE *out = 0;

	_unused_(argc);

	printf("stdin=%d, stdout=%d, stderr=%d\n",
				 fileno(stdin),
				 fileno(stdout),
				 fileno(stderr));

	out = fdopen(fileno(stdout), "w");
	if (!out) 
    {
      perror(0);
      return 1;
    }
	fprintf(out, "end of %s\n", argv[0]);

#ifdef MSVC
	/* fclose stdout should: */
  /* Security check failure or stack buffer overrun - code c0000409 */
#else
	fclose(out);
#endif

	return 0;
}
