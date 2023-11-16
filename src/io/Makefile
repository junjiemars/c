#
# ./configure --has-io
#
#

ifeq ($(NM_SYSTEM),WinNT)
io:
	@echo "#skip ..."
io_test:
	@echo "#skip ..."
else

io:                                             \
    io_access                                   \
    io_adv                                      \
    io_close                                    \
    io_copy                                     \
    io_dir                                      \
    io_dup                                      \
    io_fcntl                                    \
    io_link                                     \
    io_ls                                       \
    io_name                                     \
    io_open                                     \
    io_own                                      \
    io_read                                     \
    io_redirect                                 \
    io_rename                                   \
    io_share                                    \
    io_seek                                     \
    io_size                                     \
    io_stat                                     \
    io_struct                                   \
    io_sync                                     \
    io_time                                     \
    io_trunc                                    \
    io_umask

io_test:                                        \
         io_access_test                         \
         io_adv_test                            \
         io_close_test                          \
         io_copy_test                           \
         io_dir_test                            \
         io_dup_test                            \
         io_fcntl_test                          \
         io_link_test                           \
         io_ls_test                             \
         io_name_test                           \
         io_open_test                           \
         io_own_test                            \
         io_read_test                           \
         io_redirect_test                       \
         io_rename_test                         \
         io_share_test                          \
         io_seek_test                           \
         io_size_test                           \
         io_stat_test                           \
         io_struct_test                         \
         io_sync_test                           \
         io_time_test                           \
         io_trunc_test                          \
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

stat := stat
ifeq ($(NM_SYSTEM), Darwin)
stat := stat -x
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
	echo "#!/bin/sh\necho abc" > $@
	chmod 400 $@
	ls -lh $@

$(io_access_open_link): $(io_access_open_file)
	ln -s $(CURDIR)/$< $@

$(io_access_open_binout): $(io_root)/access/a.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_access_at_binout): $(io_root)/access/aat.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# adv
io_adv_nonblk_binout := $(bin_path)/$(io_prefix)_adv_nonblk$(bin_ext)
io_adv_lock_binout := $(bin_path)/$(io_prefix)_adv_lock$(bin_ext)
io_adv_mmap_binout := $(bin_path)/$(io_prefix)_adv_mmap$(bin_ext)
io_adv_out_file1 := $(tmp_path)/$(io_prefix)_adv_out.file1
io_adv_out_file2 := $(tmp_path)/$(io_prefix)_adv_out.file2

io_adv: $(io_adv_nonblk_binout)                 \
        $(io_adv_lock_binout)                   \
        $(io_adv_mmap_binout)
io_adv_test: io_adv_nonblk_test                 \
             io_adv_lock_test                   \
             io_adv_mmap_test

io_adv_nonblk_test: $(io_adv_nonblk_binout)
	ls -lh /etc/services
	$< </etc/services >$(io_adv_out_file1)
	ls -l $(io_adv_out_file1)
	$< </etc/services 2>$(io_adv_out_file2)
	ls -l $(io_adv_out_file2)

io_adv_lock_test: $(io_adv_lock_binout)
	$< <$(out)/Makefile

io_adv_mmap_test: $(io_adv_mmap_binout)
	time $< $(io_root)/Makefile $(io_adv_out_file1) \
		&& diff $(io_root)/Makefile $(io_adv_out_file1)

$(io_adv_nonblk_binout): $(io_root)/adv/nonblk1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_adv_lock_binout): $(io_root)/adv/lock.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_adv_mmap_binout): $(io_root)/adv/m1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# close
io_close_binout := $(bin_path)/$(io_prefix)_close$(bin_ext)

io_close: $(io_close_binout)
io_close_test: io_close
	$(io_close_binout)

$(io_close_binout): $(io_root)/close/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# copy
io_copy_unbuf_binout := $(bin_path)/$(io_prefix)_copy_unbuf$(bin_ext)
io_copy_stdbuf_binout := $(bin_path)/$(io_prefix)_copy_stdbuf$(bin_ext)
io_copy_hole_binout := $(bin_path)/$(io_prefix)_copy_hole$(bin_ext)
io_copy_file := $(tmp_path)/$(io_prefix)_copy_file

