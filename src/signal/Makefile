# -*- major-mode:makefile-gmake-mode -*-
#
# ./configure --has-signal
#
#

ifeq ($(CC_NAME), msvc)
signal:
	@echo "#skip ..."
signal_test:
	@echo "#skip ..."
else


signal:                                         \
        signal_abort                            \
        signal_alarm                            \
        signal_child                            \
        signal_info                             \
        signal_io                               \
        signal_job                              \
        signal_kill                             \
        signal_pause                            \
        signal_queue                            \
        singal_safe                             \
        signal_sleep                            \
        signal_suspend                          \
        signal_sync                             \
        signal_system                           \
        signal_timeout                          \
        signal_timer                            \
        signal_wait

signal_test:                                    \
             signal_abort_test                  \
             signal_alarm_test                  \
             signal_child_test                  \
             signal_info_test                   \
             signal_io_test                     \
             signal_job_test                    \
             signal_kill_test                   \
             signal_pause_test                  \
             signal_queue_test                  \
             signal_safe_test                   \
             signal_sleep_test                  \
             signal_suspend_test                \
             signal_sync_test                   \
             signal_system_test                 \
             signal_timeout_test                \
             signal_timer_test                  \
             signal_wait_test

endif														# msvc



# env
signal_prefix := signal
posix_root := $(root)/posix

INC += $(nm_inc_opt)$(signal_root) $(nm_inc_opt)$(posix_root)



# abort
signal_abort_d_binout := $(bin_path)/$(signal_prefix)_abort_d$(bin_ext)
signal_abort_a1_binout := $(bin_path)/$(signal_prefix)_abort_a1$(bin_ext)
signal_abort_cflags := -D_IGN_SIG_ABRT_=-1 -D_EXIT_SIG_HANDLER_=1

signal_abort: $(signal_abort_d_binout) \
              $(signal_abort_a1_binout)
signal_abort_test: signal_abort_d_test \
                   signal_abort_a1_test

signal_abort_d_test: $(signal_abort_d_binout)
	-$<

signal_abort_a1_test: $(signal_abort_a1_binout)
	-$<

$(signal_abort_d_binout): $(signal_root)/abort/d1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(signal_abort_cflags) \
    $^ $(bin_out)$@

$(signal_abort_a1_binout): $(signal_root)/abort/d1.c \
                           $(signal_root)/abort/abrt1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(signal_abort_cflags) \
    $^ $(bin_out)$@



# alarm
signal_alarm_d_binout := $(bin_path)/$(signal_prefix)_alarm_d$(bin_ext)
signal_alarm_a1_binout := $(bin_path)/$(signal_prefix)_alarm_a1$(bin_ext)
signal_alarm_cflags ?= -D_ALRM_N_=4

signal_alarm: $(signal_alarm_d_binout) \
              $(signal_alarm_a1_binout)

signal_alarm_test: signal_alarm_d_test \
                   signal_alarm_a1_test

signal_alarm_d_test: $(signal_alarm_d_binout)
	$<

signal_alarm_a1_test: $(signal_alarm_a1_binout)
	$<

$(signal_alarm_d_binout): $(signal_root)/alarm/d1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ \
    $(signal_alarm_cflags)

$(signal_alarm_a1_binout): $(signal_root)/alarm/d1.c \
                           $(signal_root)/alarm/alrm1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ \
    $(signal_alarm_cflags)



# child
signal_child_proc_binout := $(bin_path)/$(signal_prefix)_child_proc$(bin_ext)
signal_child_chld_binout := $(bin_path)/$(signal_prefix)_child_chld$(bin_ext)

signal_child: $(signal_child_proc_binout) \
              $(signal_child_chld_binout)
signal_child_test: signal_child_proc_test \
                   signal_child_chld_test


signal_child_proc_test: $(signal_child_proc_binout)
	$<

signal_child_chld_test: $(signal_child_chld_binout)
	$< 1

