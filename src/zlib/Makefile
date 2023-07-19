# ./configure --has-zlib

zlib:  zlib_hi

zlib_test: zlib_hi_test

# env
zlib_prefix := zlib
INC += $(nm_inc_opt)$(root) $(nm_inc_opt)$(zlib_root) $(nm_inc_opt)$(root)/posix

zlib_cc_opt =
zlib_ld_opt =

ifeq (1, $(_MEMORY_))
zlib_cc_opt += $(f_sanitize)
zlib_ld_opt += $(f_sanitize)
endif # end of _MEMORY_


# hi
zlib_hi_binout := $(bin_path)/$(zlib_prefix)_hi$(bin_ext)

zlib_hi: $(zlib_hi_binout)
zlib_hi_test: zlib_hi
	$(zlib_hi_binout)

$(zlib_hi_binout): $(zlib_root)/hi/hi.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
