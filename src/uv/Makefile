
uv: dns
uv_test: dns_test


INC += -I$(src_path)
uv_lflags += $(LFLAGS) $(INC)
uv_opts =

ifeq ($(NM_SYSTEM), Darwin)
	# macports default install-directory
	INC += -I/opt/local/include
	uv_lflags += -L/opt/local/lib
	uv_opts += DYLD_LIBRARY_PATH=/opt/local/lib
endif

uv_ldlibs += $(LDLIBS) -luv

dns_binout := $(bin_path)dns$(bin_ext)
dns: $(dns_binout)
$(dns_binout): $(src_path)dns/main.c
	$(LINK) $(uv_lflags) $^ $(bin_out)$@ $(uv_ldlibs)
dns_test: dns
	$(uv_opts) $(dns_binout) "www.bing.com"