$(signal_child_proc_binout): $(signal_root)/child/p1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_child_chld_binout): $(signal_root)/child/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# info
signal_info_lst_binout := $(bin_path)/$(signal_prefix)_lst$(bin_ext)
signal_info_dfl_binout := $(bin_path)/$(signal_prefix)_dfl$(bin_ext)
signal_info_sig2str_h := $(inc_path)/sig2str.h
signal_info_sig2str_c := $(tmp_path)/sig2str.c
signal_info_lst_awk_in := $(signal_root)/info/sig2str.awk.$(NM_SYSTEM).in

signal_info: $(signal_info_lst_binout) \
             $(signal_info_dfl_binout)

signal_info_test: signal_info_lst_test \
                  signal_info_dfl_test

signal_info_lst_test: $(signal_info_lst_binout)
	$<

signal_info_dfl_test: $(signal_info_dfl_binout)
	$<

$(signal_info_lst_binout): $(signal_root)/info/lst1.c \
                           $(signal_info_sig2str_c)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_inc_opt)$(signal_root)/info $^ $(bin_out)$@

$(signal_info_dfl_binout): $(signal_root)/info/dfl1.c \
                           $(signal_info_sig2str_c)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_inc_opt)$(signal_root)/info $^ $(bin_out)$@

$(signal_info_sig2str_c): $(signal_root)/info/sig2str.awk \
                          $(signal_info_lst_awk_in)
	awk -f $^ > $@



# io
signal_io_xfsz_binout := $(bin_path)/$(signal_prefix)_xfsz$(bin_ext)
signal_io_xfsz_n ?= 100
signal_io_xfsz_rl ?= 2000
signal_io_file := $(tmp_path)/$(signal_prefix)_xfsz.file

signal_io: $(signal_io_xfsz_binout)
signal_io_test: signal_io_xfsz_test

signal_io_xfsz_test: $(signal_io_xfsz_binout)
	-$< 0<${signal_root}/io/x1.c 1>${signal_io_file}

$(signal_io_xfsz_binout): $(signal_root)/io/x1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                                \
    -DBUF_SIZE=$(signal_io_xfsz_n) -DRL_FSIZE=$(signal_io_xfsz_rl)  \
    $^ $(bin_out)$@

# job
signal_job_tstp_binout := $(bin_path)/$(signal_prefix)_job_tstp$(bin_ext)

signal_job: signal_job_tstp
signal_job_test: signal_job_tstp_test

signal_job_tstp: $(signal_job_tstp_binout)

signal_job_tstp_test: $(signal_job_tstp_binout)
	# $<
	@echo "#skip ... (C-z emit SIGTSTP)"

$(signal_job_tstp_binout): $(signal_root)/job/j1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# kill
signal_kill_binout := $(bin_path)/$(signal_prefix)_kill$(bin_ext)

signal_kill: $(signal_kill_binout)
signal_kill_test: signal_kill
	$(signal_kill_binout)

$(signal_kill_binout): $(signal_root)/kill/k1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# pause
signal_pause_d_binout := $(bin_path)/$(signal_prefix)_pause_d$(bin_ext)
signal_pause_p1_binout := $(bin_path)/$(signal_prefix)_pause_p1$(bin_ext)

signal_pause: $(signal_pause_d_binout) \
              $(signal_pause_p1_binout)
signal_pause_test: signal_pause_d_test \
                   signal_pause_p1_test

signal_pause_d_test: $(signal_pause_d_binout)
	-$< |head -n1|xargs kill -TERM

signal_pause_p1_test: $(signal_pause_p1_binout)
	-$< |head -n1|xargs kill -TERM

$(signal_pause_d_binout): $(signal_root)/pause/d1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_pause_p1_binout): $(signal_root)/pause/d1.c \
                           $(signal_root)/pause/pause1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# queue
signal_queue_q1_binout := $(bin_path)/$(signal_prefix)_queue_q1$(bin_ext)
signal_queue_q2_binout := $(bin_path)/$(signal_prefix)_queue_q2$(bin_ext)
signal_queue_n ?= 1
signal_queue_deps = $(signal_queue_q1_binout)
signal_queue_test_deps = signal_queue_q1_test

