#include "_unix_.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>


#define M_KEY 0x1234
#define M_TYPE 1
#define M_SIZE sizeof(long) * 1

typedef struct s_msgbuf {
  long mtype;
  char mtext[M_SIZE];
} msgbuf_t;


static void
usage(char *prog_name, char *errmsg)
{
  if (errmsg != NULL)
    {
      fputs(errmsg, stderr);
    }

  fprintf(stderr, "Usage: %s [options]\n", prog_name);
  fprintf(stderr, "Options are:\n");
  fprintf(stderr, "-s        send message using msgsnd()\n");
  fprintf(stderr, "-r        read message using msgrcv()\n");
  fprintf(stderr, "-t        message type (default is %i)\n", M_TYPE);
  fprintf(stderr, "-k        message queue key (default is 0x%08x)\n", M_KEY);
  exit(EXIT_FAILURE);
}

static void
send_msg(int qid, int mtype, const char *mtext)
{
  msgbuf_t msg;
  if (snprintf(&msg.mtext[0], sizeof(msg.mtext), "%s", mtext) < 0)
    {
      perror(NULL);
      return;
    }
  msg.mtype = mtype;

  if (msgsnd(qid, &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1)
    {
      perror("msgsnd error");
      exit(EXIT_FAILURE);
    }
  printf("sent: %s\n", msg.mtext);
}

static void
get_msg(int qid, int mtype)
{
  msgbuf_t msg;

  if (msgrcv(qid, &msg, sizeof(msg.mtext), mtype,
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
  int qid, opt;
  int mode = 0;               /* 's' = send, 'r' = receive */
  int msgkey = M_KEY;
  int mtype = M_TYPE;
  char mtext[M_SIZE];

  while ((opt = getopt(argc, argv, "hsrt:k:")) != -1)
    {
      switch (opt)
        {
        case 'h':
          usage(argv[0], NULL);
          break;
        case 's':
          mode = 's';
          break;
        case 'r':
          mode = 'r';
          break;
        case 't':
          mtype = atoi(optarg);
          if (mtype <= 0)
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

  if (optind < argc)
    {
      int n = 0;
      for (int i = optind; i < argc; i++)
        {
          n = snprintf((char*)&mtext[0] + n, M_SIZE - n, "%s", argv[i]);
        }
    }

  qid = msgget(msgkey, IPC_CREAT | 0666);
  if (qid == -1)
    {
      perror("msgget");
      exit(EXIT_FAILURE);
    }

  if (mode == 'r')
    {
      get_msg(qid, mtype);
    }
  else
    {
      send_msg(qid, mtype, mtext);
    }

  exit(EXIT_SUCCESS);
}
