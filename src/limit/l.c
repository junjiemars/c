#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>


#define STR(s)   #s
#define ULL(u)   (unsigned long long) (u)
#define SLL(s)   (long long) (s)
#define DBL(d)   (long double) (d)

#define FMT_ULL  "%-35s %-24llu\n"
#define FMT_SLL  "%-35s% -24lli\n"
#define FMT_DBL  "%-35s% -24LE\n"
#define FMT_SYM  "%-35s (no symbol)\n"


int main(void) 
{

/* number */
#if defined(CHAR_BIT)
  printf(FMT_ULL, STR(CHAR_BIT), ULL(CHAR_BIT));
#else
  printf(FMT_SYM, STR(CHAR_BIT));
#endif

#if defined(CHAR_MAX)
  printf(FMT_ULL, STR(CHAR_MAX), ULL(CHAR_MAX));
#else
  printf(FMT_SYM, STR(CHAR_MAX));
#endif

#if defined(CHAR_MIN)
  printf(FMT_SLL, STR(CHAR_MIN), SLL(CHAR_MIN));
#else
  printf(FMT_SYM, STR(CHAR_MIN));
#endif

#if defined(SCHAR_MAX)
  printf(FMT_ULL, STR(SCHAR_MAX), ULL(SCHAR_MAX));
#else
  printf(FMT_SYM, STR(SCHAR_MAX));
#endif

#if defined(SCHAR_MIN)
  printf(FMT_SLL, STR(SCHAR_MIN), SLL(SCHAR_MIN));
#else
  printf(FMT_SYM, STR(SCHAR_MIN));
#endif

#if defined(UCHAR_MAX)
  printf(FMT_ULL, STR(UCHAR_MAX), ULL(UCHAR_MAX));
#else
  printf(FMT_SYM, STR(UCHAR_MAX));
#endif

#if defined(SHRT_MAX)
  printf(FMT_ULL, STR(SHRT_MAX), ULL(SHRT_MAX));
#else
  printf(FMT_SYM, STR(SHRT_MAX));
#endif

#if defined(SHRT_MIN)
  printf(FMT_SLL, STR(SHRT_MIN), SLL(SHRT_MIN));
#else
  printf(FMT_SYM, STR(SHRT_MIN));
#endif

#if defined(USHRT_MAX)
  printf(FMT_ULL, STR(USHRT_MAX), ULL(USHRT_MAX));
#else
  printf(FMT_SYM, STR(USHRT_MAX));
#endif

#if defined(INT_MAX)
  printf(FMT_ULL, STR(INT_MAX), ULL(INT_MAX));
#else
  printf(FMT_SYM, STR(INT_MAX));
#endif

#if defined(INT_MIN)
  printf(FMT_SLL, STR(INT_MIN), SLL(INT_MIN));
#else
  printf(FMT_SYM, STR(INT_MIN));
#endif

#if defined(UINT_MAX)
  printf(FMT_ULL, STR(UINT_MAX), ULL(UINT_MAX));
#else
  printf(FMT_SYM, STR(UINT_MAX));
#endif

#if defined(LONG_MAX)
  printf(FMT_ULL, STR(LONG_MAX), ULL(LONG_MAX));
#else
  printf(FMT_SYM, STR(LONG_MAX));
#endif

#if defined(LONG_MIN)
  printf(FMT_SLL, STR(LONG_MIN), SLL(LONG_MIN));
#else
  printf(FMT_SYM, STR(LONG_MIN));
#endif

#if defined(ULONG_MAX)
  printf(FMT_ULL, STR(ULONG_MAX), ULL(ULONG_MAX));
#else
  printf(FMT_SYM, STR(ULONG_MAX));
#endif

#if defined(LLONG_MAX)
  printf(FMT_ULL, STR(LLONG_MAX), ULL(LLONG_MAX));
#else
  printf(FMT_SYM, STR(LLONG_MAX));
#endif

#if defined(LLONG_MIN)
  printf(FMT_SLL, STR(LLONG_MIN), SLL(LLONG_MIN));
#else
  printf(FMT_SYM, STR(LLONG_MIN));
#endif

#if defined(ULLONG_MAX)
  printf(FMT_ULL, STR(ULLONG_MAX), ULL(ULLONG_MAX));
#else
  printf(FMT_SYM, STR(ULLONG_MAX));
#endif

#if defined(FLT_MAX)
  printf(FMT_DBL, STR(FLT_MAX), DBL(FLT_MAX));
#else
  printf(FMT_SYM, STR(FLT_MAX));
#endif

#if defined(FLT_MIN)
  printf(FMT_DBL, STR(FLT_MIN), DBL(FLT_MIN));
#else
  printf(FMT_SYM, STR(FLT_MIN));
#endif

#if defined(DBL_MAX)
  printf(FMT_DBL, STR(DBL_MAX), DBL(DBL_MAX));
#else
  printf(FMT_SYM, STR(DBL_MAX));
#endif

#if defined(DBL_MIN)
  printf(FMT_DBL, STR(DBL_MIN), DBL(DBL_MIN));
#else
  printf(FMT_SYM, STR(DBL_MIN));
#endif

#if defined(LDBL_MAX)
  printf(FMT_DBL, STR(LDBL_MAX), DBL(LDBL_MAX));
#else
  printf(FMT_SYM, STR(LDBL_MAX));
#endif

#if defined(LDBL_MIN)
  printf(FMT_DBL, STR(LDBL_MIN), DBL(LDBL_MIN));
#else
  printf(FMT_SYM, STR(LDBL_MIN));
#endif


/* system */
#if defined(AIO_LISTIO_MAX)
  printf(FMT_ULL, STR(AIO_LISTIO_MAX), ULL(AIO_LISTIO_MAX));
#else
  printf(FMT_SYM, STR(AIO_LISTIO_MAX));
#endif

#if defined(AIO_MAX)
  printf(FMT_ULL, STR(AIO_MAX), ULL(AIO_MAX));
#else
  printf(FMT_SYM, STR(AIO_MAX));
#endif

#if defined(AIO_PRIO_DELTA_MAX)
  printf(FMT_ULL, STR(AIO_PRIO_DELTA_MAX), ULL(AIO_PRIO_DELTA_MAX));
#else
  printf(FMT_SYM, STR(AIO_PRIO_DELTA_MAX));
#endif

#if defined(ARG_MAX)
  printf(FMT_ULL, STR(ARG_MAX), ULL(ARG_MAX));
#else
  printf(FMT_SYM, STR(ARG_MAX));
#endif

#if defined(ATEXIT_MAX)
  printf(FMT_ULL, STR(ATEXIT_MAX), ULL(ATEXIT_MAX));
#else
  printf(FMT_SYM, STR(ATEXIT_MAX));
#endif

#if defined(BC_BASE_MAX)
  printf(FMT_ULL, STR(BC_BASE_MAX), ULL(BC_BASE_MAX));
#else
  printf(FMT_SYM, STR(BC_BASE_MAX));
#endif

#if defined(BC_DIM_MAX)
  printf(FMT_ULL, STR(BC_DIM_MAX), ULL(BC_DIM_MAX));
#else
  printf(FMT_SYM, STR(BC_DIM_MAX));
#endif

#if defined(BC_SCALE_MAX)
  printf(FMT_ULL, STR(BC_SCALE_MAX), ULL(BC_SCALE_MAX));
#else
  printf(FMT_SYM, STR(BC_SCALE_MAX));
#endif

#if defined(BC_STRING_MAX)
  printf(FMT_ULL, STR(BC_STRING_MAX), ULL(BC_STRING_MAX));
#else
  printf(FMT_SYM, STR(BC_STRING_MAX));
#endif

#if defined(CHARCLASS_NAME_MAX)
  printf(FMT_ULL, STR(CHARCLASS_NAME_MAX), ULL(CHARCLASS_NAME_MAX));
#else
  printf(FMT_SYM, STR(CHARCLASS_NAME_MAX));
#endif

#if defined(CHILD_MAX)
  printf(FMT_ULL, STR(CHILD_MAX), ULL(CHILD_MAX));
#else
  printf(FMT_SYM, STR(CHILD_MAX));
#endif

#if defined(CLK_TCK)
  printf(FMT_ULL, STR(CLK_TCK), ULL(CLK_TCK));
#else
  printf(FMT_SYM, STR(CLK_TCK));
#endif

#if defined(COLL_WEIGHTS_MAX)
  printf(FMT_ULL, STR(COLL_WEIGHTS_MAX), ULL(COLL_WEIGHTS_MAX));
#else
  printf(FMT_SYM, STR(COLL_WEIGHTS_MAX));
#endif

#if defined(DELAYTIMER_MAX)
  printf(FMT_ULL, STR(DELAYTIMER_MAX), ULL(DELAYTIMER_MAX));
#else
  printf(FMT_SYM, STR(DELAYTIMER_MAX));
#endif

#if defined(EQUIV_CLASS_MAX)
  printf(FMT_ULL, STR(EQUIV_CLASS_MAX), ULL(EQUIV_CLASS_MAX));
#else
  printf(FMT_SYM, STR(EQUIV_CLASS_MAX));
#endif

#if defined(EXPR_NEST_MAX)
  printf(FMT_ULL, STR(EXPR_NEST_MAX), ULL(EXPR_NEST_MAX));
#else
  printf(FMT_SYM, STR(EXPR_NEST_MAX));
#endif

#if defined(FILESIZEBITS)
  printf(FMT_ULL, STR(FILESIZEBITS), ULL(FILESIZEBITS));
#else
  printf(FMT_SYM, STR(FILESIZEBITS));
#endif

#if defined(HOST_NAME_MAX)
  printf(FMT_ULL, STR(HOST_NAME_MAX), ULL(HOST_NAME_MAX));
#else
  printf(FMT_SYM, STR(HOST_NAME_MAX));
#endif

#if defined(IOV_MAX)
  printf(FMT_ULL, STR(IOV_MAX), ULL(IOV_MAX));
#else
  printf(FMT_SYM, STR(IOV_MAX));
#endif

#if defined(LINE_MAX)
  printf(FMT_ULL, STR(LINE_MAX), ULL(LINE_MAX));
#else
  printf(FMT_SYM, STR(LINE_MAX));
#endif

#if defined(LINK_MAX)
  printf(FMT_ULL, STR(LINK_MAX), ULL(LINK_MAX));
#else
  printf(FMT_SYM, STR(LINK_MAX));
#endif

#if defined(LOGIN_NAME_MAX)
  printf(FMT_ULL, STR(LOGIN_NAME_MAX), ULL(LOGIN_NAME_MAX));
#else
  printf(FMT_SYM, STR(LOGIN_NAME_MAX));
#endif

#if defined(LOGNAME_MAX)
  printf(FMT_ULL, STR(LOGNAME_MAX), ULL(LOGNAME_MAX));
#else
  printf(FMT_SYM, STR(LOGNAME_MAX));
#endif

#if defined(MAX_CANON)
  printf(FMT_ULL, STR(MAX_CANON), ULL(MAX_CANON));
#else
  printf(FMT_SYM, STR(MAX_CANON));
#endif

#if defined(MAX_INPUT)
  printf(FMT_ULL, STR(MAX_INPUT), ULL(MAX_INPUT));
#else
  printf(FMT_SYM, STR(MAX_INPUT));
#endif

#if defined(MB_LEN_MAX)
  printf(FMT_ULL, STR(MB_LEN_MAX), ULL(MB_LEN_MAX));
#else
  printf(FMT_SYM, STR(MB_LEN_MAX));
#endif

#if defined(MQ_OPEN_MAX)
  printf(FMT_ULL, STR(MQ_OPEN_MAX), ULL(MQ_OPEN_MAX));
#else
  printf(FMT_SYM, STR(MQ_OPEN_MAX));
#endif

#if defined(MQ_PRIO_MAX)
  printf(FMT_ULL, STR(MQ_PRIO_MAX), ULL(MQ_PRIO_MAX));
#else
  printf(FMT_SYM, STR(MQ_PRIO_MAX));
#endif

#if defined(NAME_MAX)
  printf(FMT_ULL, STR(NAME_MAX), ULL(NAME_MAX));
#else
  printf(FMT_SYM, STR(NAME_MAX));
#endif

#if defined(NGROUPS_MAX)
  printf(FMT_ULL, STR(NGROUPS_MAX), ULL(NGROUPS_MAX));
#else
  printf(FMT_SYM, STR(NGROUPS_MAX));
#endif

#if defined(NL_ARGMAX)
  printf(FMT_ULL, STR(NL_ARGMAX), ULL(NL_ARGMAX));
#else
  printf(FMT_SYM, STR(NL_ARGMAX));
#endif

#if defined(NL_LANGMAX)
  printf(FMT_ULL, STR(NL_LANGMAX), ULL(NL_LANGMAX));
#else
  printf(FMT_SYM, STR(NL_LANGMAX));
#endif

#if defined(NL_MSGMAX)
  printf(FMT_ULL, STR(NL_MSGMAX), ULL(NL_MSGMAX));
#else
  printf(FMT_SYM, STR(NL_MSGMAX));
#endif

#if defined(NL_NMAX)
  printf(FMT_ULL, STR(NL_NMAX), ULL(NL_NMAX));
#else
  printf(FMT_SYM, STR(NL_NMAX));
#endif

#if defined(NL_SETMAX)
  printf(FMT_ULL, STR(NL_SETMAX), ULL(NL_SETMAX));
#else
  printf(FMT_SYM, STR(NL_SETMAX));
#endif

#if defined(NL_TEXTMAX)
  printf(FMT_ULL, STR(NL_TEXTMAX), ULL(NL_TEXTMAX));
#else
  printf(FMT_SYM, STR(NL_TEXTMAX));
#endif

#if defined(NSS_BUFLEN_GROUP)
  printf(FMT_ULL, STR(NSS_BUFLEN_GROUP), ULL(NSS_BUFLEN_GROUP));
#else
  printf(FMT_SYM, STR(NSS_BUFLEN_GROUP));
#endif

#if defined(NSS_BUFLEN_PASSWD)
  printf(FMT_ULL, STR(NSS_BUFLEN_PASSWD), ULL(NSS_BUFLEN_PASSWD));
#else
  printf(FMT_SYM, STR(NSS_BUFLEN_PASSWD));
#endif

#if defined(NZERO)
  printf(FMT_ULL, STR(NZERO), ULL(NZERO));
#else
  printf(FMT_SYM, STR(NZERO));
#endif

#if defined(OPEN_MAX)
  printf(FMT_ULL, STR(OPEN_MAX), ULL(OPEN_MAX));
#else
  printf(FMT_SYM, STR(OPEN_MAX));
#endif

#if defined(PAGESIZE)
  printf(FMT_ULL, STR(PAGESIZE), ULL(PAGESIZE));
#else
  printf(FMT_SYM, STR(PAGESIZE));
#endif

#if defined(PAGE_SIZE)
  printf(FMT_ULL, STR(PAGE_SIZE), ULL(PAGE_SIZE));
#else
  printf(FMT_SYM, STR(PAGE_SIZE));
#endif

#if defined(PASS_MAX)
  printf(FMT_ULL, STR(PASS_MAX), ULL(PASS_MAX));
#else
  printf(FMT_SYM, STR(PASS_MAX));
#endif

#if defined(PATH_MAX)
  printf(FMT_ULL, STR(PATH_MAX), ULL(PATH_MAX));
#else
  printf(FMT_SYM, STR(PATH_MAX));
#endif

#if defined(PIPE_BUF)
  printf(FMT_ULL, STR(PIPE_BUF), ULL(PIPE_BUF));
#else
  printf(FMT_SYM, STR(PIPE_BUF));
#endif

#if defined(POSIX2_BC_BASE_MAX)
  printf(FMT_ULL, STR(POSIX2_BC_BASE_MAX), ULL(POSIX2_BC_BASE_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_BC_BASE_MAX));
#endif

#if defined(POSIX2_BC_DIM_MAX)
  printf(FMT_ULL, STR(POSIX2_BC_DIM_MAX), ULL(POSIX2_BC_DIM_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_BC_DIM_MAX));
#endif

#if defined(POSIX2_BC_SCALE_MAX)
  printf(FMT_ULL, STR(POSIX2_BC_SCALE_MAX), ULL(POSIX2_BC_SCALE_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_BC_SCALE_MAX));
#endif

#if defined(POSIX2_BC_STRING_MAX)
  printf(FMT_ULL, STR(POSIX2_BC_STRING_MAX), ULL(POSIX2_BC_STRING_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_BC_STRING_MAX));
#endif

#if defined(POSIX2_CHAR_TERM)
  printf(FMT_ULL, STR(POSIX2_CHAR_TERM), ULL(POSIX2_CHAR_TERM));
#else
  printf(FMT_SYM, STR(POSIX2_CHAR_TERM));
#endif

#if defined(POSIX2_COLL_WEIGHTS_MAX)
  printf(FMT_ULL, STR(POSIX2_COLL_WEIGHTS_MAX), ULL(POSIX2_COLL_WEIGHTS_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_COLL_WEIGHTS_MAX));
#endif

#if defined(POSIX2_C_BIND)
  printf(FMT_ULL, STR(POSIX2_C_BIND), ULL(POSIX2_C_BIND));
#else
  printf(FMT_SYM, STR(POSIX2_C_BIND));
#endif

#if defined(POSIX2_C_DEV)
  printf(FMT_ULL, STR(POSIX2_C_DEV), ULL(POSIX2_C_DEV));
#else
  printf(FMT_SYM, STR(POSIX2_C_DEV));
#endif

#if defined(POSIX2_C_VERSION)
  printf(FMT_ULL, STR(POSIX2_C_VERSION), ULL(POSIX2_C_VERSION));
#else
  printf(FMT_SYM, STR(POSIX2_C_VERSION));
#endif

#if defined(POSIX2_EXPR_NEST_MAX)
  printf(FMT_ULL, STR(POSIX2_EXPR_NEST_MAX), ULL(POSIX2_EXPR_NEST_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_EXPR_NEST_MAX));
#endif

#if defined(POSIX2_FORT_DEV)
  printf(FMT_ULL, STR(POSIX2_FORT_DEV), ULL(POSIX2_FORT_DEV));
#else
  printf(FMT_SYM, STR(POSIX2_FORT_DEV));
#endif

#if defined(POSIX2_FORT_RUN)
  printf(FMT_ULL, STR(POSIX2_FORT_RUN), ULL(POSIX2_FORT_RUN));
#else
  printf(FMT_SYM, STR(POSIX2_FORT_RUN));
#endif

#if defined(POSIX2_LINE_MAX)
  printf(FMT_ULL, STR(POSIX2_LINE_MAX), ULL(POSIX2_LINE_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_LINE_MAX));
#endif

#if defined(POSIX2_LOCALEDEF)
  printf(FMT_ULL, STR(POSIX2_LOCALEDEF), ULL(POSIX2_LOCALEDEF));
#else
  printf(FMT_SYM, STR(POSIX2_LOCALEDEF));
#endif

#if defined(POSIX2_RE_DUP_MAX)
  printf(FMT_ULL, STR(POSIX2_RE_DUP_MAX), ULL(POSIX2_RE_DUP_MAX));
#else
  printf(FMT_SYM, STR(POSIX2_RE_DUP_MAX));
#endif

#if defined(POSIX2_SW_DEV)
  printf(FMT_ULL, STR(POSIX2_SW_DEV), ULL(POSIX2_SW_DEV));
#else
  printf(FMT_SYM, STR(POSIX2_SW_DEV));
#endif

#if defined(POSIX2_SYMLINKS)
  printf(FMT_ULL, STR(POSIX2_SYMLINKS), ULL(POSIX2_SYMLINKS));
#else
  printf(FMT_SYM, STR(POSIX2_SYMLINKS));
#endif

#if defined(POSIX2_UPE)
  printf(FMT_ULL, STR(POSIX2_UPE), ULL(POSIX2_UPE));
#else
  printf(FMT_SYM, STR(POSIX2_UPE));
#endif

#if defined(POSIX2_VERSION)
  printf(FMT_ULL, STR(POSIX2_VERSION), ULL(POSIX2_VERSION));
#else
  printf(FMT_SYM, STR(POSIX2_VERSION));
#endif

#if defined(POSIX_ALLOC_SIZE_MIN)
  printf(FMT_ULL, STR(POSIX_ALLOC_SIZE_MIN), ULL(POSIX_ALLOC_SIZE_MIN));
#else
  printf(FMT_SYM, STR(POSIX_ALLOC_SIZE_MIN));
#endif

#if defined(POSIX_REC_INCR_XFER_SIZE)
  printf(FMT_ULL, STR(POSIX_REC_INCR_XFER_SIZE), ULL(POSIX_REC_INCR_XFER_SIZE));
#else
  printf(FMT_SYM, STR(POSIX_REC_INCR_XFER_SIZE));
#endif

#if defined(POSIX_REC_MAX_XFER_SIZE)
  printf(FMT_ULL, STR(POSIX_REC_MAX_XFER_SIZE), ULL(POSIX_REC_MAX_XFER_SIZE));
#else
  printf(FMT_SYM, STR(POSIX_REC_MAX_XFER_SIZE));
#endif

#if defined(POSIX_REC_MIN_XFER_SIZE)
  printf(FMT_ULL, STR(POSIX_REC_MIN_XFER_SIZE), ULL(POSIX_REC_MIN_XFER_SIZE));
#else
  printf(FMT_SYM, STR(POSIX_REC_MIN_XFER_SIZE));
#endif

#if defined(POSIX_REC_XFER_ALIGN)
  printf(FMT_ULL, STR(POSIX_REC_XFER_ALIGN), ULL(POSIX_REC_XFER_ALIGN));
#else
  printf(FMT_SYM, STR(POSIX_REC_XFER_ALIGN));
#endif

#if defined(PTHREAD_DESTRUCTOR_ITERATIONS)
  printf(FMT_ULL, STR(PTHREAD_DESTRUCTOR_ITERATIONS), ULL(PTHREAD_DESTRUCTOR_ITERATIONS));
#else
  printf(FMT_SYM, STR(PTHREAD_DESTRUCTOR_ITERATIONS));
#endif

#if defined(PTHREAD_KEYS_MAX)
  printf(FMT_ULL, STR(PTHREAD_KEYS_MAX), ULL(PTHREAD_KEYS_MAX));
#else
  printf(FMT_SYM, STR(PTHREAD_KEYS_MAX));
#endif

#if defined(PTHREAD_STACK_MIN)
  printf(FMT_ULL, STR(PTHREAD_STACK_MIN), ULL(PTHREAD_STACK_MIN));
#else
  printf(FMT_SYM, STR(PTHREAD_STACK_MIN));
#endif

#if defined(PTHREAD_THREADS_MAX)
  printf(FMT_ULL, STR(PTHREAD_THREADS_MAX), ULL(PTHREAD_THREADS_MAX));
#else
  printf(FMT_SYM, STR(PTHREAD_THREADS_MAX));
#endif

#if defined(RAW_SOCKETS)
  printf(FMT_ULL, STR(RAW_SOCKETS), ULL(RAW_SOCKETS));
#else
  printf(FMT_SYM, STR(RAW_SOCKETS));
#endif

#if defined(RE_DUP_MAX)
  printf(FMT_ULL, STR(RE_DUP_MAX), ULL(RE_DUP_MAX));
#else
  printf(FMT_SYM, STR(RE_DUP_MAX));
#endif

#if defined(RTSIG_MAX)
  printf(FMT_ULL, STR(RTSIG_MAX), ULL(RTSIG_MAX));
#else
  printf(FMT_SYM, STR(RTSIG_MAX));
#endif

#if defined(SEM_NSEMS_MAX)
  printf(FMT_ULL, STR(SEM_NSEMS_MAX), ULL(SEM_NSEMS_MAX));
#else
  printf(FMT_SYM, STR(SEM_NSEMS_MAX));
#endif

#if defined(SEM_VALUE_MAX)
  printf(FMT_ULL, STR(SEM_VALUE_MAX), ULL(SEM_VALUE_MAX));
#else
  printf(FMT_SYM, STR(SEM_VALUE_MAX));
#endif

#if defined(SIGQUEUE_MAX)
  printf(FMT_ULL, STR(SIGQUEUE_MAX), ULL(SIGQUEUE_MAX));
#else
  printf(FMT_SYM, STR(SIGQUEUE_MAX));
#endif

#if defined(SOCK_MAXBUF)
  printf(FMT_ULL, STR(SOCK_MAXBUF), ULL(SOCK_MAXBUF));
#else
  printf(FMT_SYM, STR(SOCK_MAXBUF));
#endif

#if defined(SSIZE_MAX)
  printf(FMT_ULL, STR(SSIZE_MAX), ULL(SSIZE_MAX));
#else
  printf(FMT_SYM, STR(SSIZE_MAX));
#endif

#if defined(STREAM_MAX)
  printf(FMT_ULL, STR(STREAM_MAX), ULL(STREAM_MAX));
#else
  printf(FMT_SYM, STR(STREAM_MAX));
#endif

#if defined(SYMLINK_MAX)
  printf(FMT_ULL, STR(SYMLINK_MAX), ULL(SYMLINK_MAX));
#else
  printf(FMT_SYM, STR(SYMLINK_MAX));
#endif

#if defined(SYMLOOP_MAX)
  printf(FMT_ULL, STR(SYMLOOP_MAX), ULL(SYMLOOP_MAX));
#else
  printf(FMT_SYM, STR(SYMLOOP_MAX));
#endif

#if defined(TIMER_MAX)
  printf(FMT_ULL, STR(TIMER_MAX), ULL(TIMER_MAX));
#else
  printf(FMT_SYM, STR(TIMER_MAX));
#endif

#if defined(TTY_NAME_MAX)
  printf(FMT_ULL, STR(TTY_NAME_MAX), ULL(TTY_NAME_MAX));
#else
  printf(FMT_SYM, STR(TTY_NAME_MAX));
#endif

#if defined(TZNAME_MAX)
  printf(FMT_ULL, STR(TZNAME_MAX), ULL(TZNAME_MAX));
#else
  printf(FMT_SYM, STR(TZNAME_MAX));
#endif

#if defined(UINT_MAX)
  printf(FMT_ULL, STR(UINT_MAX), ULL(UINT_MAX));
#else
  printf(FMT_SYM, STR(UINT_MAX));
#endif

#if defined(UIO_MAXIOV)
  printf(FMT_ULL, STR(UIO_MAXIOV), ULL(UIO_MAXIOV));
#else
  printf(FMT_SYM, STR(UIO_MAXIOV));
#endif

#if defined(WORD_BIT)
  printf(FMT_ULL, STR(WORD_BIT), ULL(WORD_BIT));
#else
  printf(FMT_SYM, STR(WORD_BIT));
#endif

#if defined(_AVPHYS_PAGES)
  printf(FMT_ULL, STR(_AVPHYS_PAGES), ULL(_AVPHYS_PAGES));
#else
  printf(FMT_SYM, STR(_AVPHYS_PAGES));
#endif

#if defined(_NPROCESSORS_CONF)
  printf(FMT_ULL, STR(_NPROCESSORS_CONF), ULL(_NPROCESSORS_CONF));
#else
  printf(FMT_SYM, STR(_NPROCESSORS_CONF));
#endif

#if defined(_NPROCESSORS_ONLN)
  printf(FMT_ULL, STR(_NPROCESSORS_ONLN), ULL(_NPROCESSORS_ONLN));
#else
  printf(FMT_SYM, STR(_NPROCESSORS_ONLN));
#endif

#if defined(_PHYS_PAGES)
  printf(FMT_ULL, STR(_PHYS_PAGES), ULL(_PHYS_PAGES));
#else
  printf(FMT_SYM, STR(_PHYS_PAGES));
#endif

#if defined(_POSIX2_LINE_MAX)
  printf(FMT_ULL, STR(_POSIX2_LINE_MAX), ULL(_POSIX2_LINE_MAX));
#else
  printf(FMT_SYM, STR(_POSIX2_LINE_MAX));
#endif

#if defined(_POSIX_ADVISORY_INFO)
  printf(FMT_ULL, STR(_POSIX_ADVISORY_INFO), ULL(_POSIX_ADVISORY_INFO));
#else
  printf(FMT_SYM, STR(_POSIX_ADVISORY_INFO));
#endif

#if defined(_POSIX_ARG_MAX)
  printf(FMT_ULL, STR(_POSIX_ARG_MAX), ULL(_POSIX_ARG_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_ARG_MAX));
#endif

#if defined(_POSIX_ASYNCHRONOUS_IO)
  printf(FMT_ULL, STR(_POSIX_ASYNCHRONOUS_IO), ULL(_POSIX_ASYNCHRONOUS_IO));
#else
  printf(FMT_SYM, STR(_POSIX_ASYNCHRONOUS_IO));
#endif

#if defined(_POSIX_ASYNC_IO)
  printf(FMT_ULL, STR(_POSIX_ASYNC_IO), ULL(_POSIX_ASYNC_IO));
#else
  printf(FMT_SYM, STR(_POSIX_ASYNC_IO));
#endif

#if defined(_POSIX_BARRIERS)
  printf(FMT_ULL, STR(_POSIX_BARRIERS), ULL(_POSIX_BARRIERS));
#else
  printf(FMT_SYM, STR(_POSIX_BARRIERS));
#endif

#if defined(_POSIX_BASE)
  printf(FMT_ULL, STR(_POSIX_BASE), ULL(_POSIX_BASE));
#else
  printf(FMT_SYM, STR(_POSIX_BASE));
#endif

#if defined(_POSIX_CHILD_MAX)
  printf(FMT_ULL, STR(_POSIX_CHILD_MAX), ULL(_POSIX_CHILD_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_CHILD_MAX));
#endif

#if defined(_POSIX_CHOWN_RESTRICTED)
  printf(FMT_ULL, STR(_POSIX_CHOWN_RESTRICTED), ULL(_POSIX_CHOWN_RESTRICTED));
#else
  printf(FMT_SYM, STR(_POSIX_CHOWN_RESTRICTED));
#endif

#if defined(_POSIX_CLOCK_SELECTION)
  printf(FMT_ULL, STR(_POSIX_CLOCK_SELECTION), ULL(_POSIX_CLOCK_SELECTION));
#else
  printf(FMT_SYM, STR(_POSIX_CLOCK_SELECTION));
#endif

#if defined(_POSIX_CPUTIME)
  printf(FMT_ULL, STR(_POSIX_CPUTIME), ULL(_POSIX_CPUTIME));
#else
  printf(FMT_SYM, STR(_POSIX_CPUTIME));
#endif

#if defined(_POSIX_C_LANG_SUPPORT)
  printf(FMT_ULL, STR(_POSIX_C_LANG_SUPPORT), ULL(_POSIX_C_LANG_SUPPORT));
#else
  printf(FMT_SYM, STR(_POSIX_C_LANG_SUPPORT));
#endif

#if defined(_POSIX_C_LANG_SUPPORT_R)
  printf(FMT_ULL, STR(_POSIX_C_LANG_SUPPORT_R), ULL(_POSIX_C_LANG_SUPPORT_R));
#else
  printf(FMT_SYM, STR(_POSIX_C_LANG_SUPPORT_R));
#endif

#if defined(_POSIX_DEVICE_IO)
  printf(FMT_ULL, STR(_POSIX_DEVICE_IO), ULL(_POSIX_DEVICE_IO));
#else
  printf(FMT_SYM, STR(_POSIX_DEVICE_IO));
#endif

#if defined(_POSIX_DEVICE_SPECIFIC)
  printf(FMT_ULL, STR(_POSIX_DEVICE_SPECIFIC), ULL(_POSIX_DEVICE_SPECIFIC));
#else
  printf(FMT_SYM, STR(_POSIX_DEVICE_SPECIFIC));
#endif

#if defined(_POSIX_DEVICE_SPECIFIC_R)
  printf(FMT_ULL, STR(_POSIX_DEVICE_SPECIFIC_R), ULL(_POSIX_DEVICE_SPECIFIC_R));
#else
  printf(FMT_SYM, STR(_POSIX_DEVICE_SPECIFIC_R));
#endif

#if defined(_POSIX_FD_MGMT)
  printf(FMT_ULL, STR(_POSIX_FD_MGMT), ULL(_POSIX_FD_MGMT));
#else
  printf(FMT_SYM, STR(_POSIX_FD_MGMT));
#endif

#if defined(_POSIX_FIFO)
  printf(FMT_ULL, STR(_POSIX_FIFO), ULL(_POSIX_FIFO));
#else
  printf(FMT_SYM, STR(_POSIX_FIFO));
#endif

#if defined(_POSIX_FILE_ATTRIBUTES)
  printf(FMT_ULL, STR(_POSIX_FILE_ATTRIBUTES), ULL(_POSIX_FILE_ATTRIBUTES));
#else
  printf(FMT_SYM, STR(_POSIX_FILE_ATTRIBUTES));
#endif

#if defined(_POSIX_FILE_LOCKING)
  printf(FMT_ULL, STR(_POSIX_FILE_LOCKING), ULL(_POSIX_FILE_LOCKING));
#else
  printf(FMT_SYM, STR(_POSIX_FILE_LOCKING));
#endif

#if defined(_POSIX_FILE_SYSTEM)
  printf(FMT_ULL, STR(_POSIX_FILE_SYSTEM), ULL(_POSIX_FILE_SYSTEM));
#else
  printf(FMT_SYM, STR(_POSIX_FILE_SYSTEM));
#endif

#if defined(_POSIX_FSYNC)
  printf(FMT_ULL, STR(_POSIX_FSYNC), ULL(_POSIX_FSYNC));
#else
  printf(FMT_SYM, STR(_POSIX_FSYNC));
#endif

#if defined(_POSIX_IPV6)
  printf(FMT_ULL, STR(_POSIX_IPV6), ULL(_POSIX_IPV6));
#else
  printf(FMT_SYM, STR(_POSIX_IPV6));
#endif

#if defined(_POSIX_JOB_CONTROL)
  printf(FMT_ULL, STR(_POSIX_JOB_CONTROL), ULL(_POSIX_JOB_CONTROL));
#else
  printf(FMT_SYM, STR(_POSIX_JOB_CONTROL));
#endif

#if defined(_POSIX_LINK_MAX)
  printf(FMT_ULL, STR(_POSIX_LINK_MAX), ULL(_POSIX_LINK_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_LINK_MAX));
#endif

#if defined(_POSIX_MAPPED_FILES)
  printf(FMT_ULL, STR(_POSIX_MAPPED_FILES), ULL(_POSIX_MAPPED_FILES));
#else
  printf(FMT_SYM, STR(_POSIX_MAPPED_FILES));
#endif

#if defined(_POSIX_MAX_CANON)
  printf(FMT_ULL, STR(_POSIX_MAX_CANON), ULL(_POSIX_MAX_CANON));
#else
  printf(FMT_SYM, STR(_POSIX_MAX_CANON));
#endif

#if defined(_POSIX_MAX_INPUT)
  printf(FMT_ULL, STR(_POSIX_MAX_INPUT), ULL(_POSIX_MAX_INPUT));
#else
  printf(FMT_SYM, STR(_POSIX_MAX_INPUT));
#endif

#if defined(_POSIX_MEMLOCK)
  printf(FMT_ULL, STR(_POSIX_MEMLOCK), ULL(_POSIX_MEMLOCK));
#else
  printf(FMT_SYM, STR(_POSIX_MEMLOCK));
#endif

#if defined(_POSIX_MEMLOCK_RANGE)
  printf(FMT_ULL, STR(_POSIX_MEMLOCK_RANGE), ULL(_POSIX_MEMLOCK_RANGE));
#else
  printf(FMT_SYM, STR(_POSIX_MEMLOCK_RANGE));
#endif

#if defined(_POSIX_MEMORY_PROTECTION)
  printf(FMT_ULL, STR(_POSIX_MEMORY_PROTECTION), ULL(_POSIX_MEMORY_PROTECTION));
#else
  printf(FMT_SYM, STR(_POSIX_MEMORY_PROTECTION));
#endif

#if defined(_POSIX_MESSAGE_PASSING)
  printf(FMT_ULL, STR(_POSIX_MESSAGE_PASSING), ULL(_POSIX_MESSAGE_PASSING));
#else
  printf(FMT_SYM, STR(_POSIX_MESSAGE_PASSING));
#endif

#if defined(_POSIX_MONOTONIC_CLOCK)
  printf(FMT_ULL, STR(_POSIX_MONOTONIC_CLOCK), ULL(_POSIX_MONOTONIC_CLOCK));
#else
  printf(FMT_SYM, STR(_POSIX_MONOTONIC_CLOCK));
#endif

#if defined(_POSIX_MULTI_PROCESS)
  printf(FMT_ULL, STR(_POSIX_MULTI_PROCESS), ULL(_POSIX_MULTI_PROCESS));
#else
  printf(FMT_SYM, STR(_POSIX_MULTI_PROCESS));
#endif

#if defined(_POSIX_NAME_MAX)
  printf(FMT_ULL, STR(_POSIX_NAME_MAX), ULL(_POSIX_NAME_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_NAME_MAX));
#endif

#if defined(_POSIX_NETWORKING)
  printf(FMT_ULL, STR(_POSIX_NETWORKING), ULL(_POSIX_NETWORKING));
#else
  printf(FMT_SYM, STR(_POSIX_NETWORKING));
#endif

#if defined(_POSIX_NGROUPS_MAX)
  printf(FMT_ULL, STR(_POSIX_NGROUPS_MAX), ULL(_POSIX_NGROUPS_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_NGROUPS_MAX));
#endif

#if defined(_POSIX_NO_TRUNC)
  printf(FMT_ULL, STR(_POSIX_NO_TRUNC), ULL(_POSIX_NO_TRUNC));
#else
  printf(FMT_SYM, STR(_POSIX_NO_TRUNC));
#endif

#if defined(_POSIX_OPEN_MAX)
  printf(FMT_ULL, STR(_POSIX_OPEN_MAX), ULL(_POSIX_OPEN_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_OPEN_MAX));
#endif

#if defined(_POSIX_PATH_MAX)
  printf(FMT_ULL, STR(_POSIX_PATH_MAX), ULL(_POSIX_PATH_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_PATH_MAX));
#endif

#if defined(_POSIX_PII)
  printf(FMT_ULL, STR(_POSIX_PII), ULL(_POSIX_PII));
#else
  printf(FMT_SYM, STR(_POSIX_PII));
#endif

#if defined(_POSIX_PII_INTERNET)
  printf(FMT_ULL, STR(_POSIX_PII_INTERNET), ULL(_POSIX_PII_INTERNET));
#else
  printf(FMT_SYM, STR(_POSIX_PII_INTERNET));
#endif

#if defined(_POSIX_PII_INTERNET_DGRAM)
  printf(FMT_ULL, STR(_POSIX_PII_INTERNET_DGRAM), ULL(_POSIX_PII_INTERNET_DGRAM));
#else
  printf(FMT_SYM, STR(_POSIX_PII_INTERNET_DGRAM));
#endif

#if defined(_POSIX_PII_INTERNET_STREAM)
  printf(FMT_ULL, STR(_POSIX_PII_INTERNET_STREAM), ULL(_POSIX_PII_INTERNET_STREAM));
#else
  printf(FMT_SYM, STR(_POSIX_PII_INTERNET_STREAM));
#endif

#if defined(_POSIX_PII_OSI)
  printf(FMT_ULL, STR(_POSIX_PII_OSI), ULL(_POSIX_PII_OSI));
#else
  printf(FMT_SYM, STR(_POSIX_PII_OSI));
#endif

#if defined(_POSIX_PII_OSI_CLTS)
  printf(FMT_ULL, STR(_POSIX_PII_OSI_CLTS), ULL(_POSIX_PII_OSI_CLTS));
#else
  printf(FMT_SYM, STR(_POSIX_PII_OSI_CLTS));
#endif

#if defined(_POSIX_PII_OSI_COTS)
  printf(FMT_ULL, STR(_POSIX_PII_OSI_COTS), ULL(_POSIX_PII_OSI_COTS));
#else
  printf(FMT_SYM, STR(_POSIX_PII_OSI_COTS));
#endif

#if defined(_POSIX_PII_OSI_M)
  printf(FMT_ULL, STR(_POSIX_PII_OSI_M), ULL(_POSIX_PII_OSI_M));
#else
  printf(FMT_SYM, STR(_POSIX_PII_OSI_M));
#endif

#if defined(_POSIX_PII_SOCKET)
  printf(FMT_ULL, STR(_POSIX_PII_SOCKET), ULL(_POSIX_PII_SOCKET));
#else
  printf(FMT_SYM, STR(_POSIX_PII_SOCKET));
#endif

#if defined(_POSIX_PII_XTI)
  printf(FMT_ULL, STR(_POSIX_PII_XTI), ULL(_POSIX_PII_XTI));
#else
  printf(FMT_SYM, STR(_POSIX_PII_XTI));
#endif

#if defined(_POSIX_PIPE)
  printf(FMT_ULL, STR(_POSIX_PIPE), ULL(_POSIX_PIPE));
#else
  printf(FMT_SYM, STR(_POSIX_PIPE));
#endif

#if defined(_POSIX_PIPE_BUF)
  printf(FMT_ULL, STR(_POSIX_PIPE_BUF), ULL(_POSIX_PIPE_BUF));
#else
  printf(FMT_SYM, STR(_POSIX_PIPE_BUF));
#endif

#if defined(_POSIX_POLL)
  printf(FMT_ULL, STR(_POSIX_POLL), ULL(_POSIX_POLL));
#else
  printf(FMT_SYM, STR(_POSIX_POLL));
#endif

#if defined(_POSIX_PRIORITIZED_IO)
  printf(FMT_ULL, STR(_POSIX_PRIORITIZED_IO), ULL(_POSIX_PRIORITIZED_IO));
#else
  printf(FMT_SYM, STR(_POSIX_PRIORITIZED_IO));
#endif

#if defined(_POSIX_PRIORITY_SCHEDULING)
  printf(FMT_ULL, STR(_POSIX_PRIORITY_SCHEDULING), ULL(_POSIX_PRIORITY_SCHEDULING));
#else
  printf(FMT_SYM, STR(_POSIX_PRIORITY_SCHEDULING));
#endif

#if defined(_POSIX_PRIO_IO)
  printf(FMT_ULL, STR(_POSIX_PRIO_IO), ULL(_POSIX_PRIO_IO));
#else
  printf(FMT_SYM, STR(_POSIX_PRIO_IO));
#endif

#if defined(_POSIX_RAW_SOCKETS)
  printf(FMT_ULL, STR(_POSIX_RAW_SOCKETS), ULL(_POSIX_RAW_SOCKETS));
#else
  printf(FMT_SYM, STR(_POSIX_RAW_SOCKETS));
#endif

#if defined(_POSIX_READER_WRITER_LOCKS)
  printf(FMT_ULL, STR(_POSIX_READER_WRITER_LOCKS), ULL(_POSIX_READER_WRITER_LOCKS));
#else
  printf(FMT_SYM, STR(_POSIX_READER_WRITER_LOCKS));
#endif

#if defined(_POSIX_REALTIME_SIGNALS)
  printf(FMT_ULL, STR(_POSIX_REALTIME_SIGNALS), ULL(_POSIX_REALTIME_SIGNALS));
#else
  printf(FMT_SYM, STR(_POSIX_REALTIME_SIGNALS));
#endif

#if defined(_POSIX_REGEXP)
  printf(FMT_ULL, STR(_POSIX_REGEXP), ULL(_POSIX_REGEXP));
#else
  printf(FMT_SYM, STR(_POSIX_REGEXP));
#endif

#if defined(_POSIX_SAVED_IDS)
  printf(FMT_ULL, STR(_POSIX_SAVED_IDS), ULL(_POSIX_SAVED_IDS));
#else
  printf(FMT_SYM, STR(_POSIX_SAVED_IDS));
#endif

#if defined(_POSIX_SELECT)
  printf(FMT_ULL, STR(_POSIX_SELECT), ULL(_POSIX_SELECT));
#else
  printf(FMT_SYM, STR(_POSIX_SELECT));
#endif

#if defined(_POSIX_SEMAPHORES)
  printf(FMT_ULL, STR(_POSIX_SEMAPHORES), ULL(_POSIX_SEMAPHORES));
#else
  printf(FMT_SYM, STR(_POSIX_SEMAPHORES));
#endif

#if defined(_POSIX_SHARED_MEMORY_OBJECTS)
  printf(FMT_ULL, STR(_POSIX_SHARED_MEMORY_OBJECTS), ULL(_POSIX_SHARED_MEMORY_OBJECTS));
#else
  printf(FMT_SYM, STR(_POSIX_SHARED_MEMORY_OBJECTS));
#endif

#if defined(_POSIX_SHELL)
  printf(FMT_ULL, STR(_POSIX_SHELL), ULL(_POSIX_SHELL));
#else
  printf(FMT_SYM, STR(_POSIX_SHELL));
#endif

#if defined(_POSIX_SIGNALS)
  printf(FMT_ULL, STR(_POSIX_SIGNALS), ULL(_POSIX_SIGNALS));
#else
  printf(FMT_SYM, STR(_POSIX_SIGNALS));
#endif

#if defined(_POSIX_SINGLE_PROCESS)
  printf(FMT_ULL, STR(_POSIX_SINGLE_PROCESS), ULL(_POSIX_SINGLE_PROCESS));
#else
  printf(FMT_SYM, STR(_POSIX_SINGLE_PROCESS));
#endif

#if defined(_POSIX_SPAWN)
  printf(FMT_ULL, STR(_POSIX_SPAWN), ULL(_POSIX_SPAWN));
#else
  printf(FMT_SYM, STR(_POSIX_SPAWN));
#endif

#if defined(_POSIX_SPIN_LOCKS)
  printf(FMT_ULL, STR(_POSIX_SPIN_LOCKS), ULL(_POSIX_SPIN_LOCKS));
#else
  printf(FMT_SYM, STR(_POSIX_SPIN_LOCKS));
#endif

#if defined(_POSIX_SPORADIC_SERVER)
  printf(FMT_ULL, STR(_POSIX_SPORADIC_SERVER), ULL(_POSIX_SPORADIC_SERVER));
#else
  printf(FMT_SYM, STR(_POSIX_SPORADIC_SERVER));
#endif

#if defined(_POSIX_SSIZE_MAX)
  printf(FMT_ULL, STR(_POSIX_SSIZE_MAX), ULL(_POSIX_SSIZE_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_SSIZE_MAX));
#endif

#if defined(_POSIX_STREAM_MAX)
  printf(FMT_ULL, STR(_POSIX_STREAM_MAX), ULL(_POSIX_STREAM_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_STREAM_MAX));
#endif

#if defined(_POSIX_SYNCHRONIZED_IO)
  printf(FMT_ULL, STR(_POSIX_SYNCHRONIZED_IO), ULL(_POSIX_SYNCHRONIZED_IO));
#else
  printf(FMT_SYM, STR(_POSIX_SYNCHRONIZED_IO));
#endif

#if defined(_POSIX_SYNC_IO)
  printf(FMT_ULL, STR(_POSIX_SYNC_IO), ULL(_POSIX_SYNC_IO));
#else
  printf(FMT_SYM, STR(_POSIX_SYNC_IO));
#endif

#if defined(_POSIX_SYSTEM_DATABASE)
  printf(FMT_ULL, STR(_POSIX_SYSTEM_DATABASE), ULL(_POSIX_SYSTEM_DATABASE));
#else
  printf(FMT_SYM, STR(_POSIX_SYSTEM_DATABASE));
#endif

#if defined(_POSIX_SYSTEM_DATABASE_R)
  printf(FMT_ULL, STR(_POSIX_SYSTEM_DATABASE_R), ULL(_POSIX_SYSTEM_DATABASE_R));
#else
  printf(FMT_SYM, STR(_POSIX_SYSTEM_DATABASE_R));
#endif

#if defined(_POSIX_THREADS)
  printf(FMT_ULL, STR(_POSIX_THREADS), ULL(_POSIX_THREADS));
#else
  printf(FMT_SYM, STR(_POSIX_THREADS));
#endif

#if defined(_POSIX_THREAD_ATTR_STACKADDR)
  printf(FMT_ULL, STR(_POSIX_THREAD_ATTR_STACKADDR), ULL(_POSIX_THREAD_ATTR_STACKADDR));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_ATTR_STACKADDR));
