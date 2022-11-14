#include "_io_.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

/*
 * Emulates `stat(1)'.
 *
*/


#if (LINUX)
#  include <sys/sysmacros.h>
#endif


static void         pr_stat(const char *, const struct stat *);
static const char  *file_type(mode_t);
static const char  *file_mode(mode_t);
static const char  *str_uid(uid_t);
static const char  *str_gid(gid_t);


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
pr_stat(const char *name, const struct stat *ss)
{
  printf("  File: %s\n", name);

  printf("  Size: %-11lld  FileType: %s\n",
         (long long int) ss->st_size,
         file_type(ss->st_mode));

  printf("  Mode: (%s)        Uid: (%5d/%8s)  Gid: (%5d/%8s)\n",
         file_mode(ss->st_mode),
         ss->st_uid,
         str_uid(ss->st_uid),
         ss->st_gid,
         str_gid(ss->st_gid));

  printf("Device: %d,%d   Inode: %llu    Links: %lu\n",
         major(ss->st_dev),
         minor(ss->st_dev),
         (unsigned long long) ss->st_ino,
         (unsigned long) ss->st_nlink);

  printf("Access: %s"
         "Modify: %s"
         "Change: %s",
         ctime(&ss->st_atime),
         ctime(&ss->st_mtime),
         ctime(&ss->st_ctime));

}

const char *
file_type(mode_t m)
{
  if (S_ISREG(m))
    {
      filetype_c = '-';
      return "regular file";
    }
  else if (S_ISDIR(m))
    {
      filetype_c = 'd';
      return "directory";
    }
  else if (S_ISCHR(m))
    {
      filetype_c = 'c';
      return "character device";
    }
  else if (S_ISBLK(m))
    {
      filetype_c = 'b';
      return "block device";
    }
  else if (S_ISFIFO(m))
    {
      filetype_c = 'p';
      return "fifo file";
    }
  else if (S_ISLNK(m))
    {
      filetype_c = 'l';
      return "symbolic link";
    }
  else if (S_ISSOCK(m))
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
file_mode(mode_t mode)
{
  static char  ss[64];
  mode_t       m  =  mode & (~S_IFMT);

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
str_uid(uid_t uid)
{
  struct passwd  *p;
  static char     ss[64];

  if ((p = getpwuid(uid)) != NULL)
    {
      return strncpy(ss, p->pw_name, sizeof(ss)-1);
    }

  return NULL;
}

const char *
str_gid(gid_t gid)
{
  struct group  *p;
  static char    ss[64];

  if ((p = getgrgid(gid)) != NULL)
    {
      return strncpy(ss, p->gr_name, sizeof(ss)-1);
    }

  return NULL;
}
