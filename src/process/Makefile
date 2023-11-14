# -*- mode:makefile-gmake -*-
#
# ./configure --has-process
#

ifeq ($(NM_SYSTEM),WinNT)
process:
	@echo "#skip ..."
process_test: process
	@echo "#skip ..."
else

process: process_argv                           \
         process_env                            \
         process_exec                           \
         process_exit                           \
         process_group                          \
         process_id                             \
         process_io                             \
         process_layout                         \
         process_login                          \
         process_main                           \
         process_mmap                           \
         process_nice                           \
         process_orphan                         \
         process_rlimit                         \
         process_time                           \
         process_tty                            \
         process_wait                           \
         process_zombie

process_test: process_argv_test                 \
              process_env_test                  \
              process_exec_test                 \
              process_exit_test                 \
              process_group_test                \
              process_id_test                   \
              process_io_test                   \
              process_layout_test               \
              process_login_test                \
              process_main_test                 \
              process_mmap_test                 \
              process_nice_test                 \
              process_orphan_test               \
              process_rlimit_test               \
              process_time_test                 \
              process_tty_test                  \
              process_wait_test                 \
              process_zombie_test

endif



process_prefix := process
posix_root ?= $(root)/posix
INC += $(nm_inc_opt)$(process_root) $(nm_inc_opt)$(posix_root)

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(f_sanitize)
endif

ifeq ($(NM_SYSTEM),Linux)
	cflags_static_opt := -static
endif



# argv
process_argv_binout := $(bin_path)/$(process_prefix)_argv$(bin_ext)

process_argv: $(process_argv_binout)
process_argv_test: process_argv
	XXX=zZZz $(process_argv_binout) a bb ccc

$(process_argv_binout): $(process_root)/argv/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# env
process_env_raw_binout := $(bin_path)/$(process_prefix)_env_raw$(bin_ext)
process_env_mov_binout := $(bin_path)/$(process_prefix)_env_mov$(bin_ext)
process_env_chld_binout := $(bin_path)/$(process_prefix)_env_chld$(bin_ext)
process_env_xsi_binout := $(bin_path)/$(process_prefix)_env_xsi$(bin_ext)
process_env_xsi_c := $(tmp_path)/$(process_prefix)_env_xsi.c

process_env: $(process_env_raw_binout)          \
             $(process_env_mov_binout)          \
             $(process_env_chld_binout)         \
             $(process_env_xsi_binout)
process_env_test: process_env_raw_test          \
                  process_env_mov_test          \
                  process_env_chld_test         \
                  process_env_xsi_test

process_env_raw_test: $(process_env_raw_binout)
	$<

process_env_mov_test: $(process_env_mov_binout)
	$<

process_env_chld_test: $(process_env_chld_binout)
	$<

process_env_xsi_test: $(process_env_xsi_binout)
	$<

$(process_env_raw_binout): $(process_root)/env/raw.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ $(bin_out)$@

$(process_env_mov_binout): $(process_root)/env/mov.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_env_chld_binout): $(process_root)/env/chld.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_env_xsi_binout): $(process_env_xsi_c)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_env_xsi_c): $(process_root)/env/env.awk.in  \
                      $(process_root)/env/env.awk
	awk -f $(process_root)/env/env.awk $(process_root)/env/env.awk.in >$@



# exec
process_exec_echo := $(process_prefix)_exec_echo$(bin_ext)
process_exec_echo_binout := $(bin_path)/$(process_exec_echo)
process_exec_vary_binout := $(bin_path)/$(process_prefix)_exec_vary$(bin_ext)
process_exec_vary_cppout := $(tmp_path)/$(process_prefix)_exec_vary$(cpp_ext)
process_exec_child_binout := $(bin_path)/$(process_prefix)_exec_child$(bin_ext)
process_exec_ve_binout := $(bin_path)/$(process_prefix)_exec_ve$(bin_ext)
process_exec_path_binout := $(bin_path)/$(process_prefix)_exec_path$(bin_ext)
process_exec_sh  := $(CURDIR)/$(bin_path)/$(process_prefix)_exec_echo.sh
process_exec_awk := $(CURDIR)/$(process_root)/exec/awki.sh

