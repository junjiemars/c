#ifndef _SEL_H_
#define _SEL_H_

#include "_io_.h"

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

struct message {
  int32_t message_id;
  char flight_no [FLIGHT_NUM_SIZE + 1];
  char departure [1 + 1]; // 'D': departure, 'A': arrival
  char date [10 + 1]; // dd/mm/yyyy
  char time [5 + 1];   // hh:mm
};


#endif /* end of _SEL_H_ */