ifeq ($(has_sigqueue), yes)
signal_queue_deps += $(signal_queue_q2_binout)
signal_queue_test_deps += signal_queue_q2_test
endif

signal_queue: $(signal_queue_deps)
signal_queue_test: $(signal_queue_test_deps)

signal_queue_q1_test: $(signal_queue_q1_binout)
	$< ${signal_queue_n} | cat -
	# echo "#skip ... (C-\ emit SIGQUIT)"

signal_queue_q2_test: $(signal_queue_q2_binout)
	$< ${signal_queue_n} | cat -
	# echo "#skip ... (C-\ emit SIGQUIT)"

$(signal_queue_q1_binout): $(signal_root)/queue/q1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_queue_q2_binout): $(signal_root)/queue/q2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# safe
signal_safe_stdio_binout := $(bin_path)/$(signal_prefix)_safe_stdio$(bin_ext)
signal_safe_nre_binout := $(bin_path)/$(signal_prefix)_safe_nre$(bin_ext)
signal_safe_re_binout := $(bin_path)/$(signal_prefix)_safe_re$(bin_ext)


signal_safe: $(signal_safe_stdio_binout)        \
             $(signal_safe_nre_binout)          \
             $(signal_safe_re_binout)

signal_safe_test: signal_safe_stdio_test        \
                  signal_safe_nre_test          \
                  signal_safe_re_test

signal_safe_stdio_test: $(signal_safe_stdio_binout)
	$<

signal_safe_nre_test: $(signal_safe_nre_binout)
	-$< root daemon

signal_safe_re_test: $(signal_safe_re_binout)
	$< root daemon

$(signal_safe_stdio_binout): $(signal_root)/safe/stdio1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_safe_nre_binout): $(signal_root)/safe/re1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_safe_re_binout): $(signal_root)/safe/re1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_REENTRANT_=1 $^ $(bin_out)$@



# sleep
signal_sleep_d_binout := $(bin_path)/$(signal_prefix)_sleep_d$(bin_ext)
signal_sleep_s1_binout := $(bin_path)/$(signal_prefix)_sleep_s1$(bin_ext)
signal_sleep_s2_binout := $(bin_path)/$(signal_prefix)_sleep_s2$(bin_ext)
signal_sleep_s3_binout := $(bin_path)/$(signal_prefix)_sleep_s3$(bin_ext)
signal_sleep_n ?= 1
signal_sleep_deps = $(signal_sleep_d_binout)
signal_sleep_deps += $(signal_sleep_s1_binout)
signal_sleep_deps += $(signal_sleep_s2_binout)
signal_sleep_test_deps = signal_sleep_d_test
signal_sleep_test_deps += signal_sleep_s1_test
signal_sleep_test_deps += signal_sleep_s2_test

ifeq ($(has_nanosleep), yes)
signal_sleep_deps += $(signal_sleep_s3_binout)
signal_sleep_test_deps += signal_sleep_s3_test
endif

signal_sleep: $(signal_sleep_deps)
signal_sleep_test: $(signal_sleep_test_deps)

signal_sleep_d_test: $(signal_sleep_d_binout)
	$< $(signal_sleep_n)

signal_sleep_s1_test: $(signal_sleep_s1_binout)
	$< $(signal_sleep_n)

signal_sleep_s2_test: $(signal_sleep_s2_binout)
	$< $(signal_sleep_n)

signal_sleep_s3_test: $(signal_sleep_s3_binout)
	$< $(signal_sleep_n)

$(signal_sleep_d_binout): $(signal_root)/sleep/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_s1_binout): $(signal_root)/sleep/d.c   \
                           $(signal_root)/sleep/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_s2_binout): $(signal_root)/sleep/d.c   \
                           $(signal_root)/sleep/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_s3_binout): $(signal_root)/sleep/d.c   \
                           $(signal_root)/sleep/s3.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# suspend
