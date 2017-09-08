
io: basic
io_test: basic_test

INC += -I$(io_root)

# basic I/O
basic_binout := $(bin_path)basic$(bin_ext)

basic: $(basic_binout)
basic_test: basic
	echo "Hello, basic IO" | $(basic_binout)

$(basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

