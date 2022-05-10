#
# ./configure --has-libgccjit
#

ifeq ($(has_libgccjit), yes)
libgccjit:
	@echo "#skip ..."
libgccjit_test:
	@echo "#skip ..."
else

libgccjit: libgccjit_basic

libgccjit_test: libgccjit_basic_test

endif


# env
libgccjit_prefix := libgccjit
INC += $(nm_inc_opt)$(libgccjit_root) $(nm_inc_opt)$(root)/posix


# basic
libgccjit_basic_binout := $(bin_path)/$(libgccjit_prefix)_basic$(bin_ext)

libgccjit_basic: $(libgccjit_basic_binout)
libgccjit_basic_test: libgccjit_basic
	$(libgccjit_basic_binout)

$(libgccjit_basic_binout): $(libgccjit_root)/basic/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(nm_lib_opt)gccjit


# eof
