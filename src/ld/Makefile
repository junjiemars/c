#
# ./configure --without-debug --has-ld
#

ld: ld_static																		\
    ld_nostdlib

ld_test: ld_static															\
         ld_nostdlib_test

ld_prefix := ld
INC += -I$(ld_root)


# static
ld_static_binout := $(bin_path)/$(ld_prefix)_static$(bin_ext)

ifeq ("", $(ld_static_opt))
ld_static:
	@echo "#skip ld_static_test ..."
ld_static_test: ld_static
else
ld_static: $(ld_static_binout)
ld_static_test: ld_static
	$(ld_static_binout) "abc"
endif

$(ld_static_binout): $(ld_root)/static/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_static_opt)


# nostdlib
ld_nostdlib_binout := $(bin_path)/$(ld_prefix)_nostdlib$(bin_ext)

ifeq ("", $(ld_nostdlib_opt))
ld_nostdlib: $(ld_nostdlib_binout)
	@echo "#skip ld_nostdlib_test ..."
ld_nostdlib_test: ld_nostdlib
	$(ld_nostdlib_binout)
else
ld_nostdlib: $(ld_nostdlib_binout)
ld_nostdlib_test: ld_nostdlib
	$(ld_nostdlib_binout)
endif

$(ld_nostdlib_binout): $(ld_root)/nostdlib/n.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_nostdlib_opt)


# eof
