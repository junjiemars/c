#include <_io_.h>
#include <stdio.h>
#include <string.h>


void
change_mode(const char *name) {
	FILE *f1 = fopen(name, "r");
	if (!f1) {
		perror("!panic");
		return;
	}
	for (int i = 0; i < 3; i++) {
		int ch = fgetc(f1);
		if (EOF == ch) {
			break;
		}
		fputc(ch, stdout);
	}
	if (feof(f1)) {
		fclose(f1);
		return;
	}
	char *s = "|mode to 'w'|";
	FILE *f2 = freopen(name, "w", f1);
	if (!f2) {
		perror("!panic");
		return;
	}
	fwrite(s, sizeof(*s), strlen(s), f2);
	if (ferror(f2)) {
		perror("!panic");
	}
	fclose(f2);
}

void
reopen(const char *name) {
	_unused_(name);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		change_mode(argv[1]);
		reopen(argv[1]);
	}
	
	return 0;
}
