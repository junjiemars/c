#
# ./configure --has-uv --with-std=no
# 
#

uv: uv_dns																			\
    uv_neti																			\
    uv_parser																		\
    uv_httpd

uv_test: uv_dns_test														\
         uv_neti_test														\
         uv_http_parser													\
         uv_httpd_test

uv_prefix := uv

INC += -I$(uv_root)
CFLAGS += $(shell pkg-config --cflags libuv)
LFLAGS += $(shell pkg-config --libs libuv)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif

# dns
dns_binout := $(bin_path)$(uv_prefix)_dns$(bin_ext)

uv_dns: $(dns_binout)
uv_dns_test: uv_dns
	$(dns_binout) "www.bing.com"

$(dns_binout): $(uv_root)dns/d1.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LFLAGS)

# neti
neti_binout := $(bin_path)$(uv_prefix)_neti$(bin_ext)

uv_neti: $(neti_binout)
uv_neti_test: uv_neti
	$(neti_binout)

$(neti_binout): $(uv_root)neti/neti.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LFLAGS)

# parser
uv_parser_objout := $(lib_path)$(uv_prefix)_parser$(obj_ext)
uv_parser_binout := $(bin_path)$(uv_prefix)_parser$(bin_ext)

uv_parser: $(uv_parser_binout)
uv_parser_test: uv_parser
	$(uv_parser_binout)

$(uv_parser_objout): $(uv_root)parser/http_parser.c $(uv_root)parser/http_parser.h
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $< $(obj_out)$@

$(uv_parser_binout): $(uv_parser_objout) $(uv_root)parser/test.c
	$(CC) $(CFLAGS) $(INC) $? $(bin_out)$@

# httpd
uv_httpd_binout := $(bin_path)$(uv_prefix)_httpd$(bin_ext)

uv_httpd: $(uv_httpd_binout)
uv_httpd_test: uv_httpd
	$(uv_httpd_binout) -H

$(uv_httpd_binout): $(uv_root)httpd/h.c $(uv_parser_objout) $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $? $(bin_out)$@ $(LFLAGS)
