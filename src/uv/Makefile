#
# ./configure --has-uv --with-std=no
#

uv: uv_dns																			\
    uv_neti
uv_test: uv_dns_test														\
         uv_neti_test

uv_prefix := uv

INC += -I$(uv_root)
CFLAGS += $(shell pkg-config --cflags libuv)
LFLAGS += $(shell pkg-config --libs libuv)

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
