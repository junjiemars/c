#include "_cio_.h"
#include <string.h>


static void change_mode(const char *);


int
main(int argc, char **argv)
{
	if (argc < 2) {
    fprintf(stderr, "usage: <filename>\n");
    return 1;
	}
  change_mode(argv[1]);

	return 0;
}

void
change_mode(const char *name)
{
	FILE *f1 = fopen(name, "r");
	if (!f1)
    {
      perror("!panic");
      return;
    }
	for (int i = 0; i < 3; i++)
    {
      int ch = fgetc(f1);
      if (EOF == ch)
        {
          break;
        }
      fputc(ch, stdout);
    }
	fputc('\n', stdout);

	FILE *f2 = freopen(name, "w", f1);
	if (!f2)
    {
      perror("!panic");
      return;
    }
	char *s = "|mode to 'w'|";
	size_t n = fwrite(s, sizeof(*s), strlen(s), f2);
	fprintf(stdout, "wrote %zu bytes into %s\n", n, name);
	if (ferror(f2))
    {
      perror("!panic");
    }
	fclose(f2);


}