#endif

#if defined(_POSIX_THREAD_ATTR_STACKSIZE)
  printf(FMT_ULL, STR(_POSIX_THREAD_ATTR_STACKSIZE), ULL(_POSIX_THREAD_ATTR_STACKSIZE));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_ATTR_STACKSIZE));
#endif

#if defined(_POSIX_THREAD_CPUTIME)
  printf(FMT_ULL, STR(_POSIX_THREAD_CPUTIME), ULL(_POSIX_THREAD_CPUTIME));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_CPUTIME));
#endif

#if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
  printf(FMT_ULL, STR(_POSIX_THREAD_PRIORITY_SCHEDULING), ULL(_POSIX_THREAD_PRIORITY_SCHEDULING));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_PRIORITY_SCHEDULING));
#endif

#if defined(_POSIX_THREAD_PRIO_INHERIT)
  printf(FMT_ULL, STR(_POSIX_THREAD_PRIO_INHERIT), ULL(_POSIX_THREAD_PRIO_INHERIT));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_PRIO_INHERIT));
#endif

#if defined(_POSIX_THREAD_PRIO_PROTECT)
  printf(FMT_ULL, STR(_POSIX_THREAD_PRIO_PROTECT), ULL(_POSIX_THREAD_PRIO_PROTECT));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_PRIO_PROTECT));
