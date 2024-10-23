#
# ./configure --has-term
#
#



ifeq ($(CC_NAME), msvc)
term:
	@echo "#skip ..."
term_test:
	@echo "#skip ..."
else

term: term_map                                  \
      term_cflag                                \
      term_win                                  \
      term_mode

term_test: term_map_test                        \
           term_cflag_test                      \
           term_win_test                        \
           term_mode_test

endif



# env
term_prefix := term
INC += $(nm_inc_opt)$(term_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(cflags_sanitize)
endif



# map
term_map_eof_binout := $(bin_path)/$(term_prefix)_map_eof$(bin_ext)

term_map: $(term_map_eof_binout)
term_map_test: term_map_eof_test

term_map_eof_test: $(term_map_eof_binout)
  # saved_stty=$(stty -g)
  # stty $saved_stty
	$< && stty -a | grep -q -e 'eof = \^B;'

$(term_map_eof_binout): $(term_root)/map/eof1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# cflag
term_cflag_csize_binout := $(bin_path)/$(term_prefix)_cflag_csize$(bin_ext)

term_cflag: $(term_cflag_csize_binout)
term_cflag_test: term_cflag_csize_test

term_cflag_csize_test: $(term_cflag_csize_binout)
	$<

$(term_cflag_csize_binout): $(term_root)/cflag/csize.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# win
term_win_size_binout := $(bin_path)/$(term_prefix)_win_size$(bin_ext)

term_win: $(term_win_size_binout)
term_win_test: term_win_size_test

term_win_size_test: $(term_win_size_binout)
	$<

$(term_win_size_binout): $(term_root)/win/w1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# mode
term_mode_raw_binout := $(bin_path)/$(term_prefix)_mode_raw$(bin_ext)

term_mode: term_mode_raw
term_mode_test: term_mode_raw_test

term_mode_raw: $(term_mode_raw_binout)
term_mode_raw_test: $(term_mode_raw_binout)
	-@echo "" | $<

$(term_mode_raw_binout): $(term_root)/mode/raw1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
