int  i2  =  12345;

inline int sqr(int n)
{
	return n*n;
}

/*
 * without `extern', `sqr' would only be an inline fn, so other files
 * would not be able to call it.
 *
 */
extern int sqr(int);
