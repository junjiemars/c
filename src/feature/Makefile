# ./configure --without-debug --has-lang

ifeq ($(NM_SYSTEM), Linux)
# man 7 feature_test_macros
feature: gcc_test_macro
feature_test:  gcc_test_macro_test

feature_prefix := feature
INC += -I$(feature_root)

# gcc test macro
gcc_tm_binout := $(bin_path)$(feature_prefix)_gcc_test_macro$(bin_ext)
gcc_test_macro: $(gcc_tm_binout)
gcc_test_macro_test: gcc_test_macro
	$(gcc_tm_binout)

$(gcc_tm_binout): $(feature_root)gcc/gcc_tm.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
endif