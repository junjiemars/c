
io: basic \
		format
io_test: basic_test \
				 format_test

INC += -I$(io_root)

# basic I/O
basic_binout := $(bin_path)io_basic$(bin_ext)
basic_stream_binout := $(bin_path)io_basic_stream$(bin_ext)

basic: $(basic_binout) $(basic_stream_binout)
basic_test: basic
	echo "Hello, basic IO" | $(basic_binout)
	echo "Hello, basic IO" | $(basic_stream_binout)

$(basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(basic_stream_binout): $(io_root)basic/bs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
format_binout := $(bin_path)io_format$(bin_ext)

format: $(format_binout)
format_test: format
	$(format_binout)

$(format_binout): $(io_root)format/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

