#include "_process_.h"

/*
 * How the pathname, filename and environment passed to `execve'?
 *
 */

int
main (int argc, char **argv)
{
  pid_t pid;
  char **args = 0;
  char **env = 0;

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      int env_n = 0;
      extern char **environ;

      /* duplicate environ */
      for (char **p = environ; *p != 0; p++)
        {
          env_n++;
        }
      env = (char **)malloc (sizeof (char *) * (env_n + 1));
      for (int i = 0; i < env_n; i++)
        {
          env[i] = strdup (environ[i]);
        }
      env[env_n] = 0;

      /* duplicate argv */
      args = (char **)malloc (sizeof (char *) * (argc + 1));
      args[0] = strdup (_FILE_NAME_);
      for (int i = 1; i < argc; i++)
        {
          args[i] = strdup (argv[i]);
        }
      args[argc] = 0;

      if ((execve (_PATH_NAME_, args, env)) == -1)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
      /* never return */
      exit (EXIT_SUCCESS);
    }

  if ((waitpid (pid, NULL, 0)) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}
