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

ifeq ($(CC_NAME), msvc)
  no_struct_align := -Zp1
else
	no_struct_align := -fpack-struct=1
endif


ifeq ($(_MEMORY_), 1)
	CFLAGS += $(f_sanitize)
endif # end of _MEMORY_



# dns
net_dns_raw_binout := $(bin_path)/$(net_prefix)_dns_raw$(bin_ext)

net_dns_test: net_dns_raw_test
net_dns_raw_test: $(net_dns_raw_binout)
	$(net_dns_raw_binout)
	$(net_dns_raw_binout) -qgithub.com -s74.82.42.42
	$(net_dns_raw_binout) -qwww.reddit.com -s74.82.42.42
	$(net_dns_raw_binout) -qwww.baidu.com -s74.42.42.42 -t5
	$(net_dns_raw_binout) -qwww.google.com -s8.8.4.4 -t5


$(net_dns_raw_binout): $(net_root)/dns/raw.c $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $(no_struct_align) $^ $(bin_out)$@


# mac
net_mac_binout := $(bin_path)/$(net_prefix)_mac$(bin_ext)

net_mac: $(net_mac_binout)
net_mac_test: net_mac
	$(net_mac_binout)

$(net_mac_binout): $(net_root)/mac/mac.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
