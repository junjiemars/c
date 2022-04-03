#
# ./configure --has-io
#
# standard IO library
#


cio: cio_basic                                  \
     cio_binary                                 \
	   cio_diff                                   \
     cio_error                                  \
     cio_fileno                                 \
     cio_flight                                 \
     cio_flush                                  \
     cio_format                                 \
     cio_line                                   \
     cio_process                                \
     cio_reopen                                 \
     cio_scan                                   \
     cio_variadic                               \
     cio_wc                                     \
     cio_wchar

cio_test: cio_basic_test                        \
          cio_binary_test                       \
          cio_diff_test                         \
          cio_error_test                        \
          cio_fileno_test                       \
          cio_flight_test                       \
          cio_flush_test                        \
          cio_format_test                       \
          cio_line_test                         \
          cio_process_test                      \
          cio_reopen_test                       \
          cio_scan_test                         \
          cio_variadic_test                     \
          cio_wc_test                           \
          cio_wchar_test


# env
cio_prefix := cio
INC += $(nm_inc_opt)$(cio_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(f_sanitize)
endif


# basic I/O
cio_basic_binout := $(bin_path)/$(cio_prefix)_basic$(bin_ext)
cio_basic_cppout := $(tmp_path)/$(cio_prefix)_basic$(cpp_ext)

cio_basic: $(cio_basic_binout)
cio_basic_test: cio_basic
	echo "Hello, basic CIO" | $(cio_basic_binout)

$(cio_basic_binout): $(cio_basic_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(cio_basic_cppout): $(cio_root)/basic/b.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# binary I/O
cio_binary_basic_binout := $(bin_path)/$(cio_prefix)_binary_basic$(bin_ext)
cio_binary_array_binout := $(bin_path)/$(cio_prefix)_binary_array$(bin_ext)

cio_binary: cio_binary_basic                      \
           cio_binary_array
cio_binary_test: cio_binary_basic_test            \
                cio_binary_array_test

cio_binary_basic: $(cio_binary_basic_binout)
cio_binary_basic_test: cio_binary_basic
	$(cio_binary_basic_binout) "w*h" "0x11220000" "0x00003344"
	$(cio_binary_basic_binout)

cio_binary_array: $(cio_binary_array_binout)
cio_binary_array_test: cio_binary_array
	$(cio_binary_array_binout) $(tmp_path)/sassy.bin

$(cio_binary_basic_binout): $(cio_root)/binary/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cio_binary_array_binout): $(cio_root)/binary/b1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# diff
cio_diff_binout := $(bin_path)/$(cio_prefix)_diff$(bin_ext)

cio_diff: $(cio_diff_binout)
cio_diff_test: cio_diff
	$(cio_diff_binout) $(cio_root)/diff/lhs.txt $(cio_root)/diff/rhs.txt

$(cio_diff_binout): $(cio_root)/diff/d1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# error
cio_error_binout := $(bin_path)/$(cio_prefix)_error$(bin_ext)

cio_error: $(cio_error_binout)
cio_error_test: cio_error
	$(cio_error_binout) $(tmp_path)/where.c
	echo "abc" > $(tmp_path)/where.c
	$(cio_error_binout) $(tmp_path)/where.c

$(cio_error_binout): $(cio_root)/error/e1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
cio_format_in_binout := $(bin_path)/$(cio_prefix)_format_in$(bin_ext)
cio_format_out_binout := $(bin_path)/$(cio_prefix)_format_out$(bin_ext)

cio_format: $(cio_format_in_binout)             \
            $(cio_format_out_binout)
cio_format_test: cio_format
	$(cio_format_in_binout)
	$(cio_format_out_binout)

cio_format_in_test: $(cio_format_in_binout)
	$(cio_format_in_binout)
cio_format_out_test: $(cio_format_out_binout)
	$(cio_format_out_binout)

$(cio_format_in_binout): $(cio_root)/format/fi.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cio_format_out_binout): $(cio_root)/format/fo.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# fileno
cio_fileno_binout := $(bin_path)/$(cio_prefix)_fileno$(bin_ext)
cio_fileno_tmp_out := $(tmp_path)/$(cio_prefix)_fileno.txt

cio_fileno: $(cio_fileno_binout)
cio_fileno_test: cio_fileno
	$(cio_fileno_binout)
	$(cio_fileno_binout) > $(cio_fileno_tmp_out)
	cat $(cio_fileno_tmp_out)

$(cio_fileno_binout): $(cio_root)/fileno/fn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# flush
cio_flush_binout := $(bin_path)/$(cio_prefix)_flush$(bin_ext)

cio_flush: $(cio_flush_binout)
cio_flush_test: cio_flush
	echo "abcdefg" | $(cio_flush_binout)

$(cio_flush_binout): $(cio_root)/flush/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# flight
cio_flight_select_s_binout := $(bin_path)/$(cio_prefix)_flight_select_s$(bin_ext)
cio_flight_select_c_binout := $(bin_path)/$(cio_prefix)_flight_select_c$(bin_ext)

inc_flight := -I$(cio_root)/flight

ifeq ($(NM_SYSTEM),$(filter $(NM_SYSTEM),Linux Darwin))
cio_flight: cio_flight_select
cio_flight_test:

cio_flight_select: $(cio_flight_select_s_binout)  \
                  $(cio_flight_select_c_binout)

# cio_flight_select_test: cio_flight_select
#   $(cio_flight_select_s_binout)
#   $(cio_flight_select_c_binout)

else
cio_flight:
cio_flight_test:
endif

