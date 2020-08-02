#include "_lang_.h"
#include <stddef.h>

#if MSVC
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif


int
main(void) {
  
  return 0;
}

void
test_size_type(void) {
  size_t st = 0x11223344;
  ssize_t sst = 0x11223344;
  
  printf("%20s=%02zu, %020zu, 0x%016lx\n",
         "sizeof(size_t)", sizeof(st), st, *(unsigned long*)&st);
  printf("%20s=%02zu, %020zi, 0x%016lx\n",
         "sizeof(ssize_t)", sizeof(sst), sst, *(unsigned long*)&sst);
}