io_copy: $(io_copy_unbuf_binout)                \
         $(io_copy_stdbuf_binout)               \
         $(io_copy_cp_binout)
io_copy_test: io_copy_unbuf_test                \
              io_copy_stdbuf_test               \
              io_copy_hole_test

io_copy_unbuf_test: $(io_copy_unbuf_binout)
	echo "abc\ndef" | $<
	$< < $(io_root)/copy/unbuf.c

io_copy_stdbuf_test: $(io_copy_stdbuf_binout)
	echo "abc\ndef" | $<
	$< < $(io_root)/copy/stdbuf.c

io_copy_hole_test: $(io_copy_hole_binout)
	$< $(CURDIR)/$(io_root)/copy/hole1.c $(CURDIR)/$(io_copy_file)  \
    && cat $(CURDIR)/$(io_copy_file)
	$< $(CURDIR)/$(io_root)/copy/hole $(CURDIR)/$(io_copy_file)_X \
    && cat $(CURDIR)/$(io_copy_file)_X

$(io_copy_unbuf_binout): $(io_root)/copy/unbuf.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_copy_stdbuf_binout): $(io_root)/copy/stdbuf.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@
	# sudo chown root $@

$(io_copy_hole_binout): $(io_root)/copy/hole1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# dir
io_dir_raw_binout := $(bin_path)/$(io_prefix)_dir_raw$(bin_ext)
io_dir_mk_binout := $(bin_path)/$(io_prefix)_dir_mk$(bin_ext)
io_dir_itor_binout := $(bin_path)/$(io_prefix)_dir_itor$(bin_ext)
io_dir_tell_binout := $(bin_path)/$(io_prefix)_dir_tell$(bin_ext)
io_dir_deep_binout := $(bin_path)/$(io_prefix)_dir_deep$(bin_ext)
io_dir_prefix := $(tmp_path)/$(io_prefix)_dir

io_dir: $(io_dir_raw_binout)                    \
        $(io_dir_mk_binout)                     \
        $(io_dir_itor_binout)                   \
        $(io_dir_tell_binout)
io_dir_test: io_dir_raw_test                    \
             io_dir_mk_test                     \
             io_dir_itor_test                   \
             io_dir_tell_test

io_dir_raw_test: $(io_dir_raw_binout)
	$< $(CURDIR)/$(io_root)/dir

io_dir_mk_test: $(io_dir_mk_binout)
	mkdir -p $(io_dir_prefix)
	$< $(io_dir_prefix) a b c && ls -lh $(io_dir_prefix)
	echo "abc" > $(io_dir_prefix)/c/xxx
	-$< $(io_dir_prefix) c

io_dir_itor_test: $(io_dir_itor_binout)
	$< $(CURDIR)/$(io_root)/dir/itor.c
	$< $(CURDIR)/$(io_root)

io_dir_tell_test: $(io_dir_tell_binout)
	$< $(CURDIR)/$(bin_path)

io_dir_deep_test: $(io_dir_deep_binout)
	$< /tmp

$(io_dir_raw_binout): $(io_root)/dir/r1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dir_mk_binout): $(io_root)/dir/d1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dir_itor_binout): $(io_root)/dir/itor.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dir_tell_binout): $(io_root)/dir/d2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dir_deep_binout): $(io_root)/dir/deep.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# dup
io_dup_raw_binout := $(bin_path)/$(io_prefix)_dup_raw$(bin_ext)
io_dup_raw2_binout := $(bin_path)/$(io_prefix)_dup_raw2$(bin_ext)
io_dup_fdft_binout := $(bin_path)/$(io_prefix)_dup_fdft$(bin_ext)
io_dup_close_binout := $(bin_path)/$(io_prefix)_dup_close$(bin_ext)
io_dup_fdft_file := $(tmp_path)/$(io_prefix)_dup_fdft.file


io_dup: $(io_dup_raw_binout)                    \
        $(io_dup_raw2_binout)                   \
        $(io_dup_fdft_binout)                   \
        $(io_dup_close_binout)
io_dup_test: io_dup_raw_test                    \
             io_dup_raw2_test                   \
             io_dup_fdft_test                   \
             io_dup_close_test

io_dup_raw_test: $(io_dup_raw_binout)
	$< < $(io_root)/dup/d.c
