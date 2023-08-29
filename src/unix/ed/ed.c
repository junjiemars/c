/*
 * ed - text editor
 *
 * references:
 * 1. https://man.cat-v.org/unix-6th/1/ed
 * 2. https://man.cat-v.org/unix-6th/2/signal
 * 3. https://man.cat-v.org/unix-6th/3/setexit
 * 4. https://man.cat-v.org/unix-6th/3/reset
 * 5. https://man.cat-v.org/unix-6th/3/ldiv
 *
 */


#include "_unix_.h"
#include <signal.h>
#include <fcntl.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <stdlib.h>

int *address(void);
int advance(char*, char*);
int append(int (*f)(void), int*);
void blkio(int, char*, ssize_t (*)());
int cclass(char*, int, int);
void commands(void);
void compile(int);
int compsub(void);
void delete(void);
void dosub(void);
void filename(void);
void exfile(void);
int execute(int, int*);
char* getblock(int, int);
int getchar(void);
int getcopy(void);
int getfile(void);
char* getline(int);
int gettty(void);
void global(int);
void init(void);
void move(int);
void newline(void);
void nonzero(void);
char* place(char*, char*, char*);
static void putchar(int);
void putfile(void);
void putd(void);
int putline(void);
void puts(char*);
void reverse(int*, int*);
void setall(void);
void setdot(void);
void setnoaddr(void);
void substitute(char*);
void unix(void);

#define seek  lseek

/* #define   SIGHUP   1 */
/* #define   SIGINTR  2 */
/* #define   SIGQUIT  3 */
#define   FNSIZE   64
#define   LBSIZE   512
#define   ESIZE    128
#define   GBSIZE   256
#define   NBRA     5
#define   EOF      -1

#define   CBRA  1
#define   CCHR  2
#define   CDOT  4
#define   CCL   6
#define   NCCL  8
#define   CDOL  10
#define   CEOF  11
#define   CKET  12

#define   STAR  01

#define   error   errfunc() /* goto errlab */
#define   READ   0
#define   WRITE  1

int   peekc;
int   lastc;
char  savedfile[FNSIZE];
char  file[FNSIZE];
char  linebuf[LBSIZE];
char  rhsbuf[LBSIZE/2];
char  expbuf[ESIZE+4];
int   circfl;
int   *zero;
int   *dot;
int   *dol;
int   *endcore;
int   *fendcore;
int   *addr1;
int   *addr2;
char  genbuf[LBSIZE];
int   count[2];
char  *nextip;
char  *linebp;
int   ninbuf;
int   io;
int   pflag;
sig_t onhup; /* int   onhup; */
sig_t onquit; /* int   onquit; */
int   vflag   = 1;
int   listf;
int   col;
char  *globp;
int   tfile =   -1;
int   tline;
char  tfname[12];
char  *loc1;
char  *loc2;
char  *locs;
char  ibuff[512];
int   iblock = -1;
char  obuff[512];
int   oblock = -1;
int   ichanged;
int   nleft;
int   errfunc(void);
/* int   *errlab   errfunc; */
char  TMPERR[] = "TMP";
int   names[26];
char  *braslist[NBRA];
char  *braelist[NBRA];


static jmp_buf jmpbuf_main;
#define setexit() setjmp(jmpbuf_main)
#define reset() longjmp(jmpbuf_main, 0)

int
main(int argc, char **argv)
{
  register char *p1, *p2;
  extern void onintr(int);

  onquit = signal(SIGQUIT, SIG_IGN);
  onhup = signal(SIGHUP, SIG_IGN);
  argv++;
  if (argc > 1 && **argv=='-') {
    vflag = 0;
    /* allow debugging quits? */
    if ((*argv)[1]=='q') {
      signal(SIGQUIT, 0);
      vflag++;
    }
    argv++;
    argc--;
  }
  if (argc>1) {
    p1 = *argv;
    p2 = savedfile;
    while ((*p2++ = *p1++));
    globp = "r";
  }
  fendcore = sbrk(0);
  init();
  if ((signal(SIGINT, SIG_IGN) != SIG_IGN))
    signal(SIGINT, onintr);
  setexit();
  commands();
  unlink(tfname);
}

