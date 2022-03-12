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

io: io_access                                   \
    io_copy                                     \
    io_redirect                                 \
    io_stat                                     \
    io_umask

io_test: io_access_test                         \
         io_copy_test                           \
         io_redirect_test                       \
         io_stat_test                           \
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


# access
io_access_binout := $(bin_path)/$(io_prefix)_access$(bin_ext)
io_access_nuid := $(tmp_path)/$(io_prefix)_access_nuid

io_access: $(io_access_binout) $(io_access_nuid)
io_access_test: io_access
	$(io_access_binout) $(io_access_binout)
	$(io_access_binout) $(io_access_nuid)
	# stat $(io_access_nuid)
	# sudo chown root $(io_access_binout)
	# sudo chmod u+s $(io_access_binout)
	# stat $(io_access_binout)

# copy
io_copy_std_binout := $(bin_path)/$(io_prefix)_copy_std$(bin_ext)

io_copy: $(io_copy_std_binout)
io_copy_test: io_copy_std_test

io_copy_std_test: $(io_copy_std_binout)
	echo "abc\ndef" | $(io_copy_std_binout)

$(io_copy_std_binout): $(io_root)/copy/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_access_nuid):
	touch $@
	chmod 600 $@
	# sudo chown root $@

$(io_access_binout): $(io_root)/access/a.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# redirect
io_redirect_binout := $(bin_path)/$(io_prefix)_redirect$(bin_ext)
io_redirect_out1 := $(tmp_path)/$(io_prefix)_redirect.out1
io_redirect_out2 := $(tmp_path)/$(io_prefix)_redirect.out2

io_redirect: $(io_redirect_binout)
io_redirect_test: io_redirect
	$(io_redirect_binout) > $(io_redirect_out1) 2>&1
	$(io_redirect_binout) 2>&1 >$(io_redirect_out2)

$(io_redirect_binout): $(io_root)/redirect/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


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