io_dup_raw2_test: $(io_dup_raw2_binout)
	$< < $(io_root)/dup/d2.c
io_dup_fdft_test: $(io_dup_fdft_binout)
	$< $(io_dup_fdft_file)
io_dup_close_test: $(io_dup_close_binout)
	$< 1 1< /dev/null
	$< 3 3< /dev/null

$(io_dup_g2_file):
	touch $@

$(io_dup_raw_binout): $(io_root)/dup/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dup_raw2_binout): $(io_root)/dup/d2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dup_fdft_binout): $(io_root)/dup/fdft.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_dup_close_binout): $(io_root)/dup/close.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# fcntl
io_fcntl_dup_binout := $(bin_path)/$(io_prefix)_fcntl_dup$(bin_ext)
io_fcntl_fl_binout := $(bin_path)/$(io_prefix)_fcntl_fl$(bin_ext)
io_fcntl_sfl_binout := $(bin_path)/$(io_prefix)_fcntl_sfl$(bin_ext)
io_fcntl_fl_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_fcntl_fl.file
io_fcntl_sfl_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_fcntl_sfl.file
io_fcntl_affect_binout := $(bin_path)/$(io_prefix)_fcntl_affect$(bin_ext)

io_fcntl: $(io_fcntl_dup_binout)                \
          $(io_fcntl_fl_binout)                 \
          $(io_fcntl_sfl_binout)                \
          $(io_fcntl_affect_binout)
io_fcntl_test: io_fcntl_dup_test                \
               io_fcntl_fl_test                 \
               io_fcntl_sfl_test                \
               io_fcntl_affect_test

io_fcntl_dup_test: $(io_fcntl_dup_binout)
	$< < $(io_root)/fcntl/d.c

io_fcntl_fl_test: $(io_fcntl_fl_binout)         \
                  $(io_fcntl_fl_file)
	$< 0
	$< 1
	$< 2
	$< 0 < /dev/null
	$< 1 < /dev/null
	$< 2 < /dev/null
	$< 0 < $(io_fcntl_fl_file)
	$< 1 < $(io_fcntl_fl_file)
	$< 2 < $(io_fcntl_fl_file)
	$< 1 1> $(io_fcntl_fl_file) && cat $(io_fcntl_fl_file)
	$< 2 2>> $(io_fcntl_fl_file)
	$< 5 5<> $(io_fcntl_fl_file)

io_fcntl_sfl_test: $(io_fcntl_sfl_binout)
	$< $(io_fcntl_sfl_file)
	$< /dev/fd/0

$(io_fcntl_fl_file):
	touch $@

io_fcntl_affect_test: $(io_fcntl_affect_binout)
	$< $<

$(io_fcntl_dup_binout): $(io_root)/fcntl/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_fcntl_fl_binout): $(io_root)/fcntl/fl.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_fcntl_sfl_binout): $(io_root)/fcntl/sfl.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_fcntl_affect_binout): $(io_root)/fcntl/aff.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# link
io_link_hard_binout := $(bin_path)/$(io_prefix)_link_hard$(bin_ext)
io_link_un_binout := $(bin_path)/$(io_prefix)_link_un$(bin_ext)
io_link_rmdir_binout := $(bin_path)/$(io_prefix)_link_rmdir$(bin_ext)
io_link_rm_binout := $(bin_path)/$(io_prefix)_link_rm$(bin_ext)
io_link_sym_binout := $(bin_path)/$(io_prefix)_link_sym$(bin_ext)
io_link_read_binout := $(bin_path)/$(io_prefix)_link_read$(bin_ext)
io_link_dir := $(tmp_path)/$(io_prefix)_link_dir
io_link_file := $(tmp_path)/$(io_prefix)_link_file

io_link: $(io_link_hard_binout)                 \
         $(io_link_un_binout)                   \
         $(io_link_rm_binout)                   \
         $(io_link_rmdir_binout)                \
         $(io_link_sym_binout)                  \
         $(io_link_read_binout)
io_link_test: io_link_hard_test                 \
              io_link_un_test                   \
              io_link_rm_test                   \
              io_link_rmdir_test                \
              io_link_sym_test                  \
              io_link_read_test