void
commands(void)
{
  int getfile(), gettty();
  register int *a1, c;
  __attribute__ ((unused)) register char *p;
  __attribute__ ((unused)) int r;

  for (;;) {
  if (pflag) {
    pflag = 0;
    addr1 = addr2 = dot;
    goto print;
  }
  addr1 = 0;
  addr2 = 0;
  do {
    addr1 = addr2;
    if ((a1 = address())==0) {
      c = getchar();
      break;
    }
    addr2 = a1;
    if ((c = getchar()) == ';') {
      c = ',';
      dot = a1;
    }
  } while (c==',');
  if (addr1==0)
    addr1 = addr2;
  switch(c) {

  case 'a':
    setdot();
    newline();
    append(gettty, addr2);
    continue;

  case 'c':
    delete();
    append(gettty, addr1-1);
    continue;

  case 'd':
    delete();
    continue;

  case 'e':
    setnoaddr();
    if ((peekc = getchar()) != ' ')
      error;
    savedfile[0] = 0;
    init();
    addr2 = zero;
    goto caseread;

  case 'f':
    setnoaddr();
    if ((c = getchar()) != '\n') {
      peekc = c;
      savedfile[0] = 0;
      filename();
    }
    puts(savedfile);
    continue;

  case 'g':
    global(1);
    continue;

  case 'i':
    setdot();
    nonzero();
    newline();
    append(gettty, addr2-1);
    continue;

  case 'k':
    if ((c = getchar()) < 'a' || c > 'z')
      error;
    newline();
    setdot();
    nonzero();
    names[c-'a'] = *addr2 | 01;
    continue;

  case 'm':
    move(0);
    continue;

  case '\n':
    if (addr2==0)
      addr2 = dot+1;
    addr1 = addr2;
    goto print;

  case 'l':
    listf++;
    __attribute__ ((fallthrough));
  case 'p':
    newline();
  print:
    setdot();
    nonzero();
    a1 = addr1;
    do
      puts(getline(*a1++));
    while (a1 <= addr2);
    dot = addr2;
    listf = 0;
    continue;

  case 'q':
    setnoaddr();
    newline();
    unlink(tfname);
    exit(0);

  case 'r':
  caseread:
    filename();
    if ((io = open(file, 0)) < 0) {
      lastc = '\n';
      error;
    }
    setall();
    ninbuf = 0;
    append(getfile, addr2);
    exfile();
    continue;

  case 's':
    setdot();
    nonzero();
    substitute(globp);
    continue;

  case 't':
    move(1);
    continue;

  case 'v':
    global(0);
    continue;

  case 'w':
    setall();
    nonzero();
    filename();
    if ((io = creat(file, 0666)) < 0)
      error;
    putfile();
    exfile();
    continue;

  case '=':
    setall();
    newline();
    count[1] = (addr2-zero)&077777;
    putd();
    putchar('\n');
    continue;

  case '!':
    unix();
    continue;

  case EOF:
    return;

  }
  error;
  }
}

int*
address(void)
{
  register int *a1, minus, c;
  int n, relerr;

  minus = 0;
  a1 = 0;
  for (;;) {
    c = getchar();
    if ('0'<=c && c<='9') {
      n = 0;
      do {
        n *= 10;
        n += c - '0';
      } while ((c = getchar())>='0' && c<='9');
      peekc = c;
      if (a1==0)
        a1 = zero;
      if (minus<0)
        n = -n;
      a1 += n;
      minus = 0;
      continue;
    }
    relerr = 0;
    if (a1 || minus)
      relerr++;
    switch(c) {
    case ' ':
    case '\t':
      continue;

    case '+':
      minus++;
      if (a1==0)
        a1 = dot;
      continue;

    case '-':
    case '^':
      minus--;
      if (a1==0)
        a1 = dot;
      continue;

    case '?':
    case '/':
      compile(c);
      a1 = dot;
      for (;;) {
        if (c=='/') {
          a1++;
          if (a1 > dol)
            a1 = zero;
        } else {
          a1--;
          if (a1 < zero)
            a1 = dol;
        }
        if (execute(0, a1))
          break;
        if (a1==dot)
          error;
      }
      break;

    case '$':
      a1 = dol;
      break;

    case '.':
      a1 = dot;
      break;

    case '\'':
      if ((c = getchar()) < 'a' || c > 'z')
        error;
      for (a1=zero; a1<=dol; a1++)
        if (names[c-'a'] == (*a1|01))
          break;
      break;

    default:
      peekc = c;
      if (a1==0)
        return(0);
      a1 += minus;
      if (a1<zero || a1>dol)
        error;
      return(a1);
    }
    if (relerr)
      error;
  }
}