#endif

#if defined(_POSIX_THREAD_PROCESS_SHARED)
  printf(FMT_ULL, STR(_POSIX_THREAD_PROCESS_SHARED), ULL(_POSIX_THREAD_PROCESS_SHARED));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_PROCESS_SHARED));
#endif

#if defined(_POSIX_THREAD_ROBUST_PRIO_INHERIT)
  printf(FMT_ULL, STR(_POSIX_THREAD_ROBUST_PRIO_INHERIT), ULL(_POSIX_THREAD_ROBUST_PRIO_INHERIT));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_ROBUST_PRIO_INHERIT));
#endif

#if defined(_POSIX_THREAD_ROBUST_PRIO_PROTECT)
  printf(FMT_ULL, STR(_POSIX_THREAD_ROBUST_PRIO_PROTECT), ULL(_POSIX_THREAD_ROBUST_PRIO_PROTECT));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_ROBUST_PRIO_PROTECT));
#endif

#if defined(_POSIX_THREAD_SAFE_FUNCTIONS)
  printf(FMT_ULL, STR(_POSIX_THREAD_SAFE_FUNCTIONS), ULL(_POSIX_THREAD_SAFE_FUNCTIONS));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_SAFE_FUNCTIONS));
#endif

#if defined(_POSIX_THREAD_SPORADIC_SERVER)
  printf(FMT_ULL, STR(_POSIX_THREAD_SPORADIC_SERVER), ULL(_POSIX_THREAD_SPORADIC_SERVER));