io_link_hard_test: $(io_link_hard_binout)
	$< $< $(io_link_file) && ls -lh $(io_link_file)

io_link_un_test: $(io_link_un_binout)
	mkdir -p $(io_link_dir) && echo "abc" > $(io_link_file) && ls -lh $(tmp_path)
	$< $(io_link_file) && ls -lh $(tmp_path)
	$< $(io_link_dir) && ls -lh $(tmp_path)

io_link_rm_test: $(io_link_rm_binout)
	mkdir -p $(io_link_dir) && echo "abc" > $(io_link_file) && ls -lh $(tmp_path)
	$< $(io_link_file) && ls -lh $(tmp_path)
	$< $(io_link_dir) && ls -lh $(tmp_path)

io_link_rmdir_test: $(io_link_rmdir_binout)
	mkdir -p $(io_link_dir) && ls -lh $(tmp_path)
	$< $(io_link_dir) && ls -lh $(tmp_path)

io_link_sym_test: $(io_link_sym_binout)
	$< $(io_root)/link/sym1.c $(io_link_file) && ls -F $(io_link_file)
	-rm -rf $(io_link_dir) $(io_link_file)            \
    && $< $(CURDIR)/$(io_link_dir) $(io_link_file)  \
    && test -d $(io_link_dir)                       \
    || mkdir -p $(io_link_dir)                      \
    && echo "abc" > $(io_link_dir)/zzz              \
    && cat $(io_link_file)/zzz

io_link_read_test: $(io_link_read_binout)
	ln -s $(CURDIR)/$^ $(io_link_file) && readlink $(io_link_file)
	$< $(io_link_file)
	-$< $^

$(io_link_hard_binout): $(io_root)/link/lk1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_link_un_binout): $(io_root)/link/ulk1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_link_rm_binout): $(io_root)/link/rm.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_link_rmdir_binout): $(io_root)/link/rd.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_link_sym_binout): $(io_root)/link/sym1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_link_read_binout): $(io_root)/link/rl.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# ls
io_ls_raw_binout := $(bin_path)/$(io_prefix)_ls_raw$(bin_ext)

io_ls: $(io_ls_raw_binout)
io_ls_test: io_ls_raw_test

io_ls_raw_test: $(io_ls_raw_binout)
	$< $(out)

$(io_ls_raw_binout): $(io_root)/ls/l1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# name
io_name_binout := $(bin_path)/$(io_prefix)_name$(bin_ext)

io_name: $(io_name_binout)
io_name_test: io_name
	-$(io_name_binout) $(io_root)/name/n.c \
		256xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

$(io_name_binout): $(io_root)/name/n.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# open
io_open_at_binout := $(bin_path)/$(io_prefix)_open_at$(bin_ext)
io_open_at_dir_binout := $(bin_path)/$(io_prefix)_open_at_dir$(bin_ext)
io_open_max_binout := $(bin_path)/$(io_prefix)_open_max$(bin_ext)
io_open_cloexec_binout := $(bin_path)/$(io_prefix)_open_cloexec$(bin_ext)
io_open_sync_binout := $(bin_path)/$(io_prefix)_open_sync$(bin_ext)
io_open_creat_binout := $(bin_path)/$(io_prefix)_open_creat$(bin_ext)
io_open_creat1_binout := $(bin_path)/$(io_prefix)_open_creat1$(bin_ext)
io_open_duff_binout := $(bin_path)/$(io_prefix)_open_duff$(bin_ext)
io_open_file := $(tmp_path)/$(io_prefix)_open_file
io_open_dir := $(tmp_path)/$(io_prefix)_open_dir

io_open: $(io_open_at_binout)                   \
         $(io_open_at_dir_binout)               \
         $(io_open_max_binout)                  \
         $(io_open_cloexec_binout)              \
         $(io_open_sync_binout)                 \
         $(io_open_creat_binout)                \
         $(io_open_creat1_binout)               \
         $(io_open_duff_bintout)
io_open_test: io_open_at_test                   \
              io_open_at_dir_test               \
              io_open_max_test                  \
              io_open_cloexec_test              \
              io_open_sync_test                 \
              io_open_creat_test                \
              io_open_creat1_test               \
              io_open_duff_test