void
setdot(void)
{
  if (addr2 == 0)
    addr1 = addr2 = dot;
  if (addr1 > addr2)
    error;
}

void
setall(void)
{
  if (addr2==0) {
    addr1 = zero+1;
    addr2 = dol;
    if (dol==zero)
      addr1 = zero;
  }
  setdot();
}

void
setnoaddr(void)
{
  if (addr2)
    error;
}

void
nonzero(void)
{
  if (addr1<=zero || addr2>dol)
    error;
}

void
newline(void)
{
  register int c;

  if ((c = getchar()) == '\n')
    return;
  if (c=='p' || c=='l') {
    pflag++;
    if (c=='l')
      listf++;
    if (getchar() == '\n')
      return;
  }
  error;
}

void
filename(void)
{
  register char *p1, *p2;
  register int c;

  count[1] = 0;
  c = getchar();
  if (c=='\n' || c==EOF) {
    p1 = savedfile;
    if (*p1==0)
      error;
    p2 = file;
    while ((*p2++ = *p1++));
    return;
  }
  if (c!=' ')
    error;
  while ((c = getchar()) == ' ');
  if (c=='\n')
    error;
  p1 = file;
  do {
    *p1++ = c;
  } while ((c = getchar()) != '\n');
  *p1++ = 0;
  if (savedfile[0]==0) {
    p1 = savedfile;
    p2 = file;
    while ((*p1++ = *p2++));
  }
}

void
exfile(void)
{
  close(io);
  io = -1;
  if (vflag) {
    putd();
    putchar('\n');
  }
}

void
onintr(__attribute__ ((unused)) int _sigintr)
{
  signal(SIGINT, onintr);
  putchar('\n');
  lastc = '\n';
  error;
}

int
errfunc(void)
{
  register int c;

  listf = 0;
  puts("?");
  count[0] = 0;
  seek(0, 0, 2);
  pflag = 0;
  if (globp)
    lastc = '\n';
  globp = 0;
  peekc = lastc;
  while ((c = getchar()) != '\n' && c != EOF);
  if (io > 0) {
    close(io);
    io = -1;
  }
  reset();
}

int
getchar(void)
{
  if ((lastc=peekc)) {
    peekc = 0;
    return(lastc);
  }
  if (globp) {
    if ((lastc = *globp++) != 0)
      return(lastc);
    globp = 0;
    return(EOF);
  }
  if (read(0, &lastc, 1) <= 0)
    return(lastc = EOF);
  lastc &= 0177;
  return(lastc);
}

int
gettty(void)
{
  register int c;
  register char *p, *gf;

  p = linebuf;
  gf = globp;
  while ((c = getchar()) != '\n') {
    if (c==EOF) {
      if (gf)
        peekc = c;
      return(c);
    }
    if ((c &= 0177) == 0)
      continue;
    *p++ = c;
    if (p >= &linebuf[LBSIZE-2])
      error;
  }
  *p++ = 0;
  if (linebuf[0]=='.' && linebuf[1]==0)
    return(EOF);
  return(0);
}

int
getfile(void)
{
  register int c;
  register char *lp, *fp;

  lp = linebuf;
  fp = nextip;
  do {
    if (--ninbuf < 0) {
      if ((ninbuf = read(io, genbuf, LBSIZE)-1) < 0)
        return(EOF);
      fp = genbuf;
    }
    if (lp >= &linebuf[LBSIZE])
      error;
    if ((*lp++ = c = *fp++ & 0177) == 0) {
      lp--;
      continue;
    }
    if (++count[1] == 0)
      ++count[0];
  } while (c != '\n');
  *--lp = 0;
  nextip = fp;
  return(0);
}

