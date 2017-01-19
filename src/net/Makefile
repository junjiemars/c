
net: dns 
net_test: dns_test

INC += -I$(src_path)
ifeq ($(NM_SYSTEM), Linux)
	CFLAGS += -D_POSIX_SOURCE
endif

dns_binout := $(bin_path)dns$(bin_ext)
dns: $(dns_binout)
$(dns_binout): $(src_path)dns/dns.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@
dns_test: dns 
	$(dns_binout) -4 -s'http' www.bing.com