signal_suspend_raw_binout := $(bin_path)/$(signal_prefix)_suspend_raw$(bin_ext)
signal_suspend_wait_binout := $(bin_path)/$(signal_prefix)_suspend_wait$(bin_ext)
signal_suspend_flag_binout := $(bin_path)/$(signal_prefix)_suspend_flag$(bin_ext)
signal_suspend_stage_binout := $(bin_path)/$(signal_prefix)_suspend_stage$(bin_ext)
signal_suspend_n ?= 1

signal_suspend: $(signal_suspend_raw_binout) \
                $(signal_suspend_wait_binout) \
                $(signal_suspend_flag_binout) \
                $(signal_suspend_stage_binout)
signal_suspend_test: signal_suspend_raw_test \
                     signal_suspend_wait_test \
                     signal_suspend_flag_test \
                     signal_suspend_stage_test

signal_suspend_stage: $(signal_suspend_stage_binout)
	$< $(signal_suspend_n)

signal_suspend_raw_test: $(signal_suspend_raw_binout)
	$< $(signal_suspend_n)

signal_suspend_wait_test: $(signal_suspend_wait_binout)
	-$< $(signal_suspend_n)

signal_suspend_flag_test: $(signal_suspend_flag_binout)
	# $<
	@echo "#skip ..."

signal_suspend_stage_test: $(signal_suspend_stage_binout)
	-$< $(signal_suspend_n)

$(signal_suspend_raw_binout): $(signal_root)/suspend/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_suspend_wait_binout): $(signal_root)/suspend/w.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_suspend_flag_binout): $(signal_root)/suspend/f.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_suspend_stage_binout): $(signal_root)/suspend/s.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# sync
signal_sync_child_binout := $(bin_path)/$(signal_prefix)_sync_child$(bin_ext)

signal_sync: $(signal_sync_child_binout)
signal_sync_test: signal_sync_child_test

signal_sync_child_test: $(signal_sync_child_binout)
	$<

$(signal_sync_child_binout): $(signal_root)/sync/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# system
signal_system_d_binout := $(bin_path)/$(signal_prefix)_system_d$(bin_ext)
signal_system_s1_binout := $(bin_path)/$(signal_prefix)_system_s1$(bin_ext)

signal_system: $(signal_system_d_binout) \
               $(signal_system_s1_binout)
signal_system_test: signal_system_d_test \
                    signal_system_s1_test

signal_system_d_test: $(signal_system_d_binout)
	$< || test $$? -eq 1
	$< "date"
	# $< "/bin/ed"

signal_system_s1_test: $(signal_system_s1_binout)
	-$< || test $$? -eq 1
	$< "date"
	# $< "/bin/ed"

$(signal_system_d_binout): $(signal_root)/system/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_system_s1_binout): $(signal_root)/system/d.c \
                            $(signal_root)/system/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# timeout
signal_timeout_t1_binout := $(bin_path)/$(signal_prefix)_timeout_t1$(bin_ext)
signal_timeout_n ?= 2

signal_timeout: $(signal_timeout_t1_binout)
signal_timeout_test: signal_timeout_t1_test

signal_timeout_t1_test: $(signal_timeout_t1_binout)
	-echo "abc" | $< ${signal_timeout_n}
	-$< $(signal_timeout_n)

$(signal_timeout_t1_binout): $(signal_root)/timeout/d.c   \
                             $(signal_root)/timeout/t1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# timer
signal_timer_libes_binout := $(bin_path)/$(signal_prefix)_timer_libes$(bin_ext)

signal_timer: $(signal_timer_libes_binout)
signal_timer_test: signal_timer_libes_test

signal_timer_libes_test: $(signal_timer_libes_binout)
	$<

$(signal_timer_libes_binout): $(signal_root)/timer/t1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# wait
signal_wait1_binout := $(bin_path)/$(signal_prefix)_wait1$(bin_ext)

signal_wait: $(signal_wait1_binout)
signal_wait_test: signal_wait
	$(signal_wait1_binout)

$(signal_wait1_binout): $(signal_root)/wait/w1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@





# eof