void
putfile(void)
{
  int *a1;
  register char *fp, *lp;
  register int nib;

  nib = 512;
  fp = genbuf;
  a1 = addr1;
  do {
    lp = getline(*a1++);
    for (;;) {
      if (--nib < 0) {
        write(io, genbuf, fp-genbuf);
        nib = 511;
        fp = genbuf;
      }
      if (++count[1] == 0)
        ++count[0];
      if ((*fp++ = *lp++) == 0) {
        fp[-1] = '\n';
        break;
      }
    }
  } while (a1 <= addr2);
  write(io, genbuf, fp-genbuf);
}

int
append(int (*f)(void), int *a)
{
  register int *a1, *a2, *rdot;
  int nline, tl;
  struct { int integer; } endcore;

  nline = 0;
  dot = a;
  while ((*f)() == 0) {
    if (dol - (int*)&endcore) {
      if (sbrk(1024) == (void*)-1)
        error;
      endcore.integer += 1024;
    }
    tl = putline();
    nline++;
    a1 = ++dol;
    a2 = a1+1;
    rdot = ++dot;
    while (a1 > rdot)
      *--a2 = *--a1;
    *rdot = tl;
  }
  return(nline);
}

void
unix(void)
{
  register sig_t savint;
  register int pid, rpid;
  int retcode;

  setnoaddr();
  if ((pid = fork()) == 0) {
    signal(SIGHUP, onhup);
    signal(SIGQUIT, onquit);
    execl("/bin/sh", "sh", "-t", 0);
    exit(0);
  }
  savint = signal(SIGINT, SIG_IGN);
  while ((rpid = wait(&retcode)) != pid && rpid != -1);
  signal(SIGINT, savint);
  puts("!");
}

void
delete(void)
{
  register int *a1, *a2, *a3;

  setdot();
  newline();
  nonzero();
  a1 = addr1;
  a2 = addr2+1;
  a3 = dol;
  dol -= a2 - a1;
  do
    *a1++ = *a2++;
  while (a2 <= a3);
  a1 = addr1;
  if (a1 > dol)
    a1 = dol;
  dot = a1;
}

char*
getline(int tl)
{
  register char *bp, *lp;
  register int nl;

  lp = linebuf;
  bp = getblock(tl, READ);
  nl = nleft;
  tl &= ~0377;
  while ((*lp++ = *bp++))
    if (--nl == 0) {
      bp = getblock(tl=+0400, READ);
      nl = nleft;
    }
  return(linebuf);
}

int
putline(void)
{
  register char *bp, *lp;
  register int nl;
  int tl;

  lp = linebuf;
  tl = tline;
  bp = getblock(tl, WRITE);
  nl = nleft;
  tl &= ~0377;
  while ((*bp = *lp++)) {
    if (*bp++ == '\n') {
      *--bp = 0;
      linebp = lp;
      break;
    }
    if (--nl == 0) {
      bp = getblock(tl=+0400, WRITE);
      nl = nleft;
    }
  }
  nl = tline;
  tline =+ (((lp-linebuf)+03)>>1)&077776;
  return(nl);
}

char*
getblock(int atl, int iof)
{
  register int bno, off;

  bno = (atl>>8)&0377;
  off = (atl<<1)&0774;
  if (bno >= 255) {
    puts(TMPERR);
    error;
  }
  nleft = 512 - off;
  if (bno==iblock) {
    ichanged |= iof;
    return(ibuff+off);
  }
  if (bno==oblock)
    return(obuff+off);
  if (iof==READ) {
    if (ichanged)
      blkio(iblock, ibuff, write);
    ichanged = 0;
    iblock = bno;
    blkio(bno, ibuff, read);
    return(ibuff+off);
  }
  if (oblock>=0)
    blkio(oblock, obuff, write);
  oblock = bno;
  return(obuff+off);
}

void
blkio(int b, char *buf, ssize_t (*iofcn)())
{
  seek(tfile, b, 3);
  if ((*iofcn)(tfile, buf, 512) != 512) {
    puts(TMPERR);
    error;
  }
}

