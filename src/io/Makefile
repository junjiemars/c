#
# ./configure --has-io
#

io_prefix := io
INC += -I$(io_root) -I$(root)

ifeq ($(CC_NAME),msvc)
getopt_c := $(root)posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(cflags_sanitize)
endif

io: io_basic																		\
    io_binary																		\
    io_diff																			\
		io_error																		\
		io_fileno																		\
    io_flight																		\
    io_flush																		\
		io_format																		\
		io_line																			\
		io_process																	\
		io_reopen																		\
		io_scan																			\
    io_seek																			\
		io_variadic																	\
		io_wc																				\
		io_wchar

io_test: io_basic_test													\
         io_binary_test													\
         io_diff_test														\
         io_error_test													\
         io_fileno_test													\
         io_flight_test													\
         io_flush_test													\
         io_format_test													\
         io_line_test														\
         io_process_test												\
         io_reopen_test													\
         io_scan_test														\
         io_seek_test														\
         io_variadic_test												\
         io_wc_test															\
         io_wchar_test


# basic I/O
io_basic_binout := $(bin_path)$(io_prefix)_basic$(bin_ext)

io_basic: $(io_basic_binout)
io_basic_test: io_basic
	echo "Hello, basic IO" | $(io_basic_binout)

$(io_basic_binout): $(io_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# binary I/O
io_binary_basic_binout := $(bin_path)$(io_prefix)_binary_basic$(bin_ext)
io_binary_array_binout := $(bin_path)$(io_prefix)_binary_array$(bin_ext)

io_binary: io_binary_basic											\
           io_binary_array
io_binary_test: io_binary_basic_test						\
                io_binary_array_test

io_binary_basic: $(io_binary_basic_binout)
io_binary_basic_test: io_binary_basic
	$(io_binary_basic_binout) "w*h" "0x11220000" "0x00003344"
	$(io_binary_basic_binout)

io_binary_array: $(io_binary_array_binout)
io_binary_array_test: io_binary_array
	$(io_binary_array_binout) $(tmp_path)sassy.bin

$(io_binary_basic_binout): $(io_root)binary/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_binary_array_binout): $(io_root)binary/b1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# diff
io_diff_binout := $(bin_path)$(io_prefix)_diff$(bin_ext)

io_diff: $(io_diff_binout)
io_diff_test: io_diff
	$(io_diff_binout) $(io_root)diff/lhs.txt $(io_root)diff/rhs.txt

$(io_diff_binout): $(io_root)diff/d1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# error
io_error_binout := $(bin_path)$(io_prefix)_error$(bin_ext)

io_error: $(io_error_binout)
io_error_test: io_error
	$(io_error_binout) $(tmp_path)where.c
	echo "abc" > $(tmp_path)where.c
	$(io_error_binout) $(tmp_path)where.c

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

# flight
io_flight_select_s_binout := $(bin_path)$(io_prefix)_flight_select_s$(bin_ext)
io_flight_select_c_binout := $(bin_path)$(io_prefix)_flight_select_c$(bin_ext)

inc_flight := -I$(io_root)flight

ifeq ($(NM_SYSTEM),$(filter $(NM_SYSTEM),Linux Darwin))
io_flight: io_flight_select
io_flight_test:

io_flight_select: $(io_flight_select_s_binout)	\
                  $(io_flight_select_c_binout)

# io_flight_select_test: io_flight_select
# 	$(io_flight_select_s_binout)
# 	$(io_flight_select_c_binout)

else
io_flight:
io_flight_test:
endif

$(io_flight_select_s_binout): $(io_root)flight/select/server.c	\
                              $(io_root)flight/flight.h
	$(CC) $(INC) $(inc_flight) $(CFLAGS) $< $(bin_out)$@

$(io_flight_select_c_binout): $(io_root)flight/select/client.c	\
                              $(io_root)flight/flight.h
	$(CC) $(INC) $(inc_flight) $(CFLAGS) $< $(bin_out)$@

# line
io_line_basic_binout := $(bin_path)$(io_prefix)_line_basic$(bin_ext)
io_line_gets_binout := $(bin_path)$(io_prefix)_line_gets$(bin_ext)

io_line: $(io_line_basic_binout) $(io_line_gets_binout)
io_line_test: io_line_basic_test								\
              io_line_gets_test
io_line_basic_test: $(io_line_basic_binout)
	$(io_line_basic_binout) $(CURDIR)/src/io/line/zigzag
io_line_gets_test: $(io_line_gets_binout)
	$(io_line_gets_binout) $(CURDIR)/src/io/line/zigzag

