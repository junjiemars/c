#ifndef _SIG2STR_H_
#define _SIG2STR_H_

/*
 * Implements `sig2str(3)' and `str2sig(3)'.
 *
 * https://docs.oracle.com/cd/E36784_01/html/E36874/sig2str-3c.html
 *
 */

#define N_SIG2STR    32
#define SIG2STR_MAX  64


int  sig2str(int signo, char *str);
int  str2sig(const char *str, int *signo);


#endif  /* _SIG2STR_H_ */