io_open_at_test: $(io_open_at_binout)
	$< $(io_root)/open/o1.c
	ln -s $(tmp_path)/$(io_prefix)/no/such/file $(io_open_file)
	-$< $(io_open_file)
	mkdir -p $(io_open_dir) && $< $(io_open_dir)

io_open_at_dir_test: $(io_open_at_dir_binout)
	-$< $(io_root)/open
	-$< $(io_root)/open/o2.c

io_open_max_test: $(io_open_max_binout)
	-$< $(io_root)/open/256xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

io_open_cloexec_test: $(io_open_cloexec_binout)
	$< $(tmp_path)/$(io_prefix)_open_cloexec_file

io_open_sync_test: $(io_open_sync_binout)
	$< $(tmp_path)/$(io_prefix)_open_sync_file

io_open_creat_test: $(io_open_creat_binout)
	-rm $(io_open_file)
	$< $(io_open_file) && ls -lh $(io_open_file) && cat $(io_open_file)
	echo "ABC" > $(io_open_file) && cat $(io_open_file)       \
    && chmod a-r $(io_open_file) && ls -lh $(io_open_file)  \
	  && $< $(io_open_file) && ls -lh $(io_open_file)         \
    && chmod u+r $(io_open_file) && ls -lh $(io_open_file)  \
    && cat $(io_open_file)

io_open_creat1_test: $(io_open_creat1_binout)
	-rm $(io_open_file)
	$< $(io_open_file) && ls -lh $(io_open_file)
	chmod a-r $(io_open_file) && ls -lh $(io_open_file)
	-$< $(io_open_file) && ls -lh $(io_open_file)

io_open_duff_test: $(io_open_duff_binout)
	-$<
	-$< /dev/fd/1
	-$< /dev/fd/2

$(io_open_at_binout): $(io_root)/open/o1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_open_at_dir_binout): $(io_root)/open/o2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_open_max_binout): $(io_root)/open/max.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_open_cloexec_binout): $(io_root)/open/cloexec.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_open_sync_binout): $(io_root)/open/sync.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_open_creat_binout): $(io_root)/open/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_open_creat1_binout): $(io_root)/open/c2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_open_duff_binout): $(io_root)/open/duff.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# own
io_own_binout := $(bin_path)/$(io_prefix)_own$(bin_ext)

io_own: $(io_own_binout)
io_own_test: io_own
	$(io_own_binout)

$(io_own_binout): $(io_root)/own/o1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# read
io_read_raw_binout := $(bin_path)/$(io_prefix)_read_raw$(bin_ext)
io_read_iov_binout := $(bin_path)/$(io_prefix)_read_iov$(bin_ext)

io_read: $(io_read_raw_binout)                  \
         $(io_read_iov_binout)
io_read_test: io_read_raw_test                  \
              io_read_iov_test

io_read_raw_test: $(io_read_raw_binout)
	$< <$(io_root)/read/r1.c
	$< <$(out)/nore.h

io_read_iov_test: $(io_read_iov_binout)
	$< <$(io_root)/read/r2.c
	$< <$(out)/nore.h

$(io_read_raw_binout): $(io_root)/read/r1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_read_iov_binout): $(io_root)/read/r2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# redirect
io_redirect_binout := $(bin_path)/$(io_prefix)_redirect$(bin_ext)
io_redirect_out1 := $(tmp_path)/$(io_prefix)_redirect.out1
io_redirect_out2 := $(tmp_path)/$(io_prefix)_redirect.out2

io_redirect: $(io_redirect_binout)
io_redirect_test: io_redirect
	$(io_redirect_binout)
	$(io_redirect_binout) > $(io_redirect_out1) 2>&1
	cat $(io_redirect_out1)
	$(io_redirect_binout) 2>&1 >$(io_redirect_out2)
	cat $(io_redirect_out2)

$(io_redirect_binout): $(io_root)/redirect/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# rename
io_rename_binout := $(bin_path)/$(io_prefix)_rename$(bin_ext)
io_rename_prefix := $(tmp_path)/$(io_prefix)_rename

io_rename: $(io_rename_binout)
io_rename_test: io_rename_file_test             \
                io_rename_dir_test