process_exec: $(process_exec_echo_binout)       \
              $(process_exec_vary_binout)       \
              $(process_exec_child_binout)      \
              $(process_exec_ve_binout)         \
              $(process_exec_path_binout)

process_exec_test: process_exec_echo_test       \
                   process_exec_vary_test       \
                   process_exec_child_test      \
                   process_exec_ve_test         \
                   process_exec_path_test

process_exec_echo_test: $(process_exec_echo_binout)
	env -i XXX=zZZz $< a bb ccc

process_exec_vary_test: $(process_exec_vary_binout)   \
                        $(process_exec_echo_binout)
	env -i XXX=zZZz $< "execl"
	env -i XXX=zZZz $< "execl" a bb ccc
	env -i XXX=zZZz PATH="$(CURDIR)/$(bin_path)" $< "execlp" a bb ccc
	env -i XXX=zZZz $< "execle" a bb ccc
	env -i XXX=zZZz $< "execv" a bb ccc
	env -i XXX=zZZz PATH="$(CURDIR)/$(bin_path)" $< "execvp" a bb ccc
	env -i XXX=zZZz $< "execve" a bb ccc

process_exec_child_test: $(process_exec_child_binout) \
                         $(process_exec_echo_binout)
	env -i XXX=zZZz $< a bb ccc

process_exec_ve_test: $(process_exec_ve_binout)   \
                      $(process_exec_echo_binout)
	env -i XXX=zZZz $< "execl" a bb ccc
	env -i XXX=zZZz $< "execle" a bb ccc
	PATH="$(CURDIR)/$(bin_path)" $< "execlp"

process_exec_sh_test: $(process_exec_sh)
	XXX=zZzz $< 1 2

process_exec_awk_test: $(process_exec_awk)
	$< a1 a2 a3

process_exec_path_test: $(process_exec_path_binout) \
                        $(process_exec_sh)
	$< $(process_exec_sh) execl
	PATH=$(CURDIR)/$(bin_path) $< $(process_exec_sh) execlp

$(process_exec_echo_binout): $(process_root)/exec/echo.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_exec_vary_binout): $(process_root)/exec/vary.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                        \
    -D_PATH_NAME_=\"$(CURDIR)/$(process_exec_echo_binout)\" \
    -D_FILE_NAME_=\"$(process_exec_echo)\"                  \
    $^ $(bin_out)$@

$(process_exec_child_binout): $(process_root)/exec/child.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                        \
    -D_PATH_NAME_=\"$(CURDIR)/$(process_exec_echo_binout)\" \
    -D_FILE_NAME_=\"$(process_exec_echo)\"                  \
    -D_WAIT_=0                                              \
    $^ $(bin_out)$@

$(process_exec_sh): $(process_exec_echo_binout)
	echo "#!$(CURDIR)/$< a b c\n\necho void\n" > $@ && chmod u+x $@

$(process_exec_ve_binout): $(process_root)/exec/vary.c  \
                           $(process_root)/exec/ve1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                        \
    -D_PATH_NAME_=\"$(CURDIR)/$(process_exec_echo_binout)\" \
    -D_FILE_NAME_=\"$(process_exec_echo)\"                  \
    $^ $(bin_out)$@

$(process_exec_path_binout): $(process_root)/exec/path1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# exit
process_exit_at_binout := $(bin_path)/$(process_prefix)_exit_at$(bin_ext)
process_exit_state_binout := $(bin_path)/$(process_prefix)_exit_state$(bin_ext)
process_exit_file := $(tmp_path)/$(process_prefix)_exit.file


process_exit: $(process_exit_at_binout)         \
              $(process_exit_state_binout)
process_exit_test: process_exit_at_test         \
                   process_exit_state_test

process_exit_at_test: $(process_exit_at_binout)
	$<

process_exit_state_test: $(process_exit_state_binout)
	$< 0x11223344
	$< 0x11223344 2

