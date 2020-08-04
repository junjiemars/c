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

#include "_io_.h"
#include <assert.h>

#define FLIGHT_OP_MAP(XX)                       \
  XX(0,  QUIT,   quit)                          \
  XX(1,  QUERY,  query)                         \
  XX(2,  STORE,  store)
  
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

const char *flight_op_str(enum flight_op);

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

const char *flight_errno_name(enum flight_errno);
const char *flight_errno_desc(enum flight_errno);

#if !defined(ARRAY_SIZE)
#  define ARRAY_SIZE(a) sizeof(a) / sizeof((a)[0])
#endif

#define SERVER_PORT                "4358"

#define STORE_FLIGHT               1
#define FLIGHT_TIME_STORED         2
#define FLIGHT_TIME                3
#define FLIGHT_TIME_RESULT         4
#define FLIGHT_NOT_FOUND           5
#define ERROR_IN_INPUT             9

#include <stdint.h>
#include <stdio.h>

#define FLIGHT_NUM_SIZE            15
#define LOG(...) fprintf(stderr, __VA_ARGS__)

enum flight_time_fields
  { TF_YEAR            = 0
    , TF_MONTH         = 1
    , TF_DAY           = 2
    , TF_HOUR          = 3
    , TF_MINUTE         = 4
    , TF_MAX           = 5
  };

struct message {
  uint32_t id;
  short departure;            // 'D': departure, 'A': arrival
  short time_fields[TF_MAX];
  uint16_t time_field_set;
  char date [10 + 1];  // mm/dd/yyyy
  char time [5 + 1];   // hh:mm
  char flight_no [FLIGHT_NUM_SIZE + 1];
};


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

#endif /* end of _FLIGHT_H_ */
