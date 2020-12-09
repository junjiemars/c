#include <_os_.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <getopt.h>

struct msgbuf {
  long mtype;
  char mtext[80];
};

static void
usage(char *prog_name, char *msg)
{
  if (msg != NULL)
    {
      fputs(msg, stderr);
    }

  fprintf(stderr, "Usage: %s [options]\n", prog_name);
  fprintf(stderr, "Options are:\n");
  fprintf(stderr, "-s        send message using msgsnd()\n");
  fprintf(stderr, "-r        read message using msgrcv()\n");
  fprintf(stderr, "-t        message type (default is 's')\n");
  fprintf(stderr, "-k        message queue key (default is 1234)\n");
  exit(EXIT_FAILURE);
}

static void
send_msg(int qid, int msgtype)
{
  struct msgbuf msg;
  time_t t;

  msg.mtype = msgtype;

  time(&t);
  snprintf(msg.mtext, sizeof(msg.mtext), "a message at %s", ctime(&t));

  if (msgsnd(qid, (void *) &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1)
    {
      perror("msgsnd error");
      exit(EXIT_FAILURE);
    }
  printf("sent: %s\n", msg.mtext);
}

static void
get_msg(int qid, int msgtype)
{
  struct msgbuf msg;

  if (msgrcv(qid, &msg, sizeof(msg.mtext), msgtype,
             MSG_NOERROR | IPC_NOWAIT) == -1)
    {
      if (errno != ENOMSG)
        {
          perror("msgrcv");
          exit(EXIT_FAILURE);
        }
      printf("No message available for msgrcv()\n");
    } else
    printf("received: %s\n", msg.mtext);
}

int
main(int argc, char *argv[])
{
  _unused_(argc);
  _unused_(argv);

  int qid, opt;
  int mode = 0;               /* 's' = send, 'r' = receive */
  int msgtype = 1;
  int msgkey = 1234;

  while ((opt = getopt(argc, argv, "srt:k:")) != -1)
    {
      switch (opt)
        {
        case 's':
          mode = 's';
          break;
        case 'r':
          mode = 'r';
          break;
        case 't':
          msgtype = atoi(optarg);
          if (msgtype <= 0)
            {
              usage(argv[0], "-t option must be greater than 0\n");
            }
          break;
        case 'k':
          msgkey = atoi(optarg);
          break;
        default:
          usage(argv[0], "Unrecognized option\n");
        }
    }

  if (mode == 0)
    {
      usage(argv[0], "must use either -s or -r option\n");
    }

  qid = msgget(msgkey, IPC_CREAT | 0666);
  if (qid == -1)
    {
      perror("msgget");
      exit(EXIT_FAILURE);
    }

  if (mode == 'r')
    {
      get_msg(qid, msgtype);
    }
  else
    {
      send_msg(qid, msgtype);
    }

  exit(EXIT_SUCCESS);
}

