#
# ./configure --has-io
#
#

ifeq ($(CC_NAME), msvc)
io: io_stat
	@echo "#skip ..."
io_test: io_stat_test
	@echo "#skip ..."
else

io: io_stat                                     \
    io_umask

io_test: io_stat_test                           \
         io_umask_test

endif


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
io_stat_ft_binout := $(bin_path)/$(io_prefix)_stat_ft$(bin_ext)
io_stat_ft_sl := $(tmp_path)/$(io_prefix)_stat.sl

io_stat: $(io_stat_ft_binout)
io_stat_test: io_stat $(io_stat_ft_sl)
	-$(io_stat_ft_binout)
	$(io_stat_ft_binout) $(CURDIR)/$(bin_path)
	$(io_stat_ft_binout) $(io_stat_ft_sl) /dev/null
	$(io_stat_ft_binout) $(io_stat_ft_binout)
	stat $(io_stat_ft_binout)

$(io_stat_ft_sl): $(io_stat_ft_binout)
	ln -s $(io_stat_ft_binout) $@

$(io_stat_ft_binout): $(io_root)/stat/ft.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# umask
io_umask_binout := $(bin_path)/$(io_prefix)_umask$(bin_ext)

io_umask: $(io_umask_binout)
io_umask_test: io_umask
	-$(io_umask_binout)
	$(io_umask_binout) $(CURDIR)/$(tmp_path)
	touch $(tmp_path)/x
	mkdir $(tmp_path)/y

$(io_umask_binout): $(io_root)/umask/u1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
