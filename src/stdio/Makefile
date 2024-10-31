# -*- mode:makefile-gmake -*-
#
# ./configure --has-stdio
#
# standard IO library
#


# ifeq ($(CC_NAME), msvc)
# stdio:
# 	@echo "#skip ..."
# stdio_test: stdio
# 	@echo "#skip ..."
# else


stdio: stdio_basic                              \
       stdio_binary                             \
       stdio_buf                                \
       stdio_char                               \
	     stdio_diff                               \
       stdio_error                              \
       stdio_fileno                             \
       stdio_flight                             \
       stdio_flush                              \
       stdio_format                             \
       stdio_line                               \
       stdio_open                               \
       stdio_process                            \
       stdio_scan                               \
       stdio_seek                               \
       stdio_variadic                           \
       stdio_wc                                 \
       stdio_wide                               \
       stdio_wchar

stdio_test: stdio_basic_test                    \
            stdio_binary_test                   \
            stdio_buf_test                      \
            stdio_char_test                     \
            stdio_diff_test                     \
            stdio_error_test                    \
            stdio_fileno_test                   \
            stdio_flight_test                   \
            stdio_flush_test                    \
            stdio_format_test                   \
            stdio_line_test                     \
            stdio_open_test                     \
            stdio_process_test                  \
            stdio_scan_test                     \
            stdio_seek_test                     \
            stdio_variadic_test                 \
            stdio_wc_test                       \
            stdio_wide_test                     \
            stdio_wchar_test

# endif 													#skip


