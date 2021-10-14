#include "_db_.h"
#include <mysql.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);
 
  printf("mysqlclient info: %s\n", mysql_get_client_info());
  
  return 0;
}
