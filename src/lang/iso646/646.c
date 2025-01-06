%:include "../_lang_.h"
%:include <iso646.h>
%:include <stdio.h>

int
main (int argc, char **argv)
<%
if (argc > 1 and argv<:1:> not_eq 0)
  <%
    printf("Hello, %s\n", argv<:1:>);
  %>
  return 0;
%>
