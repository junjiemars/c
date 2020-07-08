# ./configure --has-feature

ifeq ($(CC_NAME),gcc)
  include $(CURDIR)/src/feature/gcc/Makefile
else ifeq ($(CC_NAME),clang)
  include $(CURDIR)/src/feature/clang/Makefile
endif

feature: feature_inline
feature_test: feature_inline_test

feature_prefix := feature
INC += -I$(feature_root)

# inline
f_noinline_binout := $(bin_path)$(feature_prefix)_inline_no$(bin_ext)
f_always_inline_binout := $(bin_path)$(feature_prefix)_inline_always$(bin_ext)

feature_inline: $(f_noinline_binout)						\
                $(f_always_inline_binout)
feature_inline_test: feature_inline
	$(f_noinline_binout) 100
	$(f_always_inline_binout) 100

$(f_noinline_binout): $(feature_root)inline/noinline.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(f_always_inline_binout): $(feature_root)inline/always.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

