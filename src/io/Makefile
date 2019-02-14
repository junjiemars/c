
io: basic \
    binary \
		error \
    file \
		fileno \
		format \
    flush \
		process \
		scan \
		variadic \
		wchar \
		wc
io_test: basic_test  \
         binary_test \
				 error_test \
         file_test \
				 fileno_test \
				 format_test \
         flush_test \
				 process_test \
				 scan_test \
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
basic_binout := $(bin_path)$(io_prefix)_basic$(bin_ext)

basic: $(basic_binout)
basic_test: basic
	echo "Hello, basic IO" | $(basic_binout)
	echo "Hello, 基础 IO" | $(basic_binout)

$(basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# binary I/O
binary_binout := $(bin_path)$(io_prefix)_binary$(bin_ext)

binary: $(binary_binout)
binary_test: binary
	$(binary_binout) "2*3" "2" "3"
	$(binary_binout)

$(binary_binout): $(io_root)binary/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# error
error_binout := $(bin_path)$(io_prefix)_error$(bin_ext)

error: $(error_binout)
error_test: error
	$(error_binout)

$(error_binout): $(io_root)error/e1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
format_binout := $(bin_path)$(io_prefix)_format$(bin_ext)

format: $(format_binout)
format_test: format
	$(format_binout)

$(format_binout): $(io_root)format/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# file
file_tmp_binout := $(bin_path)$(io_prefix)_file_tmp$(bin_ext)

file: $(file_tmp_binout)
file_test: file
	$(file_tmp_binout)

$(file_tmp_binout): $(io_root)file/tmp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# fileno
fileno_binout := $(bin_path)$(io_prefix)_fileno$(bin_ext)

fileno: $(fileno_binout)
fileno_test: fileno
	$(fileno_binout)

$(fileno_binout): $(io_root)fileno/fn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# flush
flush_binout := $(bin_path)$(io_prefix)_flush$(bin_ext)

flush: $(flush_binout)
flush_test: flush
	echo "abc" | $(flush_binout)

$(flush_binout): $(io_root)flush/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

process_binout := $(bin_path)$(io_prefix)_process$(bin_ext)

process: $(process_binout)
process_test: process
	$(process_binout)

$(process_binout): $(io_root)process/p.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# scan
scan_binout := $(bin_path)$(io_prefix)_scan$(bin_ext)

scan: $(scan_binout)
scan_test: scan
	echo -n "X" "1234" "5678" "3.1415" "2.718" | $(scan_binout)

$(scan_binout): $(io_root)scan/s.c
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

