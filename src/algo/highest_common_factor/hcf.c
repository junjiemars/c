#include <_algo_.h>
#include <stdio.h>


int
hcf1(m, n) {
	if (0 == n) return m;
	return hcf1(n, m % n);
}

int
hcf2(m, n) {
	int r;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int m, n;
	fscanf(stdin, "%i, %i", &m, &n);
	printf("hcf1(%i, %i) = %i\n", m, n, hcf1(m, n));
	printf("hcf2(%i, %i) = %i\n", m, n, hcf1(m, n));
	
	return 0;
}
