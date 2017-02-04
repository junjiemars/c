
# assert at runtime:
# ./configure --without-debug --has-assert

assert_binout := $(bin_path)assert$(bin_ext)

assert: $(assert_binout)

$(assert_binout): $(src_path)a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

assert_test: assert
	-$(assert_binout) 0
	-$(assert_binout) 100
	-$(assert_binout) 49
