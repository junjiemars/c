#include "_db_.h"
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


static void  usage(const char *);
static void  query(MYSQL *);


static struct option long_options[] =
  {
    {"help",      no_argument,          0, 'h'},
    {"host",      required_argument,    0, 'H'},
    {"port",      optional_argument ,   0, 'P'},
    {"user",      required_argument,    0, 'u'},
    {"password",  optional_argument,    0, 'p'},
    {"database",  required_argument,    0, 'D'},
    {"sqltext",   optional_argument,    0, 't'},
    {"quiet",     no_argument,          0, 'q'},
    {0,           0,                    0,  0 },
  };


static char  opt_host[64];
static int   opt_port   =  3306;
static char  opt_user[64];
static char  opt_password[64];
static char  opt_database[64];
static char  opt_sqltext[1024];
static int   opt_quiet  =  0;


int
main(int argc, char **argv)
{
  int     ch;
  MYSQL  *mysql;

  while (-1 != (ch = getopt_long(argc, argv, "hH:P:u:p:D:t:q", long_options, 0)))
    {
      switch (ch)
        {
        case 'h':
          usage(argv[0]);
          return 0;
        case 'H':
          strncpy(opt_host, optarg, _nof_(opt_host));
          break;
        case 'P':
          opt_port = (uint16_t)atoi(optarg);
          break;
        case 'u':
          strncpy(opt_user, optarg, _nof_(opt_user));
          break;
        case 'p':
          strncpy(opt_password, optarg, _nof_(opt_password));
          break;
        case 'D':
          strncpy(opt_database, optarg, _nof_(opt_database));
          break;
        case 't':
          strncpy(opt_sqltext, optarg, _nof_(opt_sqltext));
          break;
        case 'q':
          opt_quiet = 1;
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
                                opt_database,
                                opt_port,
                                NULL,
                                0))
    {
      fprintf(stderr, "%s\n", mysql_error(mysql));
      goto clean_exit;
    }

  query(mysql);

 clean_exit:
  mysql_close(mysql);

  return 0;
}


void
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


void
query(MYSQL *mysql)
{
  int         rc;
  MYSQL_RES  *res  =  NULL;

  rc = mysql_real_query(mysql, opt_sqltext, _nof_(opt_sqltext));
  if (rc != 0)
    {
      fprintf(stderr, "!panic: %s\n", mysql_error(mysql));
      return;
    }

  res = mysql_store_result(mysql);
  if (res == NULL)
    {
      if (mysql_field_count(mysql) != 0)
        {
          fprintf(stderr, "!panic: %s\n", mysql_error(mysql));
          return;
        }

      uint64_t    n_rows;
      n_rows = mysql_affected_rows(mysql);
      fprintf(stdout, PRIu64 "\n", n_rows);
      return;
    }

  MYSQL_ROW      row;
  MYSQL_FIELD   *fields;
  unsigned int   n_field;

  n_field = mysql_num_fields(res);
  fields = mysql_fetch_field(res);

  while ((row = mysql_fetch_row(res)) != NULL)
    {
      for (unsigned int i = 0; i < n_field; i++)
        {
          printf("%s: %.*s\n", fields[i].name, (int) fields[i].length,
                 row[i] == NULL ? NULL : row[i]);
        }
      printf("------------\n");
    }

  if (!mysql_eof(res))
    {
      fprintf(stderr, "!panic: %s\n", mysql_error(mysql));
      goto clean_exit;
    }

 clean_exit:
  mysql_free_result(res);

}
