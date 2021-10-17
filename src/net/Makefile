#
# ./configure --has-net
#


net: net_dns                                    \
     net_mac                                    \
     net_http_server

net_test: net_dns_test                          \
          net_mac_test                          \
          net_http_server_test


# env
net_prefix := net

INC += -I$(net_root)

ifeq ($(NM_SYSTEM), WinNT)
	INC += -I$(root)posix
	getopt_c := $(root)posix/getopt.c
endif

ifeq ($(NM_SYSTEM), Linux)
	CFLAGS += -D_POSIX_SOURCE -D_GNU_SOURCE
endif

ifeq ($(CC_NAME), msvc)
  no_struct_align := -Zp1
else
	no_struct_align := -fpack-struct=1
endif


# dns
net_dns_simple_binout := $(bin_path)/$(net_prefix)_net_dns_simple$(bin_ext)
net_dns_query_binout := $(bin_path)/$(net_prefix)_net_dns_query$(bin_ext)

net_dns: $(net_dns_simple_binout)               \
         $(net_dns_query_binout)
net_dns_test: net_dns_simple_test net_dns_query_test
net_dns_simple_test: $(net_dns_simple_binout)
	$(net_dns_simple_binout) www.google.com
	$(net_dns_simple_binout) www.bing.com
net_dns_query_test: $(net_dns_query_binout)
	$(net_dns_query_binout)
	$(net_dns_query_binout) -p53 @8.8.4.4 -qwww.bing.com

$(net_dns_simple_binout): $(net_root)/dns/simple.c $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@

$(net_dns_query_binout): $(net_root)/dns/query.c $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $(no_struct_align) $^ $(bin_out)$@


# mac
net_mac_binout := $(bin_path)/$(net_prefix)_net_mac$(bin_ext)

net_mac: $(net_mac_binout)
net_mac_test: net_mac
	$(net_mac_binout)

$(net_mac_binout): $(net_root)/mac/mac.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# http-server

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif

http_parser_root := $(net_root)/http-server/http-parser
http_parser_out := $(http_parser_root)/http_parser.o

libuv_root := $(net_root)http-server/libuv
libuv_out := $(libuv_root)/.libs/libuv.a

http_server_inc := $(INC) -I$(http_parser_root) -I$(libuv_root)/include/

$(http_parser_out): $(http_parser_root)/Makefile
	$(MAKE) -C $(http_parser_root) http_parser.o

$(libuv_root)/configure: $(libuv_root)/autogen.sh
	cd $(libuv_root) && ./autogen.sh
$(libuv_root)/Makefile: $(libuv_root)/configure
	cd $(libuv_root) && ./configure
$(libuv_out): $(libuv_root)/Makefile
	$(MAKE) -C $(libuv_root) libuv.la

net_http_server_binout := $(bin_path)/$(net_prefix)_http_server$(bin_ext)

net_http_server: $(net_http_server_binout)
net_http_server_test: net_http_server
	$(net_http_server_binout) --help

ifeq ($(NM_SYSTEM),Linux)
LDLIBS = -pthread
else ifeq ($(NM_SYSTEM),Darwin)
LDLIBS =
else
LDLIBS =
endif

$(net_http_server_binout): $(getopt_c) \
													 $(net_root)http-server/ws.c \
													 $(http_parser_out) \
												   $(libuv_out)
	$(CC) $(CFLAGS) $(http_server_inc) $^ $(bin_out)$@ $(LDLIBS)


# eof