$(cio_flight_select_s_binout): $(cio_root)/flight/select/server.c \
                              $(cio_root)/flight/flight.h
	$(CC) $(INC) $(inc_flight) $(CFLAGS) $< $(bin_out)$@

$(cio_flight_select_c_binout): $(cio_root)/flight/select/client.c \
                              $(cio_root)/flight/flight.h
	$(CC) $(INC) $(inc_flight) $(CFLAGS) $< $(bin_out)$@

# line
cio_line_basic_binout := $(bin_path)/$(cio_prefix)_line_basic$(bin_ext)
cio_line_gets_binout := $(bin_path)/$(cio_prefix)_line_gets$(bin_ext)

cio_line: $(cio_line_basic_binout) $(cio_line_gets_binout)
cio_line_test: cio_line_basic_test                \
              cio_line_gets_test
cio_line_basic_test: $(cio_line_basic_binout)
	$(cio_line_basic_binout) $(CURDIR)/src/cio/line/zigzag
cio_line_gets_test: $(cio_line_gets_binout)
	$(cio_line_gets_binout) $(CURDIR)/src/cio/line/zigzag

$(cio_line_basic_binout): $(cio_root)/line/l.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cio_line_gets_binout): $(cio_root)/line/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# reopen
cio_reopen_binout := $(bin_path)/$(cio_prefix)_reopen$(bin_ext)

cio_reopen: $(cio_reopen_binout)
cio_reopen_test: cio_reopen
	-@cp $(CURDIR)/src/cio/reopen/sample.txt $(tmp_path)/
	$(cio_reopen_binout) $(tmp_path)/sample.txt

$(cio_reopen_binout): $(cio_root)/reopen/ro.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# process

cio_process_binout := $(bin_path)/$(cio_prefix)_process$(bin_ext)

cio_process: $(cio_process_binout)
cio_process_test: cio_process
	$(cio_process_binout)

$(cio_process_binout): $(cio_root)/process/p.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# scan
cio_scan_stdin_binout := $(bin_path)/$(cio_prefix)_scan$(bin_ext)
cio_scan_csv_binout := $(bin_path)/$(cio_prefix)_scan_csv$(bin_ext)
cio_scan_free_binout := $(bin_path)/$(cio_prefix)_scan_free$(bin_ext)

cio_scan: cio_scan_stdin                          \
         cio_scan_csv                            \
         cio_scan_free
cio_scan_test: cio_scan_stdin_test                \
              cio_scan_csv_test                  \
              cio_scan_free_test

cio_scan_stdin: $(cio_scan_stdin_binout)
cio_scan_csv: $(cio_scan_csv_binout)
cio_scan_free: $(cio_scan_free_binout)

cio_scan_stdin_test: cio_scan_stdin
	echo "X, 1234, 0x11223344, 5678, 3.1415, 2.718" | $(cio_scan_stdin_binout)
cio_scan_csv_test: cio_scan_csv
	$(cio_scan_csv_binout) $(CURDIR)/src/cio/scan/a.csv
cio_scan_free_test: cio_scan_free
	$(cio_scan_free_binout) $(CURDIR)/src/cio/scan/free.txt

$(cio_scan_stdin_binout): $(cio_root)/scan/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cio_scan_csv_binout): $(cio_root)/scan/csv.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cio_scan_free_binout): $(cio_root)/scan/free.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# variadic
cio_variadic_binout := $(bin_path)/$(cio_prefix)_variadic$(bin_ext)

cio_variadic: $(cio_variadic_binout)
cio_variadic_test: cio_variadic
	$(cio_variadic_binout)
	$(cio_variadic_binout) "Hi, variadic functcion!"

$(cio_variadic_binout): $(cio_root)/variadic/v1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wide char
cio_wchar_ws_binout := $(bin_path)/$(cio_prefix)_wchar_ws$(bin_ext)
cio_wchar_wc_binout := $(bin_path)/$(cio_prefix)_wchar_wc$(bin_ext)

cio_wchar: $(cio_wchar_ws_binout) $(cio_wchar_wc_binout)
cio_wchar_test: cio_wchar
	$(cio_wchar_ws_binout) $(CURDIR)/src/cio/wchar/sample.txt
	$(cio_wchar_wc_binout) $(CURDIR)/src/cio/wchar/sample.txt

$(cio_wchar_ws_binout): $(cio_root)/wchar/ws.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cio_wchar_wc_binout): $(cio_root)/wchar/wc.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wc
cio_wc_binout := $(bin_path)/$(cio_prefix)_wc$(bin_ext)
cio_wc_cppout := $(tmp_path)/$(cio_prefix)_wc$(cpp_ext)

cio_wc: $(cio_wc_binout)
cio_wc_test: cio_wc
	$(cio_wc_binout) --help
	echo -n "abc" | $(cio_wc_binout) -c
	echo -e "a\n b\n c" | $(cio_wc_binout)
	$(cio_wc_binout) -l -w -m -c -L $(CURDIR)/Makefile $(CURDIR)/src/cio/wc/wc.c
	echo -n "abc" | \
    $(cio_wc_binout) -l -w -m -c -L \
    $(CURDIR)/Makefile $(CURDIR)/src/cio/wc/wc.c -
cio_wc_valgrind_test: cio_wc
	valgrind --leak-check=full \
           --track-origins=yes \
           $(cio_wc_binout) $(shell ls $(CURDIR)/src/*.c)

$(cio_wc_binout): $(cio_root)/wc/wc.c $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
