/*
 * Nore Standard Header (https://github.com/junjiemars)
 */


#ifdef MSVC
char*
dirname(char *path) {
	static TCHAR d[PATH_MAX + 1], *b;
	if (0 == GetFullPathName(path, _countof(d), d, &b)) {
		return 0;
	}
	b[-1] = 0; /* remove '/basename' part */
	return d;
}
#endif /* MSVC */

