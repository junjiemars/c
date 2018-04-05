
io: basic  \
		format \
    flush  \
		scan   \
		wc
io_test: basic_test  \
				 format_test \
         flush_test  \
				 scan_test   \
				 wc_test

io_prefix := io

INC += -I$(io_root)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif


# basic I/O
basic_binout := $(bin_path)$(io_prefix)_basic$(bin_ext)
basic_stream_binout := $(bin_path)$(io_prefix)_basic_stream$(bin_ext)

basic: $(basic_binout) $(basic_stream_binout)
basic_test: basic
	echo "Hello, basic IO" | $(basic_binout)
	echo "Hello, basic IO" | $(basic_stream_binout)

$(basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(basic_stream_binout): $(io_root)basic/bs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
format_binout := $(bin_path)$(io_prefix)_format$(bin_ext)

format: $(format_binout)
format_test: format
	$(format_binout)

$(format_binout): $(io_root)format/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# flush
flush_binout := $(bin_path)$(io_prefix)_flush$(bin_ext)

flush: $(flush_binout)
flush_test: flush
	echo "abc" | $(flush_binout)

$(flush_binout): $(io_root)flush/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# scan
scan_binout := $(bin_path)$(io_prefix)_scan$(bin_ext)

scan: $(scan_binout)
scan_test: scan
	echo -n "X" "1234" "5678" "3.1415" "2.718" | $(scan_binout)

$(scan_binout): $(io_root)scan/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# wc
wc_binout := $(bin_path)$(io_prefix)_wc$(bin_ext)
wc_cppout := $(tmp_path)$(io_prefix)_wc$(cpp_ext)


wc: $(wc_binout)
wc_test: wc
	$(wc_binout) --help
	echo -n "abc" | $(wc_binout) -c
	echo -e "a\n b\n c" | $(wc_binout)
	$(wc_binout) -l -w -c -L $(CURDIR)/Makefile $(CURDIR)/src/io/wc/wc.c
	echo -n "abc" | \
    $(wc_binout) -l -w -c -L \
    $(CURDIR)/Makefile $(CURDIR)/src/io/wc/wc.c -
wc_valgrind_test: wc
	valgrind --leak-check=full \
           --track-origins=yes \
           $(wc_binout) $(shell ls $(CURDIR)/src/*.c)

$(wc_binout): $(io_root)wc/wc.c $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

