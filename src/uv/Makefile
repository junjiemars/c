#
# ./configure --has-uv --with-std=no
#

uv: uv_dns																			\
    uv_neti																			\
    uv_httpd
uv_test: uv_dns_test														\
         uv_neti_test														\
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

# httpd
uv_httpd_binout := $(bin_path)$(uv_prefix)_httpd$(bin_ext)

uv_httpd: $(uv_httpd_binout)
uv_httpd_test: uv_httpd
	$(uv_httpd_binout) -H
	# $(uv_httpd_binout) --host=0.0.0.0 --port=9393 --head=@$(CURDIR)/httpd/header --file=@$(CURDIR)/httpd/h.c

$(uv_httpd_binout): $(uv_root)httpd/h.c $(getopt_c)
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LFLAGS)

# neti
neti_binout := $(bin_path)$(uv_prefix)_neti$(bin_ext)

uv_neti: $(neti_binout)
uv_neti_test: uv_neti
	$(neti_binout)

$(neti_binout): $(uv_root)neti/neti.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LFLAGS)
