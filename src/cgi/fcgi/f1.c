#include "_cgi_.h"
#include <fcgiapp.h>

int
main (void)
{
  int socket_fd;
  FCGX_Request request;

  FCGX_Init ();

  socket_fd = FCGX_OpenSocket (":9000", 10);

  FCGX_InitRequest (&request, socket_fd, 0);

  while (FCGX_Accept_r (&request) == 0)
    {
      FCGX_FPrintF (request.out, "Content-Type: text/html\r\n\r\n");

      FCGX_FPrintF (request.out, "<html><body><h1>fast?</h1></body></html>");

      FCGX_FFlush (request.out);

      FCGX_Finish_r (&request);
    }

  FCGX_Free (&request, 1);

  return 0;
}
