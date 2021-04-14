#include <_lang_.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if (DARWIN) || (LINUX)
#  include <unistd.h>
#endif  /* DARWIN || LINUX */


#define N_ENVP  2
#define N_LEN   16    


int
main(int argc, char **argv)
{
    int      rc;
    char **  envp  =  0;

    if (argc < 2) {
        printf("please, input executable path\n");
        return 1;
    }

    printf("%s ", argv[0]);
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    envp = calloc(N_ENVP, sizeof(char*));
    envp[0] = malloc(N_LEN + 1);
    strcpy(envp[0], "XXX=zzz");
    
    rc = execve((const char *) argv[1],
                (char *const *) &argv[1],
                (char *const *) envp);
    if (rc) {
        perror(0);
        return rc;
    }

    return 0;
}
