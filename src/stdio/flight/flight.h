#ifndef _FLIGHT_H_
#define _FLIGHT_H_


#ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
#endif
#ifndef __USE_MISC
#  define __USE_MISC
#endif
#ifndef __USE_GNU
#  define __USE_GNU
#endif
#ifndef __USE_XOPEN2K
#  define __USE_XOPEN2K
#endif


#include "_stdio_.h"
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>


#if (DARWIN)
#  if !defined(MSG_NOSIGNAL)
#    define MSG_NOSIGNAL 0
#  endif
#endif


#define FLIGHT_OP_MAP(XX)                       \
  XX(0,  QUIT,       quit)                      \
  XX(1,  QUERY,      query)                     \
  XX(2,  STORE,      store)

enum flight_op
  {
#define XX(num, name, string) FLIGHT_##name = num,
   FLIGHT_OP_MAP(XX)
#undef XX
  };

static const char *flight_op_strings[] =
  {
#define XX(num, name, string) #string,
   FLIGHT_OP_MAP(XX)
#undef XX
  };


#define FLIGHT_ERRNO_MAP(XX)                    \
  XX(OK,               "success")               \
  XX(NO_FOUND,         "no found")              \
  XX(INVALID_INPUT,    "invalid input")

#define FLIGHT_ERRNO_GEN(n, s) FE_##n,
enum flight_errno
  {
   FLIGHT_ERRNO_MAP(FLIGHT_ERRNO_GEN)
  };
#undef FLIGHT_ERRNO_GEN

#define FLIGHT_STRERROR_GEN(n, s) { "FE_" #n, s },
static struct {
  const char *name;
  const char *desc;
} flight_strerror_tab[] = {
  FLIGHT_ERRNO_MAP(FLIGHT_STRERROR_GEN)
};
#undef FLIGHT_STRERROR_GEN


#define FLIGHT_NUM_SIZE            15
#define FLIGHT_TIME_LEN            32

struct message_s {
  unsigned int id;
  int departure;
  time_t epoch;
  char ctime[32];
  char flight_no [FLIGHT_NUM_SIZE + 1];
};

#define TIME_FIELD_MAX(tm) (&(tm).tm_year - &(tm).tm_sec)

#if !defined(ARRAY_SIZE)
#  define ARRAY_SIZE(a) sizeof(a) / sizeof((a)[0])
#endif

#define LOG(...) fprintf(stderr, __VA_ARGS__)
#define LOGX() perror("!panic")
#define LOGM(id, ad, tm, ...)                   \
  LOG("Flight Info:\n"                          \
      "  Flight No: %u\n"                       \
      "  A(rrival)/D(eparture): %c\n"           \
      "  Date: %s\n"                            \
      , (id)                                    \
      , (ad)                                    \
      , (tm))


#define SERVER_PORT                "4358"

const char *flight_errno_name(enum flight_errno);
const char *flight_errno_desc(enum flight_errno);
const char *flight_op_str(enum flight_op);
char *strstrip(char * const);
int check_departure(int c);
struct message_s *hton_message(struct message_s *const);
struct message_s *ntoh_message(struct message_s *const);

const char *
flight_op_str(enum flight_op op) {
  assert((size_t)op < ARRAY_SIZE(flight_op_strings));
  return flight_op_strings[op];
}

const char *
flight_errno_name(enum flight_errno err) {
  assert((size_t)err < ARRAY_SIZE(flight_strerror_tab));
  return flight_strerror_tab[err].name;
}

const char *
flight_errno_desc(enum flight_errno err) {
  assert((size_t)err < ARRAY_SIZE(flight_strerror_tab));
  return flight_strerror_tab[err].desc;
}

int
check_departure(int c) {
  int u = toupper(c);
  return 'A' == u || 'D' == u;
}

char *
strstrip(char * const s) {
  assert(s);
  size_t size;
  char *end;
  char *s1 = s;

  size = strlen(s1);

  if (!size) {
    return s;
  }

  end = s1 + size - 1;
  while (end >= s1 && isspace(*end)) {
    end--;
  }
  *(end + 1) = '\0';

  while (*s1 && isspace(*s1)) {
    s1++;
  }

  return s1;
}

struct message_s *
hton_message(struct message_s *const m) {
  assert(m);
  m->id = htonl(m->id);
  m->departure = htonl(m->departure);
  m->epoch = htonl(m->epoch);
  return m;
}

struct message_s *
ntoh_message(struct message_s *const m) {
  assert(m);
  m->id = ntohl(m->id);
  m->departure = ntohl(m->departure);
  m->epoch = ntohl(m->epoch);
  return m;
}

#endif /* end of _FLIGHT_H_ */
