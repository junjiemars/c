# -*- mode:makefile-gmake -*-
#
# ./configure --has-uv
#
# https://github.com/libuv/libuv
#

uv: uv_dns                                      \
    uv_neti                                     \
    uv_parser                                   \
    uv_httpd

uv_test: uv_dns_test                            \
         uv_neti_test                           \
         uv_parser_test                         \
         uv_httpd_test



# env
uv_prefix := uv

INC += $(nm_inc_opt)$(uv_root) $(nm_inc_opt)$(root)/posix
INC += $(inc_uv)
LDLIBS += $(ldflags_uv)

ifeq (msvc, $(CC_NAME))
getopt_c := $(root)posix/getopt.c
endif



# dns
uv_dns_binout := $(bin_path)/$(uv_prefix)_dns$(bin_ext)

ifeq (YES, $(has_libuv))
uv_dns: $(uv_dns_binout)
uv_dns_test: uv_dns
	$(uv_dns_binout) "www.bing.com"
else
uv_dns:
	@echo "#skip $@ ..."
uv_dns_test: uv_dns
	@echo "#skip $@ ..."
endif

$(uv_dns_binout): $(uv_root)/dns/d1.c
	$(CC) $(INC) $(CFLAGS) $(bin_out)$@ $^ $(LDLIBS)



# neti
uv_neti_binout := $(bin_path)/$(uv_prefix)_neti$(bin_ext)

ifeq (YES,$(has_libuv))
uv_neti: $(uv_neti_binout)
uv_neti_test: uv_neti
	$(uv_neti_binout)
else
uv_neti:
	@echo "#skip $@"
uv_neti_test: uv_neti
	@echo "#skip $@"
endif

$(uv_neti_binout): $(uv_root)/neti/neti.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)



# parser
uv_parser_objout := $(lib_path)/$(uv_prefix)_parser$(obj_ext)
uv_parser_binout := $(bin_path)/$(uv_prefix)_parser$(bin_ext)

ifeq (YES, $(has_libuv))
uv_parser: $(uv_parser_binout)
uv_parser_test: uv_parser
	$(uv_parser_binout)
else
uv_parser:
	@echo "#skip $@ ..."
uv_parser_test: uv_parser
	@echo "#skip $@ ..."
endif

$(uv_parser_objout): $(uv_root)/parser/http_parser.c  \
                     $(uv_root)/parser/http_parser.h
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $(obj_out)$@ $<

$(uv_parser_binout): $(uv_parser_objout) \
                     $(uv_root)/parser/test.c
	$(CC) $(CFLAGS) $(INC) $? $(bin_out)$@



# httpd
uv_httpd_binout := $(bin_path)/$(uv_prefix)_httpd$(bin_ext)

ifeq (YES, $(has_libuv))
uv_httpd: $(uv_httpd_binout)
uv_httpd_test: uv_httpd $(uv_root)/httpd/cgi.c
	@cp $(uv_root)/httpd/cgi.c $(bin_path)/
	$(uv_httpd_binout) -H
else
uv_httpd:
	@echo "#skip $@"
uv_httpd_test: uv_httpd
	@echo "#skip $@"
endif

$(uv_httpd_binout): $(uv_root)/httpd/h.c \
                    $(uv_parser_objout) \
                    $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $? $(bin_out)$@ $(LDLIBS)




# eof
