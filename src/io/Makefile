#
# ./configure --has-io
#
#

ifeq ($(CC_NAME), msvc)
io:
	@echo "#skip ..."
io_test:
	@echo "#skip ..."
else

io: io_access                                   \
    io_copy                                     \
    io_dup                                      \
    io_fcntl                                    \
    io_ls                                       \
    io_own                                      \
    io_redirect                                 \
    io_share                                    \
    io_seek                                     \
    io_size                                     \
    io_stat                                     \
    io_struct                                   \
    io_sync                                     \
    io_umask

io_test: io_access_test                         \
         io_copy_test                           \
         io_dup_test                            \
         io_fcntl_test                          \
         io_ls_test                             \
         io_own_test                            \
         io_redirect_test                       \
         io_share_test                          \
         io_seek_test                           \
         io_size_test                           \
         io_stat_test                           \
         io_struct_test                         \
         io_sync_test                           \
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
CFLAGS += $(f_sanitize)
endif


# access
io_access_open_binout := $(bin_path)/$(io_prefix)_access_open$(bin_ext)
io_access_at_binout := $(bin_path)/$(io_prefix)_access_at$(bin_ext)

io_access_open_file := $(tmp_path)/$(io_prefix)_access_open_file
io_access_open_link := $(tmp_path)/$(io_prefix)_access_open_link

io_access: $(io_access_open_binout)             \
           $(io_access_at_binout)
io_access_test: io_access_open_test             \
                io_access_at_test

io_access_open_test: $(io_access_open_binout)   \
                     $(io_access_open_file)     \
                     $(io_access_open_link)
	ls -lh $(shell which passwd)
	$< $(io_access_open_file)
	# sudo chown root:root $(io_access_open_file)
	# sudo chown root $(io_access_open_binout) && sudo chmod u+s $<
	# $< $(io_access_open_file)

io_access_at_test: $(io_access_at_binout)       \
                   $(io_access_open_file)       \
                   $(io_access_open_link)
	ls -lh $(shell which passwd)
	$< $(io_access_open_file)

$(io_access_open_file):
	echo "abc" > $@
	chmod 400 $@
	ls -lh $@
$(io_access_open_link): $(io_access_open_file)
	ln -s $(CURDIR)/$< $@

$(io_access_open_binout): $(io_root)/access/a.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_access_at_binout): $(io_root)/access/aat.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# copy
io_copy_unbuf_binout := $(bin_path)/$(io_prefix)_copy_unbuf$(bin_ext)
io_copy_stdbuf_binout := $(bin_path)/$(io_prefix)_copy_stdbuf$(bin_ext)

io_copy: $(io_copy_unbuf_binout)                \
         $(io_copy_stdbuf_binout)
io_copy_test: io_copy_unbuf_test                \
              io_copy_stdbuf_test

io_copy_unbuf_test: $(io_copy_unbuf_binout)
	echo "abc\ndef" | $<
	$< < $(io_root)/copy/unbuf.c

io_copy_stdbuf_test: $(io_copy_stdbuf_binout)
	echo "abc\ndef" | $<
	$< < $(io_root)/copy/stdbuf.c

$(io_copy_unbuf_binout): $(io_root)/copy/unbuf.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_copy_stdbuf_binout): $(io_root)/copy/stdbuf.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@
	# sudo chown root $@

# dup
io_dup_fdft_binout := $(bin_path)/$(io_prefix)_dup_fdft$(bin_ext)
io_dup_g2_binout := $(bin_path)/$(io_prefix)_dup_g2$(bin_ext)
io_dup_fdft_file := $(tmp_path)/$(io_prefix)_dup_fdft.file


io_dup: $(io_dup_fdft_binout)                   \
        $(io_dup_g2_binout)
io_dup_test: io_dup_fdft_test                   \
             io_dup_g2_test

io_dup_fdft_test: $(io_dup_fdft_binout)
	$< $(io_dup_fdft_file)
io_dup_g2_test: $(io_dup_g2_binout)
	$< 1 < /dev/null

