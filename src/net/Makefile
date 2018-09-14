
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
dns_simple_binout := $(bin_path)$(net_prefix)_dns_simple$(bin_ext)
dns_query_binout := $(bin_path)$(net_prefix)_dns_query$(bin_ext)

dns: $(dns_simple_binout) $(dns_query_binout)
dns_test: dns
	$(dns_simple_binout) www.google.com
	$(dns_simple_binout) www.bing.com
	$(dns_query_binout)
	$(dns_query_binout) -p32000
	$(dns_query_binout) -p32000 -qwww.google.com @8.8.4.4
	$(dns_query_binout) -p32000 @8.8.4.4 -qwww.bing.com


$(dns_simple_binout): $(net_root)dns/simple.c $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@

$(dns_query_binout): $(net_root)dns/query.c $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@



