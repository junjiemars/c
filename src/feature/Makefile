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
f_inline_binout := $(bin_path)$(feature_prefix)_inline$(bin_ext)

feature_inline: $(f_inline_binout)
feature_inline_test: feature_inline
	$(f_inline_binout) 100

$(f_inline_binout): $(feature_root)inline/inline.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