$(process_exit_at_binout): $(process_root)/exit/at1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_exit_state_binout): $(process_root)/exit/x1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# group
process_group_id_binout := $(bin_path)/$(process_prefix)_group_id$(bin_ext)
process_group_child_binout := $(bin_path)/$(process_prefix)_group_child$(bin_ext)
process_group_ss_binout := $(bin_path)/$(process_prefix)_group_ss$(bin_ext)

process_group: $(process_group_id_binout)       \
               $(process_group_child_binout)    \
               $(process_group_ss_binout)
process_group_test: process_group_id_test       \
                    process_group_child_test    \
                    process_group_ss_test

process_group_id_test: $(process_group_id_binout)
	echo "make pid=$$PPID"
	-$<

process_group_child_test: $(process_group_child_binout)
	$<

process_group_ss_test: $(process_group_ss_binout)
	echo "make pid=$$PPID"
	$<

$(process_group_id_binout): $(process_root)/group/g1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_group_child_binout): $(process_root)/group/child.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_group_ss_binout): $(process_root)/group/ss1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# id
process_id_get_binout := $(bin_path)/$(process_prefix)_id_get$(bin_ext)
process_id_set_binout := $(bin_path)/$(process_prefix)_id_set$(bin_ext)
process_id_file := $(tmp_path)/$(process_prefix)_id.file

process_id: $(process_id_get_binout)            \
            $(process_id_set_binout)
process_id_test: process_id_get_test            \
                 process_id_set_test

process_id_get_test: $(process_id_get_binout)
	$<
	id
	# sudo chown root $<
	# sudo chmod u+s $<
	# $<

process_id_set_test: $(process_id_set_binout)
	$<
	# -sudo chown root $< && sudo chmod u+s $< && $<

$(process_id_get_binout): $(process_root)/id/id1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_id_set_binout): $(process_root)/id/set1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# io
process_io_buf_binout := $(bin_path)/$(process_prefix)_io_buf$(bin_ext)
process_io_async_binout := $(bin_path)/$(process_prefix)_io_async$(bin_ext)
process_io_sync_binout := $(bin_path)/$(process_prefix)_io_sync$(bin_ext)

process_io: $(process_io_buf_binout)            \
            $(process_io_async_binout)          \
            $(process_io_sync_binout)
process_io_test: process_io_buf_test            \
                 process_io_async_test          \
                 process_io_sync_test

process_io_buf_test: $(process_io_buf_binout)
	$<
	$< >$(tmp_path)/process_io_buf.out && cat $(tmp_path)/process_io_buf.out

process_io_async_test: $(process_io_async_binout)
	$<

process_io_sync_test: $(process_io_sync_binout)
	$<

$(process_io_buf_binout): $(process_root)/io/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_io_async_binout): $(process_root)/io/syn1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_io_sync_binout): $(process_root)/io/syn1.c \
                           $(posix_root)/npsyns.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_SYN_=1 $^ $(bin_out)$@



# layout
process_layout_raw_binout := $(bin_path)/$(process_prefix)_layout_raw$(bin_ext)
process_layout_raw_asmout := $(tmp_path)/$(process_prefix)_layout_raw$(asm_ext)
process_layout_brk_binout := $(bin_path)/$(process_prefix)_layout_brk$(bin_ext)

process_layout: $(process_layout_raw_binout)    \
                $(process_layout_brk_binout)
process_layout_test: process_layout_raw_test    \
                     process_layout_brk_test

process_layout_raw_test: $(process_layout_raw_binout)
	env -i XXX=zZZz $< | sort -k1,1gr
	size $<
	nm $<

ifeq ($(has_brk),yes)
ifneq ($(NM_SYSTEM),Darwin)
process_layout_brk_test: $(process_layout_brk_binout)
	$< | sort -k2,2gr -k1,1nr
	size $<
else
process_layout_brk_test:
	echo "# skipped, 'brk' had been deprecated"
endif
else
process_layout_brk_test:
	echo "# skpped, 'brk' no found"
endif

