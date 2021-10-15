#include "_db_.h"
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


#define count_of(s)  sizeof(s)/sizeof(*s)

static void
usage(const char *bin)
{
  printf("Usage: %s [OPTION]...", bin);
  printf("\n");
  printf("Play with MySQL, %s\n", mysql_get_client_info());
  printf("  -h, --help             print this message\n");
  printf("  -H, --host             connect to host\n");
  printf("  -P, --port             port number of the host\n");
  printf("  -u, --user             user for login\n");
  printf("  -p, --password         password for login\n");
  printf("  -t, --sqltext          sql text to execute\n");
}

static struct option long_options[] =
  {
    {"help",      no_argument,          0, 'h'},
    {"host",      required_argument,    0, 'H'},
    {"port",      optional_argument ,   0, 'P'},
    {"user",      required_argument,    0, 'u'},
    {"password",  optional_argument,    0, 'p'},
    {"sqltext",   optional_argument,    0, 't'},
    {0,         0,                    0,  0 },
  };


static char  opt_host[64];
static int   opt_port = 3306;
static char  opt_user[64];
static char  opt_password[64];
static char  opt_sqltext[1024];


int
main(int argc, char **argv)
{
  int     ch;
  MYSQL  *mysql;

  while (-1 != (ch = getopt_long(argc, argv, "hH:P:u:p:t:", long_options, 0)))
    {
      switch (ch)
        {
        case 'h':
          usage(argv[0]);
          return 0;
        case 'H':
          strncpy(opt_host, optarg, count_of(opt_host));
          break;
        case 'P':
          opt_port = (uint16_t)atoi(optarg);
          break;
        case 'u':
          strncpy(opt_user, optarg, count_of(opt_user));
          break;
        case 'p':
          strncpy(opt_password, optarg, count_of(opt_password));
          break;
        case 't':
          strncpy(opt_sqltext, optarg, count_of(opt_sqltext));
          break;
        default:
          usage(argv[0]);
          return -1;
        }
    }

  mysql = mysql_init(NULL);

  if(NULL == mysql_real_connect(mysql,
                        opt_host,
                        opt_user,
                        opt_password,
                        opt_sqltext,
                        3306,
                        NULL,
                        0))
    {
      fprintf(stderr, "%s\n", mysql_error(mysql));
      goto clean_exit;
    }
  fprintf(stderr, "connected.\n");

 clean_exit:
  mysql_close(mysql);

  return 0;
}