io_rename_file_test: $(io_rename_binout)
	echo "abc" > $(io_rename_prefix)_X && ls -lh $(tmp_path)
	$< $(io_rename_prefix)_X $(io_rename_prefix)_X && ls -lh $(tmp_path)
	$< $(io_rename_prefix)_X $(io_rename_prefix)_Z && ls -lh $(tmp_path)
	echo "def" > $(io_rename_prefix)_Y && ls -lh $(tmp_path)
	$< $(io_rename_prefix)_Y $(io_rename_prefix)_Z  \
    && ls -lh $(tmp_path)                         \
    && cat $(io_rename_prefix)_Z

io_rename_dir_test: $(io_rename_binout)
	rm -rf $(io_rename_prefix)_* && mkdir -p $(io_rename_prefix)_X  \
    && ls -lh $(tmp_path)
	$< $(io_rename_prefix)_X $(io_rename_prefix)_X && ls -lh $(tmp_path)
	$< $(io_rename_prefix)_X $(io_rename_prefix)_Z && ls -lh $(tmp_path)
	mkdir -p $(io_rename_prefix)_Y                \
    && echo "abc" > $(io_rename_prefix)_Y/yyy   \
    && find $(io_rename_prefix)_Y
	mkdir -p $(io_rename_prefix)_Z                \
    && echo "def" > $(io_rename_prefix)_Z/zzz   \
    && ls -lh $(tmp_path)
	-$< $(io_rename_prefix)_Z $(io_rename_prefix)_Y
	rm $(io_rename_prefix)_Y/yyy                        \
    && $< $(io_rename_prefix)_Z $(io_rename_prefix)_Y \
    && ls -lh $(io_rename_prefix)_Y


$(io_rename_file):
	echo "abc" > $@

$(io_rename_binout): $(io_root)/rename/r1.c
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
	-rm $(io_share1_out)
	$< $(io_share1_out)
	sleep 1
	wc -c $(io_share1_out)

io_share2_test: $(io_share2_binout)
	-rm $(io_share2_out)
	$< $(io_share2_out)
	sleep 1
	wc -c $(io_share2_out)

io_share3_test: $(io_share3_binout)
	-rm $(io_share3_out)
	$< $(io_share3_out)
	sleep 1
	wc -c $(io_share3_out)

$(io_share1_binout): $(io_root)/share/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_N_=1000 $^ $(bin_out)$@

$(io_share2_binout): $(io_root)/share/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_N_=1000 $^ $(bin_out)$@

$(io_share3_binout): $(io_root)/share/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_N_=1000 -D_PWRITE_ $^ $(bin_out)$@

# seek
io_seek_append_binout := $(bin_path)/$(io_prefix)_seek_append$(bin_ext)
io_seek_able_binout := $(bin_path)/$(io_prefix)_seek_able$(bin_ext)
io_seek_hole_binout := $(bin_path)/$(io_prefix)_seek_hole$(bin_ext)
io_seek_hole_find_binout := $(bin_path)/$(io_prefix)_seek_hole_find$(bin_ext)
io_seek_append_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_append.file
io_seek_hole_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_hole.file
io_seek_hole_non_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_hole_non.file

io_seek: $(io_seek_append_binout)               \
         $(io_seek_able_binout)                 \
         $(io_seek_hole_binout)                 \
         $(io_seek_hole_find_binout)
io_seek_test: io_seek_append_test               \
              io_seek_able_test                 \
              io_seek_hole_test                 \
              io_seek_hole_find_test

io_seek_append_test: $(io_seek_append_binout)
	$< $(io_seek_append_file)
	cat $(io_seek_append_file) && echo

io_seek_able_test: $(io_seek_able_binout)
	$< 0 1 2
	$< 0 < /dev/null
	$< 0 < $<
	$< 0 < $(bin_path)
	cat < $(io_root)/seek/able.c | $< 0

io_seek_hole_test: $(io_seek_hole_binout)
	$< $(io_seek_hole_non_file)
	$< $(io_seek_hole_file) 40960
	ls -s $(CURDIR)/$(tmp_path)/$(io_prefix)_seek_hole*
	du -s $(tmp_path)/$(io_prefix)_seek_hole*
	wc -c $(tmp_path)/$(io_prefix)_seek_hole*
	od -c $(io_seek_hole_file)