$(process_layout_raw_binout): $(process_layout_raw_asmout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(process_layout_raw_asmout): $(process_root)/layout/m.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_asm) $^ $(asm_out)$@

$(process_layout_brk_binout): $(process_root)/layout/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# login
process_login_proc_binout := $(bin_path)/$(process_prefix)_login_proc$(bin_ext)
process_login_name ?= abc
process_login_ldlibs =

ifeq ($(NM_SYSTEM), Linux)
process_login_ldlibs = $(nm_lib_opt)crypt
endif

process_login: $(process_login_proc_binout)
process_login_test: process_login_proc_test

process_login_proc_test: $(process_login_proc_binout)
	# $< ${process_login_name}
	echo "#skip ..."

$(process_login_proc_binout): $(process_root)/login/proc1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(process_login_ldlibs)



# main
process_main_binout := $(bin_path)/$(process_prefix)_main$(bin_ext)
_RETURN_INT_ ?= 1
_WITH_RETURN_ ?= 1
_WITH_EXIT_ ?= 0

process_main: $(process_main_binout)
process_main_test: process_main
	-$(process_main_binout); echo $$?

$(process_main_binout): $(process_root)/main/m99.c
	$(CC) $(CFLAGS) $(INC)                        \
    -D_RETURN_INT_=$(_RETURN_INT_)              \
    -D_WITH_RETURN_=$(_WITH_RETURN_)            \
    -D_WITH_EXIT_=$(_WITH_EXIT_)                \
    $^ $(bin_out)$@



# mmap
process_mmap_prot_binout := $(bin_path)/$(process_prefix)_mmap_prot$(bin_ext)

process_mmap: $(process_mmap_prot_binout)
process_mmap_test: process_mmap_prot_test

process_mmap_prot_test: $(process_mmap_prot_binout)
	$<

$(process_mmap_prot_binout): $(process_root)/mmap/p1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $< $(bin_out)$@

# nice
process_nice_raw_binout := $(bin_path)/$(process_prefix)_nice_raw$(bin_ext)
process_nice_diff_binout := $(bin_path)/$(process_prefix)_nice_diff$(bin_ext)

process_nice: $(process_nice_raw_binout)
process_nice_test: process_nice_raw_test        \
                   process_nice_diff_test

process_nice_raw_test: $(process_nice_raw_binout)
	echo "# skip process_nice_raw_test ..."
	# sudo $<

process_nice_diff_test: $(process_nice_diff_binout)
	echo "# skip process_nice_diff_test ..."
	# sudo $< 0
	# sudo $< 20
	# sudo $< -20

$(process_nice_raw_binout): $(process_root)/nice/n1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_nice_diff_binout): $(process_root)/nice/n2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# orphan
process_orphan_raw_binout := $(bin_path)/$(process_prefix)_orphan_raw$(bin_ext)
process_orphan_grp_binout := $(bin_path)/$(process_prefix)_orphan_grp$(bin_ext)
process_orphan_n ?= 3

process_orphan: $(process_orphan_raw_binout)    \
                $(process_orphan_grp_binout)

process_orphan_test: process_orphan_raw_test    \
                     process_orphan_grp_test

process_orphan_raw_test: $(process_orphan_raw_binout)
	$<

process_orphan_grp_test: $(process_orphan_grp_binout)
	echo "make pid=$$PPID"
	$< $(process_orphan_n)

$(process_orphan_raw_binout): $(process_root)/orphan/o1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_orphan_grp_binout): $(process_root)/orphan/g1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# rlimit
process_rlimit_raw_binout := $(bin_path)/$(process_prefix)_rlimit_raw$(bin_ext)
process_rlimit_c := $(tmp_path)/$(process_prefix)_rl.c
process_rlimit_awk := $(process_root)/rlimit/rl.awk
process_rlimit_awk_in := $(process_root)/rlimit/rl.awk.in
process_rlimit_nofile_binout := $(bin_path)/$(process_prefix)_rlimit_nofile$(bin_ext)
process_rlimit_pr_binout := $(bin_path)/$(process_prefix)_rlimit_pr$(bin_ext)
process_rlimit_pr1_binout := $(bin_path)/$(process_prefix)_rlimit_pr1$(bin_ext)
process_rlimit_stack_binout := $(bin_path)/$(process_prefix)_rlimit_stack$(bin_ext)