#else
  printf(FMT_SYM, STR(_POSIX_THREAD_SPORADIC_SERVER));
#endif

#if defined(_POSIX_TIMEOUTS)
  printf(FMT_ULL, STR(_POSIX_TIMEOUTS), ULL(_POSIX_TIMEOUTS));
#else
  printf(FMT_SYM, STR(_POSIX_TIMEOUTS));
#endif

#if defined(_POSIX_TIMERS)
  printf(FMT_ULL, STR(_POSIX_TIMERS), ULL(_POSIX_TIMERS));
#else
  printf(FMT_SYM, STR(_POSIX_TIMERS));
#endif

#if defined(_POSIX_TRACE)
  printf(FMT_ULL, STR(_POSIX_TRACE), ULL(_POSIX_TRACE));
#else
  printf(FMT_SYM, STR(_POSIX_TRACE));
#endif

#if defined(_POSIX_TRACE_EVENT_FILTER)
  printf(FMT_ULL, STR(_POSIX_TRACE_EVENT_FILTER), ULL(_POSIX_TRACE_EVENT_FILTER));
#else
  printf(FMT_SYM, STR(_POSIX_TRACE_EVENT_FILTER));
#endif

#if defined(_POSIX_TRACE_INHERIT)
  printf(FMT_ULL, STR(_POSIX_TRACE_INHERIT), ULL(_POSIX_TRACE_INHERIT));
