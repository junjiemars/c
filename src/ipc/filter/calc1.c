#include "_ipc_.h"

int
main(void)
{
  int   left, right;
  char  op;
  char  line[NM_LINE_MAX];

  setvbuf(stdin, NULL, _IOLBF, 0);
  setvbuf(stdout, NULL, _IOLBF, 0);

  while (fgets(line, NM_LINE_MAX, stdin) != NULL)
    {
      if (sscanf(line, "%d %c %d", &left, &op, &right) == 3)
        {
          int res = 0;

          switch (op)
            {
            case '+': res = left + right; break;
            case '-': res = left - right; break;
            case '*': res = left * right; break;
            case '/': res = left / right; break;
            }

          fprintf(stdout, "%d\n", res);
        }
    }

  exit(0);
}
