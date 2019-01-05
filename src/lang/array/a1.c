#include <_lang_.h>

char *s1[] = {
	"aaa", "bbb", "ccc", 0,
};

char s2[][3][4] = {
	{ "aa", "bb", "cc" },
	{ "aaa", "bbb", "ccc" },
};

int i1[][4] = {
	{ 0x11, 0x22, 0x33, 0x44, },
	{ 0x44, 0x33, 0x22, 0x11, },
};


void
f1(char **args) {
	char x = args[1][2];
	_unused_(x);
}

/* illife vector */
void
f2(char *args[]) {
	char x = args[1][2];
	_unused_(x);
}

void 
g1(char (*args)[3][4]) {
	char x = args[1][2][3];
	_unused_(x);
}

void
g2(char args[][3][4]) {
	char x = args[1][2][3];
	_unused_(x);
}

void
h1(int (*i)[4]) {
	int x = i[1][2];
	_unused_(x);
}


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	f1(s1);
	f2(s1);
	g1(s2);
	g2(s2);
	h1(i1);
	
	return 0;
}