void
init(void)
{
  register char *p;
  register int pid;

  close(tfile);
  tline = 0;
  iblock = -1;
  oblock = -1;
  memcpy(tfname, "/tmp/exxxxx", _nof_(tfname));
  ichanged = 0;
  pid = (int)getpid();
  for (p = &tfname[11]; p > &tfname[6];) {
    *--p = (pid&07) + '0';
    pid >>= 3;
  }
  close(creat(tfname, 0600));
  tfile = open(tfname, 2);
  brk(fendcore);
  dot = zero = dol = fendcore;
  endcore = fendcore - 2;
}

void
global(int k)
{
  register char *gp;
  register int c;
  register int *a1;
  char globuf[GBSIZE];

  if (globp)
    error;
  setall();
  nonzero();
  if ((c=getchar())=='\n')
    error;
  compile(c);
  gp = globuf;
  while ((c = getchar()) != '\n') {
    if (c==EOF)
      error;
    if (c=='\\') {
      c = getchar();
      if (c!='\n')
        *gp++ = '\\';
    }
    *gp++ = c;
    if (gp >= &globuf[GBSIZE-2])
      error;
  }
  *gp++ = '\n';
  *gp++ = 0;
  for (a1=zero; a1<=dol; a1++) {
    *a1 &= ~01;
    if (a1>=addr1 && a1<=addr2 && execute(0, a1)==k)
      *a1 |= 01;
  }
  for (a1=zero; a1<=dol; a1++) {
    if (*a1 & 01) {
      *a1 &= ~01;
      dot = a1;
      globp = globuf;
      commands();
      a1 = zero;
    }
  }
}

void
substitute(char *inglob)
{
  register int gsubf, *a1, nl;
  int getsub();

  gsubf = compsub();
  for (a1 = addr1; a1 <= addr2; a1++) {
    if (execute(0, a1)==0)
      continue;
    inglob += 01;
    dosub();
    if (gsubf) {
      while (*loc2) {
        if (execute(1, 0)==0)
          break;
        dosub();
      }
    }
    *a1 = putline();
    nl = append(getsub, a1);
    a1 += nl;
    addr2 += nl;
  }
  if (inglob==0)
    error;
}

int
compsub(void)
{
  register int seof, c;
  register char *p;
  /* int gsubf; */

  if ((seof = getchar()) == '\n')
    error;
  compile(seof);
  p = rhsbuf;
  for (;;) {
    c = getchar();
    if (c=='\\')
      c = getchar() | 0200;
    if (c=='\n')
      error;
    if (c==seof)
      break;
    *p++ = c;
    if (p >= &rhsbuf[LBSIZE/2])
      error;
  }
  *p++ = 0;
  if ((peekc = getchar()) == 'g') {
    peekc = 0;
    newline();
    return(1);
  }
  newline();
  return(0);
}

int
getsub(void)
{
  register char *p1, *p2;

  p1 = linebuf;
  if ((p2 = linebp) == 0)
    return(EOF);
  while ((*p1++ = *p2++));
  linebp = 0;
  return(0);
}

void
dosub(void)
{
  register char *lp, *sp, *rp;
  int c;

  lp = linebuf;
  sp = genbuf;
  rp = rhsbuf;
  while (lp < loc1)
    *sp++ = *lp++;
  while ((c = *rp++)) {
    if (c=='&') {
      sp = place(sp, loc1, loc2);
      continue;
    } else if (c<0 && (c &= 0177) >='1' && c < NBRA+'1') {
      sp = place(sp, braslist[c-'1'], braelist[c-'1']);
      continue;
    }
    *sp++ = c&0177;
    if (sp >= &genbuf[LBSIZE])
      error;
  }
  lp = loc2;
  loc2 = sp + (linebuf - genbuf);
  while ((*sp++ = *lp++))
    if (sp >= &genbuf[LBSIZE])
      error;
  lp = linebuf;
  sp = genbuf;
  while ((*lp++ = *sp++));
}

