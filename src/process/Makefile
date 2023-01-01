#
# ./configure --has-process
#

ifeq ($(NM_SYSTEM), WinNT)
process:
	@echo "#skip ..."
process_test: process
	@echo "#skip ..."
else

process: process_main                           \
         process_argv                           \
         process_env                            \
         process_exec                           \
         process_id                             \
         process_io                             \
         process_layout                         \
         process_rlimit                         \
         process_time                           \
         process_zombie

process_test: process_main_test                 \
              process_argv_test                 \
              process_env_test                  \
              process_exec_test                 \
              process_id_test                   \
              process_io_test                   \
              process_layout_test               \
              process_rlimit_test               \
              process_time_test                 \
              process_zombie_test

endif

# process env
process_prefix := process
INC += $(nm_inc_opt)$(process_root) $(nm_inc_opt)$(root)/posix

ifeq ($(NM_SYSTEM), Linux)
	cflags_static_opt := -static
endif

# main
process_main_binout := $(bin_path)/$(process_prefix)_main$(bin_ext)
_RETURN_INT_ ?= 1
_WITH_RETURN_ ?= 1
_WITH_EXIT_ ?= 0

process_main: $(process_main_binout)
process_main_test: process_main
	-$(process_main_binout)

$(process_main_binout): $(process_root)/main/m99.c
	$(CC) $(CFLAGS) $(INC)                        \
    -D_RETURN_INT_=$(_RETURN_INT_)              \
    -D_WITH_RETURN_=$(_WITH_RETURN_)            \
    -D_WITH_EXIT_=$(_WITH_EXIT_)                \
    $^ $(bin_out)$@


# argv
process_argv_binout := $(bin_path)/$(process_prefix)_argv$(bin_ext)

process_argv: $(process_argv_binout)
process_argv_test: process_argv
	$(process_argv_binout)
	$(process_argv_binout) a bb ccc

$(process_argv_binout): $(process_root)/argv/clargv.c
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
process_exec_echo_binout := $(bin_path)/$(process_prefix)_exec_echo$(bin_ext)
process_exec_vary_binout := $(bin_path)/$(process_prefix)_exec_vary$(bin_ext)
process_exec_vary_cppout := $(tmp_path)/$(process_prefix)_exec_vary$(cpp_ext)
process_exec_child_binout := $(bin_path)/$(process_prefix)_exec_child$(bin_ext)

process_exec: $(process_exec_echo_binout)       \
              $(process_exec_vary_binout)       \
              $(process_exec_child_binout)
process_exec_test: process_exec_echo_test       \
                   process_exec_vary_test       \
                   process_exec_child_test

process_exec_echo_test: $(process_exec_echo_binout)
	$< a b c

process_exec_vary_test: $(process_exec_echo_binout) \
                        $(process_exec_vary_binout)
	$(process_exec_vary_binout) execl
	$(process_exec_vary_binout) execle
	$(process_exec_vary_binout) execv
	PATH="$(PATH):$(CURDIR)/$(bin_path)" $(process_exec_vary_binout) execlp
	PATH="$(PATH):$(CURDIR)/$(bin_path)" $(process_exec_vary_binout) execvp

process_exec_child_test: $(process_exec_echo_binout)  \
                         $(process_exec_child_binout)
	PATH="$(PATH):$(CURDIR)/$(bin_path)" $(process_exec_child_binout)

$(process_exec_echo_binout): $(process_root)/exec/echoa.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_exec_vary_binout): $(process_exec_vary_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(process_exec_vary_cppout): $(process_root)/exec/vary.c
	$(CC) $(CPPFLAGS) $(INC)                              \
    -D_PATH_NAME_=\"$(CURDIR)/$(process_exec_echo_binout)\" \
    -D_FILE_NAME_=\"$(process_prefix)_exec_echo$(bin_ext)\" \
    $(nm_stage_pre) $^ $(cpp_out)$@

$(process_exec_child_binout): $(process_root)/exec/child.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                        \
    -D_PATH_NAME_=\"$(CURDIR)/$(process_exec_echo_binout)\" \
    -D_FILE_NAME_=\"$(process_prefix)_exec_echo$(bin_ext)\" \
    -D_WAIT_=0                                              \
    $^ $(bin_out)$@

# id
process_id_binout := $(bin_path)/$(process_prefix)_id$(bin_ext)
process_id_asmout := $(tmp_path)/$(process_prefix)_id$(asm_ext)

process_id: $(process_id_binout)
process_id_test: $(process_id_binout)
	$<
	# sudo chown root $<
	# sudo chmod u+s $<
	# $<

$(process_id_binout): $(process_id_asmout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(process_id_asmout): $(process_root)/id/id1.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_asm) $^ $(asm_out)$@



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
	$< > $(tmp_path)/$(process_prefix)_io_buf.txt
	cat $(tmp_path)/$(process_prefix)_io_buf.txt

process_io_async_test: $(process_io_async_binout)
	$<

process_io_sync_test: $(process_io_sync_binout)
	$<

$(process_io_buf_binout): $(process_root)/io/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_io_async_binout): $(process_root)/io/c.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_io_sync_binout): $(process_root)/io/c.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_SYNC_=1 $^ $(bin_out)$@

# layout
process_layout_raw_binout := $(bin_path)/$(process_prefix)_layout_raw$(bin_ext)
process_layout_raw_asmout := $(tmp_path)/$(process_prefix)_layout_raw$(asm_ext)
process_layout_brk_binout := $(bin_path)/$(process_prefix)_layout_brk$(bin_ext)

ifeq ($(NM_SYSTEM), Darwin)
process_layout: $(process_layout_raw_binout)
process_layout_test: process_layout_raw_test
else
process_layout: $(process_layout_raw_binout)    \
                $(process_layout_brk_binout)
process_layout_test: process_layout_raw_test    \
                     process_layout_brk_test
endif

process_layout_raw_test: $(process_layout_raw_binout)
	$<
	size $<
	nm $<

process_layout_brk_test: $(process_layout_brk_binout)
	$<
	size $<

$(process_layout_raw_binout): $(process_layout_raw_asmout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(process_layout_raw_asmout): $(process_root)/layout/m.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_asm) $^ $(asm_out)$@

$(process_layout_brk_binout): $(process_root)/layout/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# rlimit
process_rlimit_binout := $(bin_path)/$(process_prefix)_rlimit$(bin_ext)
process_rlimit_source := $(tmp_path)/$(process_prefix)_rl.c
process_rlimit_awk := $(process_root)/rlimit/rl.awk
process_rlimit_awk_in := $(process_root)/rlimit/rl.awk.in

process_rlimit: $(process_rlimit_binout)
process_rlimit_test: process_rlimit
	$(process_rlimit_binout)

# $(process_rlimit_source)
# $(process_root)/rlimit/def.c
$(process_rlimit_binout): $(process_rlimit_source)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_rlimit_source): $(process_rlimit_awk)     \
                          $(process_rlimit_awk_in)
	awk -f $^ > $@


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
	$< sleep 1
	$< grep NM_CLK_TCK -r $(process_root) > /dev/null

$(process_time1_binout): $(process_root)/time/t1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_time2_binout): $(process_root)/time/t2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# zombie
process_zombie_binout := $(bin_path)/$(process_prefix)_zombie$(bin_ext)

process_zombie: $(process_zombie_binout)
process_zombie_test: process_zombie
	$(process_zombie_binout)

$(process_zombie_binout): $(process_root)/zombie/z.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