io_seek_hole_find_test: $(io_seek_hole_find_binout) \
                        io_seek_hole_test
	$< $(io_seek_hole_file)

$(io_seek_append_binout): $(io_root)/seek/a.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_seek_able_binout): $(io_root)/seek/able.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_seek_hole_binout): $(io_root)/seek/hole.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_seek_hole_find_binout): $(io_root)/seek/hf.c
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
	$(io_size_binout) $(io_size_binout)           \
    $(io_size_file)                             \
    $(io_size_link)                             \
    /dev/null                                   \
    /dev/zero                                   \
    $(io_root)/size/s1.c                        \
    $(io_root)                                  \
    $(io_root)/size

$(io_size_file):
	touch $@

$(io_size_link): $(io_size_file)
	ln -s $< $@

$(io_size_binout): $(io_root)/size/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stat
io_stat_ft_binout := $(bin_path)/$(io_prefix)_stat_ft$(bin_ext)
io_stat_uid_binout := $(bin_path)/$(io_prefix)_stat_uid$(bin_ext)
io_stat_stat1_binout := $(bin_path)/$(io_prefix)_stat1$(bin_ext)
io_stat_dev_binout := $(bin_path)/$(io_prefix)_dev$(bin_ext)
io_stat_link := $(CURDIR)/$(tmp_path)/$(io_prefix)_stat.link

io_stat: $(io_stat_ft_binout)                   \
         $(io_stat_uid_binout)                  \
         $(io_stat_stat1_binout)                \
         $(io_stat_dev_binout)
io_stat_test: io_stat_ft_test                   \
              io_stat_uid_test                  \
              io_stat_stat1_test                \
              io_stat_dev_test

io_stat_ft_test: $(io_stat_ft_binout)
	rm -f $(io_stat_link)
	ln -s $(CURDIR)/$< $(io_stat_link)
	$< $< $(bin_path) $(io_stat_link) /dev/zero

io_stat_uid_test: $(io_stat_uid_binout)
	ls -lh $< $(shell command -v passwd)
	$< $< $(shell command -v passwd)
	-chmod ug+s $<
	$< $<
	ls -lh $<

io_stat_stat1_test: $(io_stat_stat1_binout)
	rm -f $(io_stat_link)
	ln -s $(CURDIR)/$< $(io_stat_link)
	$< $(bin_path) $(io_stat_link) /dev/zero $(shell command -v passwd)

io_stat_dev_test: $(io_stat_dev_binout)
	-ls -lh $(out)/nore.h /dev/null /dev/zero /dev/tty[01]
	$< $(out)/nore.h /dev/null /dev/zero /dev/tty[01]

$(io_stat_ft_binout): $(io_root)/stat/ft.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_stat_uid_binout): $(io_root)/stat/uid.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_stat_stat1_binout): $(io_root)/stat/stat1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_stat_dev_binout): $(io_root)/stat/dev1.c
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
io_sync_sync_binout := $(bin_path)/$(io_prefix)_sync_sync$(bin_ext)
io_sync_non_binout := $(bin_path)/$(io_prefix)_sync_non$(bin_ext)
io_sync_iov_binout := $(bin_path)/$(io_prefix)_sync_iov$(bin_ext)
io_sync_in_file := $(CURDIR)/$(io_root)/sync/.$(io_prefix)_sync_in.file
io_sync_out_file := $(CURDIR)/$(tmp_path)/$(io_prefix)_sync_out.file
io_sync_blk_size := -DBLK_SIZE=4096

io_sync: $(io_sync_sync_binout)                 \
         $(io_sync_non_binout)                  \
         $(io_sync_iov_binout)
io_sync_test: io_sync_sync_test                 \
              io_sync_non_test                  \
              io_sync_iov_test

io_sync_sync_test: $(io_sync_sync_binout)       \
                   $(io_sync_in_file)
	rm -f $(io_sync_out_file)
	ls -lh $(io_sync_in_file)
	$< $(io_sync_in_file) $(io_sync_out_file)

io_sync_non_test: $(io_sync_non_binout)         \
                  $(io_sync_in_file)
	rm -f $(io_sync_out_file)
	ls -lh $(io_sync_in_file)
	$< $(io_sync_in_file) $(io_sync_out_file)

