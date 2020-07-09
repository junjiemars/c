#include "_uv_.h"
#include <stdio.h>

void
test_neti(void) {
  char buf[512];
  uv_interface_address_t *info;
  int count, i;

  uv_interface_addresses(&info, &count);
  i = count;

  while (i--) {
    uv_interface_address_t inet = info[i];
    if (inet.is_internal) {
      continue;
    }

    if (AF_INET == inet.address.address4.sin_family) {
      uv_ip4_name(&inet.address.address4, buf, sizeof(buf));
    } else if (AF_INET6 == inet.address.address4.sin_family) {
      uv_ip6_name(&inet.address.address6, buf, sizeof(buf));
    } else {
      continue;
    }
    fprintf(stderr, "%s\n", buf);
  }

  uv_free_interface_addresses(info, count);
}

int
main(void) {
  test_neti();
}
