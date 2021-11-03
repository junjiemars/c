#
# ./configure --has-net
#


net: net_dns                                    \
     net_mac

net_test: net_dns_test                          \
          net_mac_test


# env
net_prefix := net

INC += $(nm_inc_opt)$(net_root)

ifeq ($(NM_SYSTEM), WinNT)
	INC += $(nm_inc_opt)$(root)/posix
	getopt_c := $(root)/posix/getopt.c
endif

ifeq ($(NM_SYSTEM), Linux)
	CFLAGS += -D_POSIX_SOURCE -D_GNU_SOURCE
endif

ifeq ($(_MEMORY_), 1)
	CFLAGS += $(f_sanitize)
endif # end of _MEMORY_



# dns
net_dns_client_binout := $(bin_path)/$(net_prefix)_dns_client$(bin_ext)

net_dns_test: net_dns_client_test
net_dns_client_test: $(net_dns_client_binout)
	$(net_dns_client_binout)
	$(net_dns_client_binout) -qgithub.com -s74.82.42.42
	$(net_dns_client_binout) -qwww.reddit.com -s74.82.42.42
	$(net_dns_client_binout) -qwww.bing.com -s74.82.42.42
	$(net_dns_client_binout) -qwww.baidu.com -s74.82.42.42
	$(net_dns_client_binout) -qwww.google.com -s74.82.42.42
	$(net_dns_client_binout) -qgithub.com -s8.8.4.4 -t5 --out=$(CURDIR)/$(bin_path)/github.bin
	$(net_dns_client_binout) -qwww.reddit.com -s8.8.4.4 --out=$(bin_path)/reddit.bin
	$(net_dns_client_binout) -qwww.bing.com -s8.8.4.4 --out=$(CURDIR)/$(bin_path)/bing.bin
	$(net_dns_client_binout) -qwww.bing.com -s8.8.4.4 -tCNAME --out=$(CURDIR)/$(bin_path)/bing.bin
	$(net_dns_client_binout) -qwww.baidu.com -s8.8.4.4 --out=$(CURDIR)/$(bin_path)/bing.bin
	$(net_dns_client_binout) -qwww.google.com -s8.8.4.4 --out=$(CURDIR)/$(bin_path)/google.bin


$(net_dns_client_binout): $(net_root)/dns/c.c $(getopt_c)
	$(CC) $(INC) $(CPPFLAGS) $(CFLAGS) $^ $(bin_out)$@


# mac
net_mac_binout := $(bin_path)/$(net_prefix)_mac$(bin_ext)

net_mac: $(net_mac_binout)
net_mac_test: net_mac
	$(net_mac_binout)

$(net_mac_binout): $(net_root)/mac/mac.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
