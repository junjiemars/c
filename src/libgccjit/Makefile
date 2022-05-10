#
# ./configure --has-libgccjit
#

ifneq ($(has_libgccjit), yes)
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
libgccjit_basic_hi_binout := $(bin_path)/$(libgccjit_prefix)_basic_hi$(bin_ext)
libgccjit_basic_sqr_binout := $(bin_path)/$(libgccjit_prefix)_basic_sqr$(bin_ext)

libgccjit_basic: $(libgccjit_basic_hi_binout)   \
                 $(libgccjit_basic_sqr_binout)
libgccjit_basic_test: libgccjit_basic_hi_test   \
                      libgccjit_basic_sqr_test

libgccjit_basic_hi_test: $(libgccjit_basic_hi_binout)
	$<

libgccjit_basic_sqr_test: $(libgccjit_basic_sqr_binout)
	$< 10

$(libgccjit_basic_hi_binout): $(libgccjit_root)/basic/hi.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(nm_lib_opt)gccjit

$(libgccjit_basic_sqr_binout): $(libgccjit_root)/basic/sqr.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(nm_lib_opt)gccjit


# eof
