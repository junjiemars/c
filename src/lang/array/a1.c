#include <_lang_.h>

char *s1[] = {
	"aaa", "bbb", "ccc", 0,
};

void
f1(char **args) {
	_unused_(args);
}

void
f2(char *args[]) {
	_unused_(args);
}

char s2[][3][4] = {
	{ "aa", "bb", "cc" },
	{ "aaa", "bbb", "ccc" },
};

void 
g1(char (*args)[3][4]) {
	_unused_(args);
}

void
g2(char args[][3][4]) {
	_unused_(args);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	f1(s1);
	f2(s1);

	g1(s2);
	g2(s2);
	return 0;
}