$(io_dup_g2_file):
	touch $@

$(io_dup_fdft_binout): $(io_root)/dup/fdft.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dup_g2_binout): $(io_root)/dup/g2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# fcntl
io_fcntl_fl_binout := $(bin_path)/$(io_prefix)_fcntl_fl$(bin_ext)
io_fcntl_sfl_binout := $(bin_path)/$(io_prefix)_fcntl_sfl$(bin_ext)
io_fcntl_fl_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_fcntl_fl.file
io_fcntl_sfl_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_fcntl_sfl.file

io_fcntl: $(io_fcntl_fl_binout)               \
          $(io_fcntl_sfl_binout)
io_fcntl_test: io_fcntl_fl_test               \
                io_fcntl_sfl_test

io_fcntl_fl_test: $(io_fcntl_fl_binout)       \
                   $(io_fcntl_fl_file)
	$< 0 < /dev/null
	$< 1 < /dev/null
	$< 2 < /dev/null
	$< 1 > $(io_fcntl_fl_file)
	cat $(io_fcntl_fl_file)
	$< 0 < $(io_fcntl_fl_file)
	$< 2 2>> $(io_fcntl_fl_file)
	$< 5 5<> $(io_fcntl_fl_file)

io_fcntl_sfl_test: $(io_fcntl_sfl_binout)
	$< $(io_fcntl_sfl_file)
	$< /dev/fd/0

$(io_fcntl_fl_file):
	touch $@

$(io_fcntl_fl_binout): $(io_root)/fcntl/fl.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_fcntl_sfl_binout): $(io_root)/fcntl/sfl.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# ls
io_ls_raw_binout := $(bin_path)/$(io_prefix)_ls_raw$(bin_ext)

io_ls: $(io_ls_raw_binout)
io_ls_test: io_ls_raw_test

io_ls_raw_test: $(io_ls_raw_binout)
	$< $(CURDIR)
	$< /dev/fd

$(io_ls_raw_binout): $(io_root)/ls/l1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# own
io_own_binout := $(bin_path)/$(io_prefix)_own$(bin_ext)

io_own: $(io_own_binout)
io_own_test: io_own
	$(io_own_binout)

$(io_own_binout): $(io_root)/own/o1.c
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
io_seek_append_binout := $(bin_path)/$(io_prefix)_seek_append$(bin_ext)
io_seek_able_binout := $(bin_path)/$(io_prefix)_seek_able$(bin_ext)
io_seek_hole_binout := $(bin_path)/$(io_prefix)_seek_hole$(bin_ext)
io_seek_append_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_append.file
io_seek_hole_has_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_hole_has.file
io_seek_hole_non_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_hole_non.file

io_seek: $(io_seek_append_binout)               \
         $(io_seek_able_binout)                 \
         $(io_seek_hole_binout)
io_seek_test: io_seek_append_test               \
              io_seek_able_test                 \
              io_seek_hole_test

io_seek_append_test: $(io_seek_append_binout)
	$< $(io_seek_append_file)
	cat $(io_seek_append_file)

io_seek_able_test: $(io_seek_able_binout)
	$< 0
	$< 1
	$< 2
	$< 0 < /dev/null
	$< 0 < $<
	cat < $(io_root)/seek/able.c | $< 0

io_seek_hole_test: $(io_seek_hole_binout)
	$< $(io_seek_hole_non_file)
	$< $(io_seek_hole_has_file) 16384
	ls -s $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_hole*
	du -s $(tmp_path)/$(io_prefix)_seek_hole*
	wc -c $(tmp_path)/$(io_prefix)_seek_hole*
	od -c $(io_seek_hole_has_file)

$(io_seek_append_binout): $(io_root)/seek/a.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_seek_able_binout): $(io_root)/seek/able.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_seek_hole_binout): $(io_root)/seek/hole.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# size
io_size_binout := $(bin_path)/$(io_prefix)_size$(bin_ext)
io_size_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_size.file
io_size_link := $(tmp_path)/$(io_prefix)_size.link

