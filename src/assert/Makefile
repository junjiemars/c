
# assert at runtime
# static_assert at compile time
# ./configure --without-debug --has-assert

assert_cflags = $(CFLAGS)
ifeq ((NM_SYSTEM), Linux)
	assert_cflags += -std=c11
endif

assert_binout := $(bin_path)assert$(bin_ext)

assert: $(assert_binout)

$(assert_binout): $(src_path)a.c
	$(CC) $(assert_cflags) $(INC) $^ $(bin_out)$@

assert_test: assert
	-$(assert_binout) 0
	-$(assert_binout) 100
	-$(assert_binout) 49