#else
  printf(FMT_SYM, STR(_POSIX_TRACE_INHERIT));
#endif

#if defined(_POSIX_TRACE_LOG)
  printf(FMT_ULL, STR(_POSIX_TRACE_LOG), ULL(_POSIX_TRACE_LOG));
#else
  printf(FMT_SYM, STR(_POSIX_TRACE_LOG));
#endif

#if defined(_POSIX_TYPED_MEMORY_OBJECTS)
  printf(FMT_ULL, STR(_POSIX_TYPED_MEMORY_OBJECTS), ULL(_POSIX_TYPED_MEMORY_OBJECTS));
#else
  printf(FMT_SYM, STR(_POSIX_TYPED_MEMORY_OBJECTS));
#endif

#if defined(_POSIX_TZNAME_MAX)
  printf(FMT_ULL, STR(_POSIX_TZNAME_MAX), ULL(_POSIX_TZNAME_MAX));
#else
  printf(FMT_SYM, STR(_POSIX_TZNAME_MAX));
#endif

#if defined(_POSIX_USER_GROUPS)
  printf(FMT_ULL, STR(_POSIX_USER_GROUPS), ULL(_POSIX_USER_GROUPS));
#else
  printf(FMT_SYM, STR(_POSIX_USER_GROUPS));
