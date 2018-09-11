
net: dns 
net_test: dns_test

net_prefix := net

INC += -I$(net_root)
ifeq ($(NM_SYSTEM), WinNT)
	INC += -I$(root)posix
	getopt_c := $(root)posix/getopt.c
endif

ifeq ($(NM_SYSTEM), Linux)
	CFLAGS += -D_POSIX_SOURCE -D_GNU_SOURCE
endif

# dns
dns_binout := $(bin_path)$(net_prefix)_dns$(bin_ext)

dns: $(dns_binout)
$(dns_binout): $(net_root)dns/dns.c $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@
dns_test: dns
	$(dns_binout)
	$(dns_binout) www.google.com
	$(dns_binout) www.bing.com
