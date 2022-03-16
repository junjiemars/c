#
# ./configure --has-term
#
#

ifeq ($(CC_NAME), msvc)
term: term_map
	@echo "#skip ..."
term_test: term_map_test
	@echo "#skip ..."
else

term: term_map

term_test: term_map_test

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



# eof
