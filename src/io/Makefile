
io: basic  \
		format \
		wc
io_test: basic_test  \
				 format_test \
				 wc_test

io_prefix := io_

INC += -I$(io_root)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif


# basic I/O
basic_binout := $(bin_path)$(io_prefix)basic$(bin_ext)
basic_stream_binout := $(bin_path)$(io_prefix)basic_stream$(bin_ext)

basic: $(basic_binout) $(basic_stream_binout)
basic_test: basic
	echo "Hello, basic IO" | $(basic_binout)
	echo "Hello, basic IO" | $(basic_stream_binout)

$(basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(basic_stream_binout): $(io_root)basic/bs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
format_binout := $(bin_path)$(io_prefix)format$(bin_ext)

format: $(format_binout)
format_test: format
	$(format_binout)

$(format_binout): $(io_root)format/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wc
wc_binout := $(bin_path)$(io_prefix)wc$(bin_ext)
wc_cppout := $(tmp_path)$(io_prefix)wc$(cpp_ext)


wc: $(wc_binout)
wc_test: wc
	$(wc_binout) -h
	$(wc_binout) -c $(CURDIR)/Makefile $(CURDIR)/src/io/wc/wc.c
	$(wc_binout) -l $(CURDIR)/Makefile $(CURDIR)/src/io/wc/wc.c

$(wc_binout): $(wc_cppout) $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(wc_cppout): $(io_root)wc/wc.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@