char*
place(char *asp, char *al1, char *al2)
{
  register char *sp, *l1, *l2;

  sp = asp;
  l1 = al1;
  l2 = al2;
  while (l1 < l2) {
    *sp++ = *l1++;
    if (sp >= &genbuf[LBSIZE])
      error;
  }
  return(sp);
}

void
move(int cflag)
{
  register int *adt, *ad1, *ad2;
  int getcopy();

  setdot();
  nonzero();
  if ((adt = address())==0)
    error;
  newline();
  ad1 = addr1;
  ad2 = addr2;
  if (cflag) {
    ad1 = dol;
    append(getcopy, ad1++);
    ad2 = dol;
  }
  ad2++;
  if (adt<ad1) {
    dot = adt + (ad2-ad1);
    if ((++adt)==ad1)
      return;
    reverse(adt, ad1);
    reverse(ad1, ad2);
    reverse(adt, ad2);
  } else if (adt >= ad2) {
    dot = adt++;
    reverse(ad1, ad2);
    reverse(ad2, adt);
    reverse(ad1, adt);
  } else
    error;
}

void
reverse(int *aa1, int *aa2)
{
  register int *a1, *a2, t;

  a1 = aa1;
  a2 = aa2;
  for (;;) {
    t = *--a2;
    if (a2 <= a1)
      return;
    *a2 = *a1;
    *a1++ = t;
  }
}

int
getcopy(void)
{
  if (addr1 > addr2)
    return(EOF);
  getline(*addr1++);
  return(0);
}

void
compile(int aeof)
{
  register int eof, c;
  register char *ep;
  char *lastep;
  char bracket[NBRA], *bracketp;
  int nbra;
  int cclcnt;

  ep = expbuf;
  eof = aeof;
  bracketp = bracket;
  nbra = 0;
  if ((c = getchar()) == eof) {
    if (*ep==0)
      error;
    return;
  }
  circfl = 0;
  if (c=='^') {
    c = getchar();
    circfl++;
  }
  if (c=='*')
    goto cerror;
  peekc = c;
  for (;;) {
    if (ep >= &expbuf[ESIZE])
      goto cerror;
    c = getchar();
    if (c==eof) {
      *ep++ = CEOF;
      return;
    }
    if (c!='*')
      lastep = ep;
    switch (c) {

    case '\\':
      if ((c = getchar())=='(') {
        if (nbra >= NBRA)
          goto cerror;
        *bracketp++ = nbra;
        *ep++ = CBRA;
        *ep++ = nbra++;
        continue;
      }
      if (c == ')') {
        if (bracketp <= bracket)
          goto cerror;
        *ep++ = CKET;
        *ep++ = *--bracketp;
        continue;
      }
      *ep++ = CCHR;
      if (c=='\n')
        goto cerror;
      *ep++ = c;
      continue;

    case '.':
      *ep++ = CDOT;
      continue;

    case '\n':
      goto cerror;

    case '*':
      if (*lastep==CBRA || *lastep==CKET)
        error;
      *lastep |= STAR;
      continue;

    case '$':
      if ((peekc=getchar()) != eof)
        goto defchar;
      *ep++ = CDOL;
      continue;

    case '[':
      *ep++ = CCL;
      *ep++ = 0;
      cclcnt = 1;
      if ((c=getchar()) == '^') {
        c = getchar();
        ep[-2] = NCCL;
      }
      do {
        if (c=='\n')
          goto cerror;
        *ep++ = c;
        cclcnt++;
        if (ep >= &expbuf[ESIZE])
          goto cerror;
      } while ((c = getchar()) != ']');
      lastep[1] = cclcnt;
      continue;

    defchar:
    default:
      *ep++ = CCHR;
      *ep++ = c;
    }
  }
   cerror:
  expbuf[0] = 0;
  error;
}

