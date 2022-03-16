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
    io_hole                                     \
    io_redirect                                 \
    io_share                                    \
    io_seek                                     \
    io_stat                                     \
    io_struct                                   \
    io_umask

io_test: io_access_test                         \
         io_copy_test                           \
         io_hole_test                           \
         io_redirect_test                       \
         io_share_test                          \
         io_seek_test                           \
         io_stat_test                           \
         io_struct_test                         \
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
io_access_open_binout := $(bin_path)/$(io_prefix)_access_open$(bin_ext)
io_access_mode_binout := $(bin_path)/$(io_prefix)_access_mode$(bin_ext)
io_access_cntlfl_binout := $(bin_path)/$(io_prefix)_access_cntlfl$(bin_ext)
io_access_open_file := $(tmp_path)/$(io_prefix)_access_open_file
io_access_mode_file := $(tmp_path)/$(io_prefix)_access_mode_file
io_access_cntlfl_file := $(tmp_path)/$(io_prefix)_access_cntlfl_file

io_access: $(io_access_open_binout)             \
           $(io_access_mode_binout)             \
           $(io_access_cntlfl_binout)
io_access_test: io_access_open_test             \
                io_access_mode_test             \
                io_access_cntlfl_test

io_access_open_test: $(io_access_open_binout)   \
                     $(io_access_open_file)
	$(io_access_binout) $(io_access_binout)
	$(io_access_binout) $(io_access_open_file)
	# stat $(io_access_open_file)
	# sudo chown root $(io_access_binout)
	# sudo chmod u+s $(io_access_binout)
	# stat $(io_access_binout)

$(io_access_open_file):
	touch $@
	chmod 600 $@

io_access_mode_test: $(io_access_mode_binout)
	$(io_access_mode_binout) 0 < /dev/tty
	$(io_access_mode_binout) 1 > $(io_access_mode_file)
	cat $(io_access_mode_file)
	$(io_access_mode_binout) 2 2>> $(io_access_mode_file)
	$(io_access_mode_binout) 5 5<>$(io_access_mode_file)

io_access_cntlfl_test: $(io_access_cntlfl_binout)
	$(io_access_cntlfl_binout) $(io_access_cntlfl_file)

$(io_access_mode_binout): $(io_root)/access/m.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_access_open_binout): $(io_root)/access/a.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_access_cntlfl_binout): $(io_root)/access/c.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# copy
io_copy_std_binout := $(bin_path)/$(io_prefix)_copy_std$(bin_ext)

io_copy: $(io_copy_std_binout)
io_copy_test: io_copy_std_test

io_copy_std_test: $(io_copy_std_binout)
	echo "abc\ndef" | $(io_copy_std_binout)

$(io_copy_std_binout): $(io_root)/copy/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

	# sudo chown root $@

# hole
io_hole_binout := $(bin_path)/$(io_prefix)_hole$(bin_ext)
io_hole_yes := $(tmp_path)/$(io_prefix)_hole.yes$(bin_ext)
io_hole_no := $(tmp_path)/$(io_prefix)_hole.no$(bin_ext)

io_hole: $(io_hole_binout)
io_hole_test: io_hole
	$(io_hole_binout) $(io_hole_yes)
	$(io_hole_binout) $(io_hole_no) no
	ls -ls $(tmp_path)/$(io_prefix)_hole*
	od -c $(io_hole_yes)

$(io_hole_binout): $(io_root)/hole/h1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# redirect
io_redirect_binout := $(bin_path)/$(io_prefix)_redirect$(bin_ext)
io_redirect_out1 := $(tmp_path)/$(io_prefix)_redirect.out1
io_redirect_out2 := $(tmp_path)/$(io_prefix)_redirect.out2

io_redirect: $(io_redirect_binout)
io_redirect_test: io_redirect
	$(io_redirect_binout) > $(io_redirect_out1) 2>&1
	cat $(io_redirect_out1)
	$(io_redirect_binout) 2>&1 >$(io_redirect_out2)
	cat $(io_redirect_out2)

$(io_redirect_binout): $(io_root)/redirect/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# share
io_share1_binout := $(bin_path)/$(io_prefix)_share1$(bin_ext)
io_share2_binout := $(bin_path)/$(io_prefix)_share2$(bin_ext)
io_share3_binout := $(bin_path)/$(io_prefix)_share3$(bin_ext)
io_share1_out := $(tmp_path)/$(io_prefix)_share1_out
io_share2_out := $(tmp_path)/$(io_prefix)_share2_out
io_share3_out := $(tmp_path)/$(io_prefix)_share3_out

io_share: $(io_share1_binout)                   \
          $(io_share2_binout)                   \
          $(io_share3_binout)
io_share_test: io_share1_test                   \
               io_share2_test                   \
               io_share3_test

io_share1_test: $(io_share1_binout)
	$(io_share1_binout) $(io_share1_out)
	sleep 1
	wc -c $(io_share1_out)

io_share2_test: $(io_share2_binout)
	$(io_share2_binout) $(io_share2_out)
	sleep 1
	wc -c $(io_share2_out)

io_share3_test: $(io_share3_binout)
	$(io_share3_binout) $(io_share3_out)
	sleep 1
	wc -c $(io_share3_out)

$(io_share1_binout): $(io_root)/share/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -DN=1000 $^ $(bin_out)$@

$(io_share2_binout): $(io_root)/share/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -DN=1000 $^ $(bin_out)$@

$(io_share3_binout): $(io_root)/share/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -DN=1000 -D_PWRITE_ $^ $(bin_out)$@

# seek
io_seek_append_binout := $(bin_path)/$(io_prefix)_append$(bin_ext)
io_seek_append_file := $(tmp_path)/$(io_prefix)_append.file

io_seek: $(io_seek_append_binout)
io_seek_test: io_seek_append_test

io_seek_append_test: $(io_seek_append_binout)
	$(io_seek_append_binout) $(io_seek_append_file)
	cat $(io_seek_append_file)

$(io_seek_append_binout): $(io_root)/seek/a.c
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


# struct
io_struct_binout := $(bin_path)/$(io_prefix)_struct$(bin_ext)
io_struct_open := $(tmp_path)/$(io_prefix)_struct.open

io_struct: $(io_struct_binout)
io_struct_test: io_struct
	-$(io_struct_binout) $(io_struct_open)

$(io_struct_binout): $(io_root)/struct/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
