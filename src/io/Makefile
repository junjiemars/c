#
# ./configure --has-io
#
#


io: io_stat

io_test: io_stat_test


# env
io_prefix := io
INC += $(nm_inc_opt)$(io_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(cflags_sanitize)
endif


# stat
io_stat_binout := $(bin_path)/$(io_prefix)_stat$(bin_ext)

io_stat: $(io_stat_binout)
io_stat_test: io_stat
	$(io_stat_binout) $(CURDIR)/$(bin_path) $(CURDIR)/$(io_stat_binout) /dev/null

$(io_stat_binout): $(io_root)/stat/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
