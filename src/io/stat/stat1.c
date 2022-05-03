#include "_io_.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

static void pr_stat(const char *, const struct stat *);
static const char *file_type(const struct stat *);
static const char *file_mode(const struct stat *);
static const char *str_uid(void);
static const char *str_gid(void);


static char link_or_pipe = '-';


int
main(int argc, char **argv)
{
  struct stat  buf;

  if (argc < 2)
    {
      if (fstat(STDIN_FILENO, &buf) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
      pr_stat("(stdin)", &buf);
      exit(EXIT_SUCCESS);
    }

  for (int i = 1; i < argc; i++)
    {
      if (lstat(argv[i], &buf) == -1)
        {
          perror(NULL);
          continue;
        }

      pr_stat(argv[i], &buf);
    }


  exit(EXIT_SUCCESS);
}

void
pr_stat(const char *name, const struct stat *buf)
{
  printf("  File: %s\n", name);
  printf("  Size: %-11lld  FileType: %s\n", buf->st_size, file_type(buf));
  printf("  Mode: (%s)        Uid: (%5d/%8s)  Gid: (%5d/%8s)\n",
         file_mode(buf),
         getuid(),
         str_uid(),
         getgid(),
         str_gid());
  printf("Device: %d,%d   Inode: %lld    Links: %d\n",
         major(buf->st_dev),
         minor(buf->st_dev),
         buf->st_ino,
         buf->st_nlink);
  printf("Access: %s"
         "Modify: %s"
         "Change: %s",
         ctime(&buf->st_atime),
         ctime(&buf->st_mtime),
         ctime(&buf->st_ctime));

}

const char *
file_type(const struct stat *buf)
{
  if (S_ISREG(buf->st_mode))
    {
      return "regular file";
    }
  else if (S_ISDIR(buf->st_mode))
    {
      return "directory";
    }
  else if (S_ISCHR(buf->st_mode))
    {
      return "character device";
    }
  else if (S_ISBLK(buf->st_mode))
    {
      return "block device";
    }
  else if (S_ISFIFO(buf->st_mode))
    {
      link_or_pipe = 'p';
      return "fifo file";
    }
  else if (S_ISLNK(buf->st_mode))
    {
      link_or_pipe = 'l';
      return "symbolic link";
    }
  else if (S_ISSOCK(buf->st_mode))
    {
      return "socket";
    }
  else
    {
      return "(unknown)";
    }

}

const char *
file_mode(const struct stat *buf)
{
  static char  ss[64];
  mode_t       m  =  buf->st_mode & (~S_IFMT);

  sprintf(ss, "%04o/%c%c%c%c%c%c%c%c%c%c", m,
          link_or_pipe,
          (m & S_IRUSR) ? 'r' : '-',
          (m & S_IWUSR) ? 'w' : '-',
          (m & S_ISUID) ? 's' : (m & S_IXUSR) ? 'x' : '-',
          (m & S_IRGRP) ? 'r' : '-',
          (m & S_IWGRP) ? 'w' : '-',
          (m & S_ISGID) ? : (m & S_IXGRP) ? 'x' : '-',
          (m & S_IROTH) ? 'r' : '-',
          (m & S_IWOTH) ? 'w' : '-',
          (m & S_IXOTH) ? 'x' : '-'
          );
  return ss;
}


const char *
str_uid(void)
{
  struct passwd  *p;
  static char     ss[64];

  if ((p = getpwuid(getuid())) != NULL)
    {
      return strcpy(ss, p->pw_name);
    }

  return NULL;
}

const char *
str_gid(void)
{
  struct group  *p;
  static char    ss[64];

  if ((p = getgrgid(getgid())) != NULL)
    {
      return strcpy(ss, p->gr_name);
    }

  return NULL;
}