# env
stdio_prefix := stdio
INC += $(nm_inc_opt)$(stdio_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(f_sanitize)
endif


# basic I/O
stdio_basic_raw_binout := $(bin_path)/$(stdio_prefix)_basic_raw$(bin_ext)
stdio_basic_raw_cppout := $(tmp_path)/$(stdio_prefix)_basic_raw$(cpp_ext)
stdio_basic_err_binout := $(bin_path)/$(stdio_prefix)_basic_err$(bin_ext)

stdio_basic: $(stdio_basic_raw_binout)          \
             $(stdio_basic_err_binout)
stdio_basic_test: stdio_basic_raw_test          \
                  stdio_basic_err_test

stdio_basic_raw_test: $(stdio_basic_raw_binout)
	echo "Hello, basic STDIO" | $<
	$< < $(stdio_root)/basic/b.c

stdio_basic_err_test: $(stdio_basic_err_binout)
	$< 0< $(out)/nore.h

$(stdio_basic_raw_binout): $(stdio_basic_raw_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(stdio_basic_raw_cppout): $(stdio_root)/basic/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

$(stdio_basic_err_binout): $(stdio_root)/basic/b1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(cpp_out)$@


# binary I/O
stdio_binary_basic_binout := $(bin_path)/$(stdio_prefix)_binary_basic$(bin_ext)
stdio_binary_array_binout := $(bin_path)/$(stdio_prefix)_binary_array$(bin_ext)
stdio_binary_rect_file := $(tmp_path)/$(stdio_prefix)_binary_rect.file
stdio_binary_sassy_file := $(tmp_path)/$(stdio_prefix)_binary_sassy.file

stdio_binary: stdio_binary_basic                \
              stdio_binary_array
stdio_binary_test: stdio_binary_basic_test      \
                   stdio_binary_array_test

stdio_binary_basic: $(stdio_binary_basic_binout)
stdio_binary_basic_test: stdio_binary_basic
	$(stdio_binary_basic_binout) $(stdio_binary_rect_file)  \
    "w*h" "0x11220000" "0x00003344"
	$(stdio_binary_basic_binout) $(stdio_binary_rect_file)

stdio_binary_array: $(stdio_binary_array_binout)
stdio_binary_array_test: stdio_binary_array
	$(stdio_binary_array_binout) $(stdio_binary_sassy_file)

$(stdio_binary_basic_binout): $(stdio_root)/binary/b.c  \
                              $(root)/posix/nio.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(stdio_binary_array_binout): $(stdio_root)/binary/b1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# buf
stdio_buf_un_binout := $(bin_path)/$(stdio_prefix)_buf_un$(bin_ext)
stdio_buf_out_file := $(tmp_path)/$(stdio_prefix)_buf_out.file

stdio_buf: $(stdio_buf_un_binout)
stdio_buf_test: stdio_buf_un_test

stdio_buf_un_test: $(stdio_buf_un_binout)
	$< < $(out)/nore.h > $(stdio_buf_out_file)

$(stdio_buf_un_binout): $(stdio_root)/buf/ub1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# char
stdio_char_binout := $(bin_path)/$(stdio_prefix)_char$(bin_ext)

stdio_char: $(stdio_char_binout)
stdio_char_test: stdio_char
	-$(stdio_char_binout) 0 < $(stdio_root)/char/c1.c

$(stdio_char_binout): $(stdio_root)/char/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# diff
stdio_diff_binout := $(bin_path)/$(stdio_prefix)_diff$(bin_ext)

stdio_diff: $(stdio_diff_binout)
stdio_diff_test: stdio_diff
	$(stdio_diff_binout) $(stdio_root)/diff/lhs.txt $(stdio_root)/diff/rhs.txt

$(stdio_diff_binout): $(stdio_root)/diff/d1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# error
stdio_error_binout := $(bin_path)/$(stdio_prefix)_error$(bin_ext)

stdio_error: $(stdio_error_binout)
stdio_error_test: stdio_error
	$(stdio_error_binout) $(tmp_path)/where.c
	echo "abc" > $(tmp_path)/where.c
	$(stdio_error_binout) $(tmp_path)/where.c

$(stdio_error_binout): $(stdio_root)/error/e1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# format I/O
stdio_format_in_binout := $(bin_path)/$(stdio_prefix)_format_in$(bin_ext)
stdio_format_out_binout := $(bin_path)/$(stdio_prefix)_format_out$(bin_ext)

stdio_format: $(stdio_format_in_binout)             \
            $(stdio_format_out_binout)
stdio_format_test: stdio_format_in_test             \
                 stdio_format_out_test

stdio_format_in_test: $(stdio_format_in_binout)
	-$(stdio_format_in_binout)
stdio_format_out_test: $(stdio_format_out_binout)
	-$(stdio_format_out_binout)

$(stdio_format_in_binout): $(stdio_root)/format/fi.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(stdio_format_out_binout): $(stdio_root)/format/fo.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# fileno
stdio_fileno_binout := $(bin_path)/$(stdio_prefix)_fileno$(bin_ext)
stdio_fileno_file := $(tmp_path)/$(stdio_prefix)_fileno.file

stdio_fileno: $(stdio_fileno_binout)
stdio_fileno_test: stdio_fileno                     \
                 $(stdio_fileno_file)
	$(stdio_fileno_binout) < $(stdio_fileno_file)
	$(stdio_fileno_binout) <> $(stdio_fileno_file)
	cat $(stdio_fileno_file)

$(stdio_fileno_file):
	touch $@


$(stdio_fileno_binout): $(stdio_root)/fileno/fn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# flush
stdio_flush_binout := $(bin_path)/$(stdio_prefix)_flush$(bin_ext)

stdio_flush: $(stdio_flush_binout)
stdio_flush_test: stdio_flush
	echo "abcdefg" | $(stdio_flush_binout)

$(stdio_flush_binout): $(stdio_root)/flush/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# flight
stdio_flight_select_s_binout := $(bin_path)/$(stdio_prefix)_flight_select_s$(bin_ext)
stdio_flight_select_c_binout := $(bin_path)/$(stdio_prefix)_flight_select_c$(bin_ext)

inc_flight := -I$(stdio_root)/flight

ifeq ($(NM_SYSTEM),$(filter $(NM_SYSTEM),Linux Darwin))
stdio_flight: stdio_flight_select
stdio_flight_test:

stdio_flight_select: $(stdio_flight_select_s_binout)  \
                  $(stdio_flight_select_c_binout)

# stdio_flight_select_test: stdio_flight_select
#   $(stdio_flight_select_s_binout)
#   $(stdio_flight_select_c_binout)

else
stdio_flight:
stdio_flight_test:
endif

$(stdio_flight_select_s_binout): $(stdio_root)/flight/select/server.c \
                              $(stdio_root)/flight/flight.h
	$(CC) $(INC) $(inc_flight) $(CFLAGS) $< $(bin_out)$@

$(stdio_flight_select_c_binout): $(stdio_root)/flight/select/client.c \
                              $(stdio_root)/flight/flight.h
	$(CC) $(INC) $(inc_flight) $(CFLAGS) $< $(bin_out)$@

# line
stdio_line_basic_binout := $(bin_path)/$(stdio_prefix)_line_basic$(bin_ext)

stdio_line: $(stdio_line_basic_binout)
stdio_line_test: stdio_line_basic_test

stdio_line_basic_test: $(stdio_line_basic_binout)
	$(stdio_line_basic_binout) $(CURDIR)/src/stdio/line/zigzag

stdio_line_gets_test: $(stdio_line_gets_binout)
	$(stdio_line_gets_binout) $(CURDIR)/src/stdio/line/zigzag

$(stdio_line_basic_binout): $(stdio_root)/line/l.c  \
                          $(root)/posix/nio.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(stdio_line_gets_binout): $(stdio_root)/line/s.c   \
                         $(root)/posix/nio.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# open
stdio_open_re_binout := $(bin_path)/$(stdio_prefix)_open_re$(bin_ext)
stdio_open_fd_binout := $(bin_path)/$(stdio_prefix)_open_fd$(bin_ext)
stdio_open_file := $(tmp_path)/$(stdio_prefix)_open.file

stdio_open: $(stdio_open_re_binout)
stdio_open_test: stdio_open_re_test             \
                 stdio_open_fd_test

$(stdio_open_file):
	echo "abcdef" > $@

stdio_open_re_test: $(stdio_open_re_binout)     \
                    $(stdio_open_file)
	$< $(stdio_open_file)

stdio_open_fd_test: $(stdio_open_fd_binout)
	$< < $(stdio_root)/open/fd1.c


$(stdio_open_re_binout): $(stdio_root)/open/ro1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(stdio_open_fd_binout): $(stdio_root)/open/fd1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# process
stdio_process_binout := $(bin_path)/$(stdio_prefix)_process$(bin_ext)

stdio_process: $(stdio_process_binout)
stdio_process_test: stdio_process
	$(stdio_process_binout)

$(stdio_process_binout): $(stdio_root)/process/p.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# scan
stdio_scan_stdin_binout := $(bin_path)/$(stdio_prefix)_scan$(bin_ext)
stdio_scan_csv_binout := $(bin_path)/$(stdio_prefix)_scan_csv$(bin_ext)
stdio_scan_free_binout := $(bin_path)/$(stdio_prefix)_scan_free$(bin_ext)
stdio_scan_free_file := $(tmp_path)/$(stdio_prefix)_scan_free.file
stdio_scan_csv_file := $(tmp_path)/$(stdio_prefix)_scan.csv

stdio_scan: stdio_scan_stdin                        \
         stdio_scan_csv                           \
         stdio_scan_free
stdio_scan_test: stdio_scan_stdin_test              \
               stdio_scan_csv_test                \
               stdio_scan_free_test

stdio_scan_stdin: $(stdio_scan_stdin_binout)
stdio_scan_csv: $(stdio_scan_csv_binout)
stdio_scan_free: $(stdio_scan_free_binout)

stdio_scan_stdin_test: stdio_scan_stdin
	echo "X, 1234, 0x11223344, 5678, 3.1415, 2.718" | $(stdio_scan_stdin_binout)

stdio_scan_csv_test: stdio_scan_csv                 \
                   $(stdio_scan_csv_file)
	$(stdio_scan_csv_binout) $(stdio_scan_csv_file)

stdio_scan_free_test: stdio_scan_free               \
                    $(stdio_scan_free_file)
	$(stdio_scan_free_binout) $(stdio_scan_free_file)

$(stdio_scan_free_file):
	echo "10 100 1000" > $@

$(stdio_scan_csv_file):
	echo "01,20,1500.11,Antone" > $@
	echo "02,19,1621.22,Bourn" >> $@
	echo "03,23,11223.33,Carrol" >> $@

$(stdio_scan_stdin_binout): $(stdio_root)/scan/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(stdio_scan_csv_binout): $(stdio_root)/scan/csv.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(stdio_scan_free_binout): $(stdio_root)/scan/free.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# seek
stdio_seek_binout := $(bin_path)/$(stdio_prefix)_seek$(bin_ext)
stdio_seek_file := $(tmp_path)/$(stdio_prefix)_seek.file

stdio_seek: $(stdio_seek_binout)
stdio_seek_test: stdio_seek
	$(stdio_seek_binout) $(stdio_seek_file)

$(stdio_seek_binout): $(stdio_root)/seek/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# variadic
stdio_variadic_binout := $(bin_path)/$(stdio_prefix)_variadic$(bin_ext)

stdio_variadic: $(stdio_variadic_binout)
stdio_variadic_test: stdio_variadic
	$(stdio_variadic_binout)
	$(stdio_variadic_binout) "Hi, variadic functstdion!"

$(stdio_variadic_binout): $(stdio_root)/variadic/v1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# wc
stdio_wc_binout := $(bin_path)/$(stdio_prefix)_wc$(bin_ext)
stdio_wc_cppout := $(tmp_path)/$(stdio_prefix)_wc$(cpp_ext)

stdio_wc: $(stdio_wc_binout)
stdio_wc_test: stdio_wc
	$(stdio_wc_binout) --help
	echo -n "abc" | $(stdio_wc_binout) -c
	echo -e "a\n b\n c" | $(stdio_wc_binout)
	$(stdio_wc_binout) -l -w -m -c -L $(CURDIR)/Makefile $(CURDIR)/src/stdio/wc/wc.c
	# echo -n "abc" | \
  #   $(stdio_wc_binout) -l -w -m -c -L \
  #   $(CURDIR)/Makefile $(CURDIR)/src/stdio/wc/wc.c -
stdio_wc_valgrind_test: stdio_wc
	valgrind --leak-check=full \
           --track-origins=yes \
           $(stdio_wc_binout) $(shell ls $(CURDIR)/src/*.c)

$(stdio_wc_binout): $(stdio_root)/wc/wc.c $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wchar
stdio_wchar_ws_binout := $(bin_path)/$(stdio_prefix)_wchar_ws$(bin_ext)
stdio_wchar_wc_binout := $(bin_path)/$(stdio_prefix)_wchar_wc$(bin_ext)
stdio_wchar_file := $(tmp_path)/$(stdio_prefix)_wchar.file

stdio_wchar: $(stdio_wchar_ws_binout) $(stdio_wchar_wc_binout)
stdio_wchar_test: stdio_wchar_ws_test               \
                stdio_wchar_wc_test

stdio_wchar_ws_test: $(stdio_wchar_ws_binout)             \
                   $(stdio_wchar_file)
	$(stdio_wchar_ws_binout) $(stdio_wchar_file)

stdio_wchar_wc_test: $(stdio_wchar_wc_binout)       \
                   $(stdio_wchar_file)
	$(stdio_wchar_wc_binout) $(stdio_wchar_file)

$(stdio_wchar_file):
	echo "abc中文def" > $@

$(stdio_wchar_ws_binout): $(stdio_root)/wchar/ws.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(stdio_wchar_wc_binout): $(stdio_root)/wchar/wc.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# wide
stdio_wide_binout := $(bin_path)/$(stdio_prefix)_wide$(bin_ext)
stdio_wide_file := $(tmp_path)$(stdio_prefix)_wide.file

stdio_wide: $(stdio_wide_binout)
stdio_wide_test: stdio_wide
	$(stdio_wide_binout)
	$(stdio_wide_binout) 1
	$(stdio_wide_binout) -1
	$(stdio_wide_binout) 1 >$(stdio_wide_file) && cat $(stdio_wide_file)

$(stdio_wide_binout): $(stdio_root)/wide/w1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@
