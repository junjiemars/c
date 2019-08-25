# ./configure --has-io

io: io_basic \
    io_binary \
		io_error \
		io_fileno \
		io_format \
    io_flush \
		io_line \
		reopen \
		io_process \
		scan \
    tmp \
		variadic \
		wchar \
		wc
io_test: io_basic_test  \
         io_binary_test \
				 io_error_test \
				 io_fileno_test \
				 io_format_test \
         io_flush_test \
				 io_line_test \
				 reopen_test \
				 io_process_test \
				 scan_test \
         tmp_test \
				 variadic_test \
				 wchar_test \
				 wc_test

io_prefix := io

INC += -I$(io_root)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif


# basic I/O
io_basic_binout := $(bin_path)$(io_prefix)_basic$(bin_ext)

io_basic: $(io_basic_binout)
io_basic_test: io_basic
	echo "Hello, basic IO" | $(io_basic_binout)

$(io_basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# binary I/O
io_binary_binout := $(bin_path)$(io_prefix)_binary$(bin_ext)

io_binary: $(io_binary_binout)
io_binary_test: io_binary
	$(io_binary_binout) "w*h" "0x11220000" "0x00003344"
	$(io_binary_binout)

$(io_binary_binout): $(io_root)binary/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# error
io_error_binout := $(bin_path)$(io_prefix)_error$(bin_ext)

io_error: $(io_error_binout)
io_error_test: io_error
	$(error_binout)

$(io_error_binout): $(io_root)error/e1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
io_format_binout := $(bin_path)$(io_prefix)_format$(bin_ext)

io_format: $(io_format_binout)
io_format_test: io_format
	$(io_format_binout)

$(io_format_binout): $(io_root)format/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# fileno
io_fileno_binout := $(bin_path)$(io_prefix)_fileno$(bin_ext)

io_fileno: $(io_fileno_binout)
io_fileno_test: io_fileno
	$(io_fileno_binout)

$(io_fileno_binout): $(io_root)fileno/fn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# flush
io_flush_binout := $(bin_path)$(io_prefix)_flush$(bin_ext)

io_flush: $(io_flush_binout)
io_flush_test: io_flush
	echo "abcdefg" | $(io_flush_binout)

$(io_flush_binout): $(io_root)flush/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# line
io_line_binout := $(bin_path)$(io_prefix)_line$(bin_ext)

io_line: $(io_line_binout)
io_line_test: io_line
	$(io_line_binout) $(CURDIR)/src/io/line/boards

$(io_line_binout): $(io_root)line/l.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# reopen
reopen_binout := $(bin_path)$(io_prefix)_reopen$(bin_ext)

reopen: $(reopen_binout)
reopen_test: reopen
	-@cp $(CURDIR)/src/io/reopen/sample.txt $(tmp_path)
	$(reopen_binout) $(tmp_path)sample.txt

$(reopen_binout): $(io_root)reopen/ro.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# process

io_process_binout := $(bin_path)$(io_prefix)_process$(bin_ext)

io_process: $(io_process_binout)
io_process_test: io_process
	$(io_process_binout)

$(io_process_binout): $(io_root)process/p.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# scan
scan_binout := $(bin_path)$(io_prefix)_scan$(bin_ext)

scan: $(scan_binout)
scan_test: scan
	echo "X, 1234, 5678, 3.1415, 2.718" | $(scan_binout)

$(scan_binout): $(io_root)scan/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# tmp
tmp_binout := $(bin_path)$(io_prefix)_tmp$(bin_ext)

tmp: $(tmp_binout)
tmp_test: tmp
	$(tmp_binout)

$(tmp_binout): $(io_root)tmp/tmp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# variadic
variadic_binout := $(bin_path)$(io_prefix)_variadic$(bin_ext)

variadic: $(variadic_binout)
variadic_test: variadic
	$(variadic_binout)
	$(variadic_binout) "Hi, variadic function!"

$(variadic_binout): $(io_root)variadic/v1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wide char
wchar_ws_binout := $(bin_path)$(io_prefix)_wchar_ws$(bin_ext)
wchar_wc_binout := $(bin_path)$(io_prefix)_wchar_wc$(bin_ext)

wchar: $(wchar_ws_binout) $(wchar_wc_binout)
wchar_test: wchar
	$(wchar_ws_binout) $(io_root)wchar/ws.c
	$(wchar_wc_binout) $(io_root)wchar/wc.c

$(wchar_ws_binout): $(io_root)wchar/ws.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(wchar_wc_binout): $(io_root)wchar/wc.c
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