#endif

#if defined(_POSIX_USER_GROUPS_R)
  printf(FMT_ULL, STR(_POSIX_USER_GROUPS_R), ULL(_POSIX_USER_GROUPS_R));
#else
  printf(FMT_SYM, STR(_POSIX_USER_GROUPS_R));
#endif

#if defined(_POSIX_V6_LP64_OFF64)
  printf(FMT_ULL, STR(_POSIX_V6_LP64_OFF64), ULL(_POSIX_V6_LP64_OFF64));
#else
  printf(FMT_SYM, STR(_POSIX_V6_LP64_OFF64));
#endif

#if defined(_POSIX_V6_LPBIG_OFFBIG)
  printf(FMT_ULL, STR(_POSIX_V6_LPBIG_OFFBIG), ULL(_POSIX_V6_LPBIG_OFFBIG));
#else
  printf(FMT_SYM, STR(_POSIX_V6_LPBIG_OFFBIG));
#endif

#if defined(_POSIX_V7_ILP32_OFF32)
  printf(FMT_ULL, STR(_POSIX_V7_ILP32_OFF32), ULL(_POSIX_V7_ILP32_OFF32));
#else
  printf(FMT_SYM, STR(_POSIX_V7_ILP32_OFF32));
#endif

#if defined(_POSIX_V7_ILP32_OFFBIG)
  printf(FMT_ULL, STR(_POSIX_V7_ILP32_OFFBIG), ULL(_POSIX_V7_ILP32_OFFBIG));