$(io_line_basic_binout): $(io_root)line/l.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_line_gets_binout): $(io_root)line/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# reopen
io_reopen_binout := $(bin_path)$(io_prefix)_reopen$(bin_ext)

io_reopen: $(io_reopen_binout)
io_reopen_test: io_reopen
	-@cp $(CURDIR)/src/io/reopen/sample.txt $(tmp_path)
	$(io_reopen_binout) $(tmp_path)sample.txt

$(io_reopen_binout): $(io_root)reopen/ro.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# process

io_process_binout := $(bin_path)$(io_prefix)_process$(bin_ext)

io_process: $(io_process_binout)
io_process_test: io_process
	$(io_process_binout)

$(io_process_binout): $(io_root)process/p.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# scan
io_scan_stdin_binout := $(bin_path)$(io_prefix)_scan$(bin_ext)
io_scan_csv_binout := $(bin_path)$(io_prefix)_scan_csv$(bin_ext)
io_scan_free_binout := $(bin_path)$(io_prefix)_scan_free$(bin_ext)

io_scan: io_scan_stdin													\
         io_scan_csv														\
         io_scan_free
io_scan_test: io_scan_stdin_test								\
              io_scan_csv_test									\
              io_scan_free_test

io_scan_stdin: $(io_scan_stdin_binout)
io_scan_csv: $(io_scan_csv_binout)
io_scan_free: $(io_scan_free_binout)

io_scan_stdin_test: io_scan_stdin
	echo "X, 1234, 0x11223344, 5678, 3.1415, 2.718" | $(io_scan_stdin_binout)
io_scan_csv_test: io_scan_csv
	$(io_scan_csv_binout) $(CURDIR)/src/io/scan/a.csv
io_scan_free_test: io_scan_free
	$(io_scan_free_binout) $(CURDIR)/src/io/scan/free.txt

$(io_scan_stdin_binout): $(io_root)scan/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_scan_csv_binout): $(io_root)scan/csv.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_scan_free_binout): $(io_root)scan/free.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# seek
io_seek_basic_binout := $(bin_path)$(io_prefix)_seek_basic$(bin_ext)

io_seek: $(io_seek_basic_binout)
io_seek_test: io_seek
	$(io_seek_basic_binout) $(CURDIR)/src/io/seek/records.txt	\
                          $(CURDIR)/$(tmp_path)records.bin	\
                          $(CURDIR)/$(tmp_path)records.idx

$(io_seek_basic_binout): $(io_root)seek/s1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# variadic
io_variadic_binout := $(bin_path)$(io_prefix)_variadic$(bin_ext)

io_variadic: $(io_variadic_binout)
io_variadic_test: io_variadic
	$(io_variadic_binout)
	$(io_variadic_binout) "Hi, variadic function!"

$(io_variadic_binout): $(io_root)variadic/v1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wide char
io_wchar_ws_binout := $(bin_path)$(io_prefix)_wchar_ws$(bin_ext)
io_wchar_wc_binout := $(bin_path)$(io_prefix)_wchar_wc$(bin_ext)

io_wchar: $(io_wchar_ws_binout) $(io_wchar_wc_binout)
io_wchar_test: io_wchar
	$(io_wchar_ws_binout) $(CURDIR)/src/io/wchar/sample.txt
	$(io_wchar_wc_binout) $(CURDIR)/src/io/wchar/sample.txt

$(io_wchar_ws_binout): $(io_root)wchar/ws.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_wchar_wc_binout): $(io_root)wchar/wc.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wc
io_wc_binout := $(bin_path)$(io_prefix)_wc$(bin_ext)
io_wc_cppout := $(tmp_path)$(io_prefix)_wc$(cpp_ext)

io_wc: $(io_wc_binout)
io_wc_test: io_wc
	$(io_wc_binout) --help
	echo -n "abc" | $(io_wc_binout) -c
	echo -e "a\n b\n c" | $(io_wc_binout)
	$(io_wc_binout) -l -w -m -c -L $(CURDIR)/Makefile $(CURDIR)/src/io/wc/wc.c
	echo -n "abc" | \
    $(io_wc_binout) -l -w -m -c -L \
    $(CURDIR)/Makefile $(CURDIR)/src/io/wc/wc.c -
io_wc_valgrind_test: io_wc
	valgrind --leak-check=full \
           --track-origins=yes \
           $(io_wc_binout) $(shell ls $(CURDIR)/src/*.c)

$(io_wc_binout): $(io_root)wc/wc.c $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