int
execute(int gf, int *addr)
{
  register char *p1, *p2, c;

  if (gf) {
    if (circfl)
      return(0);
    p1 = linebuf;
    p2 = genbuf;
    while ((*p1++ = *p2++));
    locs = p1 = loc2;
  } else {
    if (addr==zero)
      return(0);
    p1 = getline(*addr);
    locs = 0;
  }
  p2 = expbuf;
  if (circfl) {
    loc1 = p1;
    return(advance(p1, p2));
  }
  /* fast check for first character */
  if (*p2==CCHR) {
    c = p2[1];
    do {
      if (*p1!=c)
        continue;
      if (advance(p1, p2)) {
        loc1 = p1;
        return(1);
      }
    } while (*p1++);
    return(0);
  }
  /* regular algorithm */
  do {
    if (advance(p1, p2)) {
      loc1 = p1;
      return(1);
    }
  } while (*p1++);
  return(0);
}

int
advance(char *alp, char *aep)
{
  register char *lp, *ep, *curlp;
  /* char *nextep; */

  lp = alp;
  ep = aep;
  for (;;) switch (*ep++) {

  case CCHR:
    if (*ep++ == *lp++)
      continue;
    return(0);

  case CDOT:
    if (*lp++)
      continue;
    return(0);

  case CDOL:
    if (*lp==0)
      continue;
    return(0);

  case CEOF:
    loc2 = lp;
    return(1);

  case CCL:
    if (cclass(ep, *lp++, 1)) {
      ep += *ep;
      continue;
    }
    return(0);

  case NCCL:
    if (cclass(ep, *lp++, 0)) {
      ep += *ep;
      continue;
    }
    return(0);

  case CBRA:
    braslist[(int)(*ep++)] = lp;
    continue;

  case CKET:
    braelist[(int)(*ep++)] = lp;
    continue;

  case CDOT|STAR:
    curlp = lp;
    while (*lp++);
    goto star;

  case CCHR|STAR:
    curlp = lp;
    while (*lp++ == *ep);
    ep++;
    goto star;

  case CCL|STAR:
  case NCCL|STAR:
    curlp = lp;
    while (cclass(ep, *lp++, ep[-1]==(CCL|STAR)));
    ep += *ep;
    goto star;

  star:
    do {
      lp--;
      if (lp==locs)
        break;
      if (advance(lp, ep))
        return(1);
    } while (lp > curlp);
    return(0);

  default:
    error;
  }
}

int
cclass(char *aset, int ac, int af)
{
  register char *set, c;
  register int n;

  set = aset;
  if ((c = ac) == 0)
    return(0);
  n = *set++;
  while (--n)
    if (*set++ == c)
      return(af);
  return(!af);
}

void
putd(void)
{
  register int r;
  int ldivr;
	ldiv_t dv;
  struct { int q; int r; } w;
  w.q = count[1];
  w.r = count[0];

	dv = ldiv(*(long*)&w, 10);
  count[1] = dv.quot;
  count[0] = 0;
  r = ldivr = dv.rem;
  if (count[1])
    putd();
  putchar(r + '0');
}

void
puts(char *as)
{
  register char *sp;

  sp = as;
  col = 0;
  while (*sp)
    putchar(*sp++);
  putchar('\n');
}

char  line[70];
char  *linp = line;

void
putchar(int ac)
{
  register char *lp;
  register int c;

  lp = linp;
  c = ac;
  if (listf) {
    col++;
    if (col >= 72) {
      col = 0;
      *lp++ = '\\';
      *lp++ = '\n';
    }
    if (c=='\t') {
      c = '>';
      goto esc;
    }
    if (c=='\b') {
      c = '<';
    esc:
      *lp++ = '-';
      *lp++ = '\b';
      *lp++ = c;
      goto out;
    }
    if (c<' ' && c!= '\n') {
      *lp++ = '\\';
      *lp++ = (c>>3)+'0';
      *lp++ = (c&07)+'0';
      col += 2;
      goto out;
    }
  }
  *lp++ = c;
out:
  if(c == '\n' || lp >= &line[64]) {
    linp = line;
    write(1, line, lp-line);
    return;
  }
  linp = lp;
}

/*
 * Get process ID routine if system call is unavailable.
getpid()
{
  register f;
  int b[1];

  f = open("/dev/kmem", 0);
  if(f < 0)
    return(-1);
  seek(f, 0140074, 0);
  read(f, b, 2);
  seek(f, b[0]+8, 0);
  read(f, b, 2);
  close(f);
  return(b[0]);
}
 */
