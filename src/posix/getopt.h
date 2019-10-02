#ifndef _GETOPT_H_
/**
 * DISCLAIMER
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is a part of the w64 mingw-runtime package.
 *
 * The w64 mingw-runtime package and its code is distributed in the hope that it 
 * will be useful but WITHOUT ANY WARRANTY.  ALL WARRANTIES, EXPRESSED OR 
 * IMPLIED ARE HEREBY DISCLAIMED.  This includes but is not limited to 
 * warranties of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#define _GETOPT_H_

/* All the headers include this file. */
#include <crtdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int optind;		/* index of first non-option in argv      */
extern int optopt;		/* single option character, as parsed     */
extern int opterr;		/* flag to enable built-in diagnostics... */
				              /* (user may set to zero, to suppress)    */

extern char *optarg;	/* pointer to argument of current option  */

extern int getopt(int nargc,
									char * const *nargv,
									const char *options);

#ifdef __cplusplus
}
#endif

/*
 * POSIX requires the `getopt' API to be specified in `unistd.h';
 * thus, `unistd.h' includes this header.  However, we do not want
 * to expose the `getopt_long' or `getopt_long_only' APIs, when
 * included in this manner.  Thus, close the standard _GETOPT_H_
 * declarations block, and open an additional _GETOPT_LONG_H_
 * specific block to declare the extended API.
 */
#endif /* !defined( _GETOPT_H_ ) */


#ifndef _GETOPT_LONG_H_
#define _GETOPT_LONG_H_

#ifdef __cplusplus
extern "C" {
#endif

struct option		/* specification for a long form option...	*/
{
  const char *name;		    /* option name, without leading hyphens */
  int         has_arg;		/* does it take an argument? */
  int        *flag;		    /* where to save its status, or NULL */
  int         val;		    /* its associated status value */
};

enum    		    /* permitted values for its `has_arg' field...	*/
{
  no_argument = 0,      	/* option never takes an argument	*/
  required_argument,		  /* option always requires an argument	*/
  optional_argument		    /* option may take an argument		*/
};

extern int
getopt_long(int nargc,
						char * const *nargv,
						const char *options,
						const struct option *long_options,
						int *idx);

extern int
getopt_long_only(int nargc,
								 char * const *nargv,
								 const char *options,
								 const struct option *long_options,
								 int *idx);


#ifdef __cplusplus
}
#endif

#endif /* !defined( _GETOPT_LONG_H_ ) */
