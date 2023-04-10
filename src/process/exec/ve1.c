#include "ve1.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>


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
execle(const char *path, const char *arg0, ...)
{
  va_list       args;
  char         *s;
  int           argc      =  0;
  char const   *argv[64]  =  {0};
  char        **envp      =  0;

  argv[argc++] = arg0;

  va_start(args, arg0);
  while ((s = va_arg(args, char*)) != 0)
    {
      argv[argc++] = s;
    }
  envp = va_arg(args, char**);
  va_end(args);

  return execve(path, (char *const *) argv, envp);
}

int
execlp(const char *file, const char *arg0, ...)
{
  va_list      args;
  char        *s;
  int          argc      =  0;
  const char  *argv[64]  =  {0};

  argv[argc++] = arg0;

  va_start(args, arg0);
  while ((s = va_arg(args, char *)) != 0)
    {
      argv[argc++] = s;
    }
  va_end(args);

  return execve(0, (char *const *) file, (char *const *) argv);
}