#else
  printf(FMT_SYM, STR(_POSIX_V7_ILP32_OFFBIG));
#endif

#if defined(_POSIX_V7_LP64_OFF64)
  printf(FMT_ULL, STR(_POSIX_V7_LP64_OFF64), ULL(_POSIX_V7_LP64_OFF64));
#else
  printf(FMT_SYM, STR(_POSIX_V7_LP64_OFF64));
#endif

#if defined(_POSIX_V7_LPBIG_OFFBIG)
  printf(FMT_ULL, STR(_POSIX_V7_LPBIG_OFFBIG), ULL(_POSIX_V7_LPBIG_OFFBIG));
#else
  printf(FMT_SYM, STR(_POSIX_V7_LPBIG_OFFBIG));
#endif

#if defined(_POSIX_VDISABLE)
  printf(FMT_ULL, STR(_POSIX_VDISABLE), ULL(_POSIX_VDISABLE));
#else
  printf(FMT_SYM, STR(_POSIX_VDISABLE));
#endif

#if defined(_POSIX_VERSION)
  printf(FMT_ULL, STR(_POSIX_VERSION), ULL(_POSIX_VERSION));
#else
  printf(FMT_SYM, STR(_POSIX_VERSION));
#endif

#if defined(_REGEX_VERSION)
  printf(FMT_ULL, STR(_REGEX_VERSION), ULL(_REGEX_VERSION));
