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
      term_csize                                \
      term_wsize                                \
      term_raw

term_test: term_map_test                        \
           term_csize_test                      \
           term_wsize_test                      \
           term_raw_test

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
term_map_binout := $(bin_path)/$(term_prefix)_map$(bin_ext)

term_map: $(term_map_binout)
term_map_test: term_map
	$(term_map_binout)

$(term_map_binout): $(term_root)/m1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# csize
term_csize_binout := $(bin_path)/$(term_prefix)_csize$(bin_ext)

term_csize: $(term_csize_binout)
term_csize_test: term_csize
	$(term_csize_binout)

$(term_csize_binout): $(term_root)/csize.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# wsize
term_wsize_binout := $(bin_path)/$(term_prefix)_wsize$(bin_ext)
term_wsize_cppout := $(tmp_path)/$(term_prefix)_wsize$(cpp_ext)

term_wsize: $(term_wsize_binout)
term_wsize_test: term_wsize
	$(term_wsize_binout)

$(term_wsize_binout): $(term_wsize_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(term_wsize_cppout): $(term_root)/wsize.c
	$(CC) $(CPPFLAGS) $(INC) $^ $(nm_stage_pre) $(cpp_out)$@

# raw
term_raw_binout := $(bin_path)/$(term_prefix)_raw$(bin_ext)
term_raw_cppout := $(tmp_path)/$(term_prefix)_raw$(cpp_ext)

term_raw: $(term_raw_binout)
term_raw_test: term_raw
	-@echo "abc" | $(term_raw_binout)

$(term_raw_binout): $(term_raw_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(term_raw_cppout): $(term_root)/raw.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@



# eof
