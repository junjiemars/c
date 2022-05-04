#include "_io_.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

#if (LINUX)
#  include <sys/sysmacros.h>
#endif

static void pr_stat(const char *, const struct stat *);
static const char *file_type(const struct stat *);
static const char *file_mode(const struct stat *);
static const char *str_uid(void);
static const char *str_gid(void);


static char filetype_c = '-';


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
  printf("  Size: %-11lld  FileType: %s\n",
         (long long int) buf->st_size,
         file_type(buf));
  printf("  Mode: (%s)        Uid: (%5d/%8s)  Gid: (%5d/%8s)\n",
         file_mode(buf),
         getuid(),
         str_uid(),
         getgid(),
         str_gid());
  printf("Device: %d,%d   Inode: %llu    Links: %d\n",
         major(buf->st_dev),
         minor(buf->st_dev),
         (unsigned long long) buf->st_ino,
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
      filetype_c = '-';
      return "regular file";
    }
  else if (S_ISDIR(buf->st_mode))
    {
      filetype_c = 'd';
      return "directory";
    }
  else if (S_ISCHR(buf->st_mode))
    {
      filetype_c = 'c';
      return "character device";
    }
  else if (S_ISBLK(buf->st_mode))
    {
      filetype_c = 'b';
      return "block device";
    }
  else if (S_ISFIFO(buf->st_mode))
    {
      filetype_c = 'p';
      return "fifo file";
    }
  else if (S_ISLNK(buf->st_mode))
    {
      filetype_c = 'l';
      return "symbolic link";
    }
  else if (S_ISSOCK(buf->st_mode))
    {
      filetype_c = 's';
      return "socket";
    }
  else
    {
      filetype_c = '?';
      return "(unknown)";
    }

}

const char *
file_mode(const struct stat *buf)
{
  static char  ss[64];
  mode_t       m  =  buf->st_mode & (~S_IFMT);

  snprintf(ss, sizeof(ss), "%04o/%c%c%c%c%c%c%c%c%c%c", m,
           filetype_c,
           (m & S_IRUSR) ? 'r' : '-',
           (m & S_IWUSR) ? 'w' : '-',
           (m & S_ISUID) ? 's' : (m & S_IXUSR) ? 'x' : '-',
           (m & S_IRGRP) ? 'r' : '-',
           (m & S_IWGRP) ? 'w' : '-',
           (m & S_ISGID) ? : (m & S_IXGRP) ? 'x' : '-',
           (m & S_IROTH) ? 'r' : '-',
           (m & S_IWOTH) ? 'w' : '-',
           (m & S_IXOTH) ? 'x' : '-');
  return ss;
}


const char *
str_uid(void)
{
  struct passwd  *p;
  static char     ss[64];

  if ((p = getpwuid(getuid())) != NULL)
    {
      return strncpy(ss, p->pw_name, sizeof(ss)-1);
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
      return strncpy(ss, p->gr_name, sizeof(ss)-1);
    }

  return NULL;
}