#else
  printf(FMT_SYM, STR(_REGEX_VERSION));
#endif

#if defined(_T_IOV_MAX)
  printf(FMT_ULL, STR(_T_IOV_MAX), ULL(_T_IOV_MAX));
#else
  printf(FMT_SYM, STR(_T_IOV_MAX));
#endif

#if defined(_XBS5_ILP32_OFF32)
  printf(FMT_ULL, STR(_XBS5_ILP32_OFF32), ULL(_XBS5_ILP32_OFF32));
#else
  printf(FMT_SYM, STR(_XBS5_ILP32_OFF32));
#endif

#if defined(_XBS5_ILP32_OFFBIG)
  printf(FMT_ULL, STR(_XBS5_ILP32_OFFBIG), ULL(_XBS5_ILP32_OFFBIG));
#else
  printf(FMT_SYM, STR(_XBS5_ILP32_OFFBIG));
#endif

#if defined(_XBS5_LP64_OFF64)
  printf(FMT_ULL, STR(_XBS5_LP64_OFF64), ULL(_XBS5_LP64_OFF64));
#else
  printf(FMT_SYM, STR(_XBS5_LP64_OFF64));
#endif

#if defined(_XOPEN_CRYPT)
  printf(FMT_ULL, STR(_XOPEN_CRYPT), ULL(_XOPEN_CRYPT));
#else
  printf(FMT_SYM, STR(_XOPEN_CRYPT));
#endif

#if defined(_XOPEN_ENH_I18N)
  printf(FMT_ULL, STR(_XOPEN_ENH_I18N), ULL(_XOPEN_ENH_I18N));
#else
  printf(FMT_SYM, STR(_XOPEN_ENH_I18N));
#endif

#if defined(_XOPEN_LEGACY)
  printf(FMT_ULL, STR(_XOPEN_LEGACY), ULL(_XOPEN_LEGACY));
#else
  printf(FMT_SYM, STR(_XOPEN_LEGACY));
#endif

#if defined(_XOPEN_REALTIME)
  printf(FMT_ULL, STR(_XOPEN_REALTIME), ULL(_XOPEN_REALTIME));
#else
  printf(FMT_SYM, STR(_XOPEN_REALTIME));
#endif

#if defined(_XOPEN_REALTIME_THREADS)
  printf(FMT_ULL, STR(_XOPEN_REALTIME_THREADS), ULL(_XOPEN_REALTIME_THREADS));
#else
  printf(FMT_SYM, STR(_XOPEN_REALTIME_THREADS));
#endif

#if defined(_XOPEN_SHM)
  printf(FMT_ULL, STR(_XOPEN_SHM), ULL(_XOPEN_SHM));
#else
  printf(FMT_SYM, STR(_XOPEN_SHM));
#endif

#if defined(_XOPEN_UNIX)
  printf(FMT_ULL, STR(_XOPEN_UNIX), ULL(_XOPEN_UNIX));
#else
  printf(FMT_SYM, STR(_XOPEN_UNIX));
#endif

#if defined(_XOPEN_VERSION)
  printf(FMT_ULL, STR(_XOPEN_VERSION), ULL(_XOPEN_VERSION));
#else
  printf(FMT_SYM, STR(_XOPEN_VERSION));
#endif

#if defined(_XOPEN_XCU_VERSION)
  printf(FMT_ULL, STR(_XOPEN_XCU_VERSION), ULL(_XOPEN_XCU_VERSION));
#else
  printf(FMT_SYM, STR(_XOPEN_XCU_VERSION));
#endif

#if defined(_XOPEN_XPG2)
  printf(FMT_ULL, STR(_XOPEN_XPG2), ULL(_XOPEN_XPG2));
#else
  printf(FMT_SYM, STR(_XOPEN_XPG2));
#endif

#if defined(_XOPEN_XPG3)
  printf(FMT_ULL, STR(_XOPEN_XPG3), ULL(_XOPEN_XPG3));
#else
  printf(FMT_SYM, STR(_XOPEN_XPG3));
#endif

#if defined(_XOPEN_XPG4)
  printf(FMT_ULL, STR(_XOPEN_XPG4), ULL(_XOPEN_XPG4));
#else
  printf(FMT_SYM, STR(_XOPEN_XPG4));
#endif


  return 0;
}
