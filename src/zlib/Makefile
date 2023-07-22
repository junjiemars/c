# ./configure --has-zlib

ifeq ($(has_zlib),yes)
zlib:  zlib_hi
zlib_test: zlib_hi_test
else
zlib:
	@echo "#skip ..."
zlib_test:
	@echo "#skip ..."
endif

# env
zlib_prefix := zlib
INC += $(nm_inc_opt)$(root) $(nm_inc_opt)$(zlib_root)
INC += $(nm_inc_opt)$(root)/posix
INC += $(zlib_inc)

ifeq ($(_MEMORY_),1)
CFLAGS += $(f_sanitize)
LDFLAGS += $(f_sanitize)
endif # end of _MEMORY_

LDFLAGS += $(zlib_ldflags)
LDLIBS += $(zlib_ldlibs)


# hi
zlib_hi_binout := $(bin_path)/$(zlib_prefix)_hi$(bin_ext)

zlib_hi: $(zlib_hi_binout)
zlib_hi_test: zlib_hi
	$(zlib_hi_binout)

$(zlib_hi_binout): $(zlib_root)/hi/hi.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDFLAGS) $(LDLIBS)



# eof
