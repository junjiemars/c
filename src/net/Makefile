
net: dns 
net_test: dns_test

INC += -I$(src_path)
#LFLAGS += -lsocket -lnsl

dns_binout := $(bin_path)dns$(bin_ext)
dns: $(dns_binout)
$(dns_binout): $(src_path)dns/dns.c
	$(CC) $(INC) $(LFLAGS) $^ $(bin_out)$@
dns_test: dns 
	$(dns_binout) -4 -s'http' www.bing.com

