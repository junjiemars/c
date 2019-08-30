#include <_net_.h>
#include <stdio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>


void
get_mac_address(const char *interface) {
	int sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (-1 == sd) {
		return;
	}
	struct ifreq ifr;
	memset(&ifr, 0, sizeof(ifr));
	snprintf(ifr.ifr_name, IFNAMSIZ, "%s", interface);
	if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0) {
		return;
	}
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);
	return 0;
}
