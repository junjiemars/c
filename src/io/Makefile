
io: io_basic \
		io_format \
		io_wc
io_test: io_basic_test \
				 io_format_test \
				 io_wc_test

INC += -I$(io_root)

# basic I/O
basic_binout := $(bin_path)io_basic$(bin_ext)
basic_stream_binout := $(bin_path)io_basic_stream$(bin_ext)

io_basic: $(basic_binout) $(basic_stream_binout)
io_basic_test: io_basic
	echo "Hello, basic IO" | $(basic_binout)
	echo "Hello, basic IO" | $(basic_stream_binout)

$(basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(basic_stream_binout): $(io_root)basic/bs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
format_binout := $(bin_path)io_format$(bin_ext)

io_format: $(format_binout)
io_format_test: io_format
	$(format_binout)

$(format_binout): $(io_root)format/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wc
wc_binout := $(bin_path)io_wc$(bin_ext)

io_wc: $(wc_binout)
io_wc_test: io_wc
	$(wc_binout) $(CURDIR)/Makefile

$(wc_binout): $(io_root)wc/wc.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