process_rlimit: $(process_rlimit_raw_binout)    \
                $(process_rlimit_nofile_binout) \
                $(process_rlimit_pr_binout)     \
                $(process_rlimit_pr1_binout)    \
                $(process_rlimit_stack_binout)
process_rlimit_test: process_rlimit_raw_test    \
                     process_rlimit_nofile_test \
                     process_rlimit_pr_test     \
                     process_rlimit_pr1_test    \
                     process_rlimit_stack_test

process_rlimit_raw_test: $(process_rlimit_raw_binout)
	# ulimit -a
	$(process_rlimit_raw_binout)

process_rlimit_nofile_test: $(process_rlimit_nofile_binout)
	$(process_rlimit_nofile_binout) $(process_root)/rlimit/nofile1.c

ifeq ($(has_prlimit),yes)
process_rlimit_pr_test: $(process_rlimit_pr_binout)
	$(process_rlimit_pr_binout) $$PPID
else
process_rlimit_pr_test:
	echo "# skipped, 'prlimit' no found"
endif

process_rlimit_stack_test: $(process_rlimit_stack_binout)
	$(process_rlimit_stack_binout)

$(process_rlimit_c): $(process_rlimit_awk)      \
                     $(process_rlimit_awk_in)
	awk -f $^ > $@

process_rlimit_pr1_test: $(process_rlimit_pr1_binout)
	$(process_rlimit_pr1_binout) $$PPID

$(process_rlimit_raw_binout): $(process_rlimit_c)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_rlimit_nofile_binout): $(process_root)/rlimit/nofile1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_rlimit_pr_binout): $(process_root)/rlimit/p1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_rlimit_pr1_binout): $(process_root)/rlimit/p2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_rlimit_stack_binout): $(process_root)/rlimit/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# time
process_time1_binout := $(bin_path)/$(process_prefix)_time1$(bin_ext)
process_time2_binout := $(bin_path)/$(process_prefix)_time2$(bin_ext)

process_time: $(process_time1_binout)           \
              $(process_time2_binout)
process_time_test: process_time1_test           \
                   process_time2_test

process_time1_test: $(process_time1_binout)
	$<

process_time2_test: $(process_time2_binout)
	$< "sleep 1"
	$< "date" "grep NM_CLK_TCK -r $(process_root) > /dev/null" "man sh >/dev/null"

$(process_time1_binout): $(process_root)/time/t1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_time2_binout): $(process_root)/time/t2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# tty
process_tty_pass_binout := $(bin_path)/$(process_prefix)_tty_pass$(bin_ext)

process_tty: $(process_tty_pass_binout)
process_tty_test: process_tty_pass_test

process_tty_pass_test: $(process_tty_pass_binout)
	$<
	$< 3
	$< 3 <$(process_root)/Makefile

$(process_tty_pass_binout): $(process_root)/tty/p1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# wait
process_wait_4_binout := $(bin_path)/$(process_prefix)_wait_4$(bin_ext)
process_wait_sig_binout := $(bin_path)/$(process_prefix)_wait_sig$(bin_ext)

process_wait: $(process_wait_4_binout)          \
              $(process_wait_sig_binout)

process_wait_test: process_wait_4_test          \
                   process_wait_sig_test

process_wait_4_test: $(process_wait_4_binout)
	$<

process_wait_sig_test: $(process_wait_sig_binout)
	$<

$(process_wait_4_binout): $(process_root)/wait/w4.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_wait_sig_binout): $(process_root)/wait/w0.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# zombie
process_zombie_binout := $(bin_path)/$(process_prefix)_zombie$(bin_ext)

process_zombie: $(process_zombie_binout)
process_zombie_test: $(process_zombie_binout)
	$<

$(process_zombie_binout): $(process_root)/zombie/z1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
