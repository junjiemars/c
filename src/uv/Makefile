
uv: dns
uv_test: dns_test

INC += -I$(src_path)

uv_lflags += $(LFLAGS) $(INC) 
uv_ldlibs += $(LDLIBS) -luv

dns_binout := $(bin_path)dns$(bin_ext)
dns: $(dns_binout)
$(dns_binout): $(src_path)dns/main.c
	$(LINK) $(uv_lflags) $^ $(bin_out)$@ $(uv_ldlibs)
dns_test: dns
	$(dns_binout) "www.bing.com"

