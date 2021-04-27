#
# ./configure --without-debug --has-ld
#

ld: ld_entry																		\
    ld_nostartfiles															\
    ld_nostdlib																	\
    ld_static

ld_test: ld_entry_test													\
         ld_nostartfiles_test										\
         ld_nostdlib_test												\
         ld_static_test


ld_prefix := ld

INC += -I$(ld_root)


# entry
ld_entry_binout := $(bin_path)/$(ld_prefix)_entry$(bin_ext)

ifeq ("", $(ld_entry_opt))
ld_entry:
	@echo "#skip ld_entry_test ..."
ld_entry_test: ld_entry
else
ld_entry: $(ld_entry_binout)
ld_entry_test: ld_entry
	$(ld_entry_binout) "abc"

endif

$(ld_entry_binout): $(ld_root)/entry/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_entry_opt)


# nostartfiles
ld_nostartfiles_binout := $(bin_path)/$(ld_prefix)_nostartfiles$(bin_ext)

ifeq ("NO", $(ld_nostartfiles_opt))
ld_nostartfiles:
	@echo "#skip ld_nostartfiles_test ..."
ld_nostartfiles_test: ld_nostartfiles
else
ld_nostartfiles: $(ld_nostartfiles_binout)
ld_nostartfiles_test: ld_nostartfiles
	$(ld_nostartfiles_binout)
endif

$(ld_nostartfiles_binout): $(ld_root)/nostartfiles/nosfs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_nostartfiles_opt)


# static
ld_static_binout := $(bin_path)/$(ld_prefix)_static$(bin_ext)

ifeq ("NO", $(ld_static_opt))
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

ifeq ("NO", $(ld_nostdlib_opt))
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