io_sync_iov_test: $(io_sync_iov_binout)         \
                  $(io_sync_in_file)
	rm -f $(io_sync_out_file)
	ls -lh $(io_sync_in_file)
	$< $(io_sync_in_file) $(io_sync_out_file)


$(io_sync_in_file):
	dd if=/dev/zero of=$@ bs=4096 count=51200

$(io_sync_sync_binout): $(io_root)/sync/s1.c    \
                        $(io_root)/sync/c1.c
	$(CC) -D_SYNC_ $(io_sync_blk_size) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_sync_non_binout): $(io_root)/sync/s1.c     \
                       $(io_root)/sync/c1.c
	$(CC) $(io_sync_blk_size) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_sync_iov_binout): $(io_root)/sync/iov1.c
	$(CC) $(io_sync_blk_size) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# temp
io_temp_binout := $(bin_path)/$(io_prefix)_temp$(bin_ext)

io_temp: $(io_temp_binout)
io_temp_test: io_temp
	$(io_temp_binout) /tmp

$(io_temp_binout): $(io_root)/temp/t.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# time
io_time_raw_binout := $(bin_path)/$(io_prefix)_time_raw$(bin_ext)
io_time_nac_binout := $(bin_path)/$(io_prefix)_time_nac$(bin_ext)
io_time_file := $(tmp_path)/$(io_prefix)_time_file

io_time: $(io_time_raw_binout)                  \
         $(io_time_nac_binout)
io_time_test: io_time_raw_test                  \
              io_time_nac_test

io_time_raw_test: $(io_time_raw_binout)
	$< $(CURDIR)/$(io_root)/time/t1.c
	$(stat) $(io_root)/time/t1.c

io_time_nac_test: $(io_time_nac_binout)
	echo "abc" > $(io_time_file)
	$(stat) $(io_time_file)
	sleep 1
	$< $(io_time_file)
	$(stat) $(io_time_file)

$(io_time_raw_binout): $(io_root)/time/t1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_time_nac_binout): $(io_root)/time/t2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# trunc
io_trunc_binout := $(bin_path)/$(io_prefix)_trunc$(bin_ext)
io_trunc_file := $(tmp_path)/$(io_prefix)_trunc_file

io_trunc: $(io_trunc_binout)
io_trunc_test: io_trunc
	echo -n "abc" > $(io_trunc_file)              \
    && $(io_trunc_binout) $(io_trunc_file) 10   \
    && cat $(io_trunc_file) && echo
	echo -n "abcdefghij" > $(io_trunc_file)       \
    && $(io_trunc_binout) $(io_trunc_file) 3    \
    && cat $(io_trunc_file) && echo


$(io_trunc_binout): $(io_root)/trunc/t1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# umask
io_umask_create_binout := $(bin_path)/$(io_prefix)_umask_create$(bin_ext)
io_umask_change_binout := $(bin_path)/$(io_prefix)_umask_change$(bin_ext)
io_umask_fork_binout := $(bin_path)/$(io_prefix)_umask_fork$(bin_ext)
io_umask_change_file := $(tmp_path)/$(io_prefix)_umask_change.file


io_umask: $(io_umask_create_binout)             \
          $(io_umask_change_binout)             \
          $(io_umask_fork_binout)
io_umask_test: io_umask_create_test             \
               io_umask_change_test             \
               io_umask_fork_test

io_umask_create_test: $(io_umask_create_binout)
	$< $(CURDIR)/$(tmp_path)
	umask
	umask -S
	touch $(tmp_path)/x
	mkdir $(tmp_path)/y
	ls -lh $(tmp_path)

io_umask_change_test: $(io_umask_change_binout) \
                      $(io_umask_change_file)
	ls -lh $(io_umask_change_file)
	$< $(io_umask_change_file)
	ls -lh $(io_umask_change_file)

io_umask_fork_test: $(io_umask_fork_binout)
	$<

$(io_umask_change_file):
	touch $@

$(io_umask_create_binout): $(io_root)/umask/u1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_umask_change_binout): $(io_root)/umask/uc1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(io_umask_fork_binout): $(io_root)/umask/uf1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
