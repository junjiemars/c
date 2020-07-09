#
# ./configure --has-uv
#

uv: uv_dns
uv_test: uv_dns_test

uv_prefix := uv

INC += -I$(uv_root)
CFLAGS += $(shell pkg-config --cflags libuv)
LFLAGS += $(shell pkg-config --libs libuv)

# dns
uv_dns_binout := $(bin_path)$(uv_prefix)_dns$(bin_ext)

uv_dns: $(uv_dns_binout)
uv_dns_test: uv_dns
	$(uv_dns_binout) "www.bing.com"

$(uv_dns_binout): $(uv_root)dns/d1.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LFLAGS)

