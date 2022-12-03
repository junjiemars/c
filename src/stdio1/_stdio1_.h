#ifndef __STDIO1_H___
#define __STDIO1_H___

/*
 *
 * References:
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/contents.html
 *
 */

#include <nustd.h>
#include <nlim.h>
#include <nstr.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/fcntl.h>
#include <sys/stat.h>



#define	_IOFBF	0               /* setvbuf should set fully buffered */
#define	_IOLBF	1               /* setvbuf should set line buffered */
#define	_IONBF	2               /* setvbuf should set unbuffered */

#define	BUFSIZ	NM_LINE_MAX     /* size of buffer used by setbuf */
#define	EOF     (-1)



typedef struct file_s
{
  int             fd;
  int             err;
  int             eof;
  int             flags;
  int             buf_type;
  off_t           offset;
  size_t          buf_size;
  unsigned char  *last;
  unsigned char  *buf;

} FILE;


extern FILE  *stdin, *stdout, *stderr;


int   feof(FILE *);
int   ferror(FILE *);
void  clearerr(FILE *);

int    fileno(FILE *);
int    fclose(FILE *);
int    fflush(FILE *);
FILE  *fopen(const char *restrict, const char *restrict);

void  setbuf(FILE *restrict, char *restrict);
int   setvbuf(FILE *restrict, char *restrict, int, size_t);

int  fgetc(FILE *);
int  fputc(int, FILE *);

size_t  fwrite(const void *restrict, size_t, size_t, FILE *restrict);
size_t  fread(void *restrict, size_t, size_t, FILE *restrict);

int  vsnprintf(char *restrict, size_t, const char *restrict, va_list);
int  fprintf(FILE * restrict, const char * restrict, ...);



#endif  /* __STDIO1_H___ */
