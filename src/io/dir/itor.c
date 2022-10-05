#include <_io_.h>
#include <dirent.h>


/*
 * Count the file types in the directory.
 *
 */


typedef int (*counter)(const struct stat*);


static long  n_reg, n_blk, n_chr, n_fifo, n_lnk, n_sock;
static long  n_dir, n_nr, n_ns, n_unk;

static void  iter(int, const char*, counter);
static int   count(const struct stat*);



int
main(int argc, char **argv)
{
  int  n, fd;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <dir>\n");
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  n_reg = n_blk = n_chr = n_fifo = n_lnk = n_sock = n_dir = n_nr = n_ns = n_unk = 0;

  iter(fd, argv[1], count);

  n = n_reg + n_blk + n_chr + n_fifo + n_lnk + n_sock + n_dir + n_nr + n_ns + n_unk;
  if (n == 0)
    {
      n = 1;
    }
  printf("directories              = %7ld, %6.2f%%\n", n_dir, n_dir * 100.0 /n);
  printf("regular files            = %7ld, %6.2f%%\n", n_reg, n_reg * 100.0 /n);
  printf("block files              = %7ld, %6.2f%%\n", n_blk, n_blk * 100.0 /n);
  printf("character files          = %7ld, %6.2f%%\n", n_chr, n_chr * 100.0 /n);
  printf("fifo files               = %7ld, %6.2f%%\n", n_fifo, n_fifo * 100.0 /n);
  printf("link files               = %7ld, %6.2f%%\n", n_lnk, n_lnk * 100.0 /n);
  printf("socket files             = %7ld, %6.2f%%\n", n_sock, n_sock * 100.0 /n);
  printf("unkown files             = %7ld, %6.2f%%\n", n_unk,  n_unk * 100.0 /n);
  printf("cann't stat paths        = %7ld, %6.2f%%\n", n_ns,  n_ns * 100.0 /n);
  printf("cann't read directories  = %7ld, %6.2f%%\n", n_nr,  n_nr * 100.0 /n);


  exit(EXIT_SUCCESS);
}

void
iter(int fd, const char *path, counter cnt)
{
  DIR            *dir;
  struct stat     ss;
  struct dirent  *ent;

  if (fstatat(fd, path, &ss, AT_SYMLINK_NOFOLLOW) == -1)
    {
      n_ns++;
      return;
    }

  if (0 == cnt(&ss))
    {
      return;
    }

  fd = openat(fd, path, O_RDONLY);
  if (fd == -1)
    {
      return;
    }

  dir = fdopendir(fd);
  if (dir == NULL)
    {
      n_nr++;
      return;
    }

  while ((ent = readdir(dir)) != NULL)
    {
      if ((ent->d_namlen == 1 && strcmp(".", ent->d_name) == 0)
          || (ent->d_namlen == 2 && strcmp("..", ent->d_name) == 0))
        {
          continue;
        }

      iter(fd, ent->d_name, cnt);
    }

  closedir(dir);

}


int
count(const struct stat *ss)
{
  switch (ss->st_mode & S_IFMT)
    {
    case S_IFREG:  n_reg++;  return 0;
    case S_IFBLK:  n_blk++;  return 0;
    case S_IFCHR:  n_chr++;  return 0;
    case S_IFIFO:  n_fifo++; return 0;
    case S_IFLNK:  n_lnk++;  return 0;
    case S_IFSOCK: n_sock++; return 0;
    case S_IFDIR:  n_dir++;  return 1;
    default:       n_unk++;  return 0;
    }
}
