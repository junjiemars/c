#include <_env_.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if NM_HAVE_SSCANF_S_FN
#  define sscanf sscanf_s
#endif

#if MSVC
#  pragma warning(disable: 4996)
#endif

int 
main(int argc, const char* argv[]) {
	printf("----------\n");
	printf("#your can set COUNT, TEXT via command-line args or env vars\n");

	int count = 3;
	char text[32] = "Hello.";

	for (int i=1; i < argc; ++i) {
		sscanf(argv[i], "--COUNT=%i", &count);
#if NM_HAVE_SSCANF_S_FN
		sscanf(argv[i], "--TEXT=%s", text, (unsigned)sizeof(text));
#else
		sscanf(argv[i], "--TEXT=%s", text);
#endif
	}

	char *c = getenv("COUNT");
	if (c) count = atoi(c);

	char *text_env = getenv("TEXT");
	if (text_env) strncpy(text, text_env, sizeof(text)/sizeof(text[0]));

	for (int i=0; i < count; i++) {
		printf("%s\n", text);
	}
	putchar('\n');
}