io_size: $(io_size_binout)                      \
         $(io_size_file)                        \
         $(io_size_link)
io_size_test: io_size
	ls -lh $(tmp_path)
	$(io_size_binout) $(io_size_binout)
	$(io_size_binout) $(io_size_file)
	$(io_size_binout) $(io_size_link)

$(io_size_file):
	touch $@
$(io_size_link): $(io_size_file)
	ln -s $< $@

$(io_size_binout): $(io_root)/size/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stat
io_stat_ft_binout := $(bin_path)/$(io_prefix)_stat_ft$(bin_ext)
io_stat_uid_binout := $(bin_path)/$(io_prefix)_stat_uid$(bin_ext)
io_stat_d_binout := $(bin_path)/$(io_prefix)_stat_d$(bin_ext)
io_stat_ft_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_stat.file
io_stat_d_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_stat_d.file

io_stat: $(io_stat_ft_binout)                   \
         $(io_stat_uid_binout)                  \
         $(io_stat_d_binout)
io_stat_test: io_stat_ft_test                   \
              io_stat_uid_test                  \
              io_stat_d_test

io_stat_ft_test: $(io_stat_ft_binout)           \
                 $(io_stat_ft_file)
	$< $(CURDIR)/$(bin_path) $(io_stat_ft_file) /dev/null $<
	echo "abc" | $< /dev/fd/0

io_stat_uid_test: $(io_stat_uid_binout)
	$< $<
	chmod ug+s $<
	$< $<

io_stat_d_test: $(io_stat_d_binout)             \
                $(io_stat_d_file)
	echo "abc" | $<
	$< $< $(io_stat_d_file) /dev/null $(bin_path)

$(io_stat_ft_file): $(io_stat_ft_binout)
	ln -s $< $@

$(io_stat_d_file): $(io_stat_d_binout)
	ln -s $< $@

$(io_stat_ft_binout): $(io_root)/stat/ft.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_stat_uid_binout): $(io_root)/stat/uid.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_stat_d_binout): $(io_root)/stat/stat1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# struct
io_struct_binout := $(bin_path)/$(io_prefix)_struct$(bin_ext)
io_struct_open := $(tmp_path)/$(io_prefix)_struct.open

io_struct: $(io_struct_binout)
io_struct_test: io_struct
	-$(io_struct_binout) $(io_struct_open)

$(io_struct_binout): $(io_root)/struct/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# sync
io_sync_binout := $(bin_path)/$(io_prefix)_sync$(bin_ext)

io_sync: $(io_sync_binout)
io_sync_test: io_sync
	$(io_sync_binout)

$(io_sync_binout): $(io_root)/sync/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# temp
io_temp_binout := $(bin_path)/$(io_prefix)_temp$(bin_ext)

io_temp: $(io_temp_binout)
io_temp_test: io_temp
	$(io_temp_binout) /tmp

$(io_temp_binout): $(io_root)/temp/t.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# umask
io_umask_create_binout := $(bin_path)/$(io_prefix)_umask_create$(bin_ext)
io_umask_change_binout := $(bin_path)/$(io_prefix)_umask_change$(bin_ext)
io_umask_change_file := $(tmp_path)/$(io_prefix)_umask_change.file

io_umask: $(io_umask_create_binout)             \
          $(io_umask_change_binout)
io_umask_test: io_umask_create_test             \
               io_umask_change_test

io_umask_create_test: $(io_umask_create_binout)
	$< $(CURDIR)/$(tmp_path)
	touch $(tmp_path)/x
	mkdir $(tmp_path)/y
	umask
	umask -S
	ls -lh $(tmp_path)

io_umask_change_test: $(io_umask_change_binout) \
                      $(io_umask_change_file)
	ls -lh $(io_umask_change_file)
	$< $(io_umask_change_file)
	ls -lh $(io_umask_change_file)

$(io_umask_change_file):
	touch $@

$(io_umask_create_binout): $(io_root)/umask/u1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_umask_change_binout): $(io_root)/umask/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
