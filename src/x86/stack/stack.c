#include <x86.h>

// on MacOS with clang 8.1.0 
long
foo(long a, long b, long c, long d, long e, long f, long g, long h) {
	long x = a+b+c+d+e+f;
	long y = g+h;
	long z = x + y;
	return z;
}

int 
main() {
	foo(1/* edi */
		, 2/* esi */
		, 3/* edx */
		, 4/* ecx */
		, 5/* */
		, 6/* */
		, 7/* r8 */
		, 8/* r9 */);
}
