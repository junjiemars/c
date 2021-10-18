#include "_net_.h"
#include <stdio.h>
#include <string.h>

void print_mac_address(void);



#if (LINUX) || (DARWIN)

#include <ifaddrs.h>
#include <netpacket/packet.h>

void
print_mac_address(void)
{
  struct ifaddrs  *ifaddr  =  NULL;

  if (getifaddrs(&ifaddr) == -1)
    {
      perror("getifaddrs");
      return;
    }

  for (struct ifaddrs *p = ifaddr; p != NULL; p = p->ifa_next)
    {
      if ((p->ifa_addr) && (p->ifa_addr->sa_family == AF_PACKET))
        {
          struct sockaddr_ll *s = (struct sockaddr_ll*) p->ifa_addr;

          printf("%-16s ", p->ifa_name);

          for (int i = 0; i < s->sll_halen; i++)
            {
              printf("%02x%c",
                     (s->sll_addr[i]),
                     (i+1 != s->sll_halen) ? ':' : '\n');
            }
        }
    }
  freeifaddrs(ifaddr);
}

#else

void
print_mac_address(void)
{
  /* void */
}

#endif

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  print_mac_address();

	return 0;
}
