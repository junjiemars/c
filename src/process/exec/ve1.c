#include "ve1.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Emulate `execl' function;
 *
 */


extern char  **environ;


int
execl(const char *path, const char *arg0, ...)
{
  va_list      args;
  char        *s;
  int          argc      =  0;
  const char  *argv[64]  =  {0};

  argv[argc++] = arg0;

  va_start(args, arg0);
  while ((s = va_arg(args, char*)) != 0)
    {
      argv[argc++] = s;
    }
  va_end(args);

  return execve(path, (char *const *) argv, environ);
}

int
execle(const char *file, const char *arg0, ...)
{
  va_list       args;
  char         *s;
  int           argc      =  0;
  const char   *argv[64]  =  {0};
  char        **envp      =  0;

  argv[argc++] = arg0;

  va_start(args, arg0);
  while ((s = va_arg(args, char *const)) != 0)
    {
      argv[argc++] = s;
    }
  envp = va_arg(args, char **);
  va_end(args);

	int rc = execve(file, (char *const *) argv, envp);
	if (rc < 0)
		{
			perror(0);
		}
	return rc;
}

int
execlp(const char *file, const char *arg0, ...)
{
  va_list				 args;
  char					*s;
  int						 argc				=  0;
  const char		*argv[64]		=  {0};
	char					 path[255]	=	 {0};

  argv[argc++] = arg0;

  va_start(args, arg0);
  while ((s = va_arg(args, char *)) != 0)
    {
      argv[argc++] = s;
    }
  va_end(args);

	sprintf(path, "%s/%s", getenv("PATH"), file);

  int rc = execve(path, (char *const *) argv, 0);
	if (rc < 0)
		{
			perror(0);
		}
	return rc;
}
