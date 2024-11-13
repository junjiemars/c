# -*- mode:makefile-gmake -*-
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
        signal_bone                             \
        signal_child                            \
        signal_info                             \
        signal_io                               \
        signal_job                              \
        signal_kill                             \
        signal_pause                            \
        signal_queue                            \
        signal_safe                             \
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
             signal_bone_test                   \
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

endif



# env
signal_prefix := signal
posix_root := $(root)/posix

INC += $(nm_inc_opt)$(signal_root) $(nm_inc_opt)$(posix_root)



# abort
signal_abort_d_binout := $(bin_path)/$(signal_prefix)_abort_d$(bin_ext)
signal_abort_a1_binout := $(bin_path)/$(signal_prefix)_abort_a1$(bin_ext)

signal_abort: signal_abort_d \
              signal_abort_a1
signal_abort_test: signal_abort_d_test \
                   signal_abort_a1_test

signal_abort_d: $(signal_abort_d_binout)
signal_abort_a1: $(signal_abort_a1_binout)

signal_abort_d_test: $(signal_abort_d_binout)
	-$<
	-$< 1
	-$< -1
	-$< -1 0
signal_abort_a1_test: $(signal_abort_a1_binout)
	-$<
	-$< 1
	-$< -1
	-$< -1 0

$(signal_abort_d_binout): $(signal_root)/abort/d1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_abort_a1_binout): $(signal_root)/abort/d1.c \
                           $(signal_root)/abort/abrt1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# alarm
signal_alarm_d_binout := $(bin_path)/$(signal_prefix)_alarm_d$(bin_ext)
signal_alarm_a1_binout := $(bin_path)/$(signal_prefix)_alarm_a1$(bin_ext)
signal_alarm_s1_binout := $(bin_path)/$(signal_prefix)_alarm_s1$(bin_ext)
signal_alarm_cflags ?= -D_ALRM_N_=4

signal_alarm: $(signal_alarm_d_binout) \
              $(signal_alarm_a1_binout) \
              $(signal_alarm_s1_binout)
signal_alarm_test: signal_alarm_d_test \
                   signal_alarm_a1_test \
                   signal_alarm_s1_test

signal_alarm_d_test: $(signal_alarm_d_binout)
	$<
signal_alarm_a1_test: $(signal_alarm_a1_binout)
	$<
signal_alarm_s1_test: $(signal_alarm_s1_binout)
	$<

$(signal_alarm_d_binout): $(signal_root)/alarm/d1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ \
    $(signal_alarm_cflags)

$(signal_alarm_a1_binout): $(signal_root)/alarm/d1.c \
                           $(signal_root)/alarm/alrm1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(bin_out)$@ $(signal_alarm_cflags) $^

$(signal_alarm_s1_binout): $(signal_root)/alarm/d1.c \
                           $(signal_root)/alarm/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(bin_out)$@ $(signal_alarm_cflags) $^



# bone
signal_bone_binout := $(bin_path)/$(signal_prefix)_bone$(bin_ext)

signal_bone: $(signal_bone_binout)
signal_bone_test: $(signal_bone_binout)
	$(signal_bone_binout)

$(signal_bone_binout): $(signal_root)/bone/b1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



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
	$< 1 0x20	# SA_NOCLDWAIT

$(signal_child_proc_binout): $(signal_root)/child/p1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_child_chld_binout): $(signal_root)/child/c1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# info
signal_info_inc := $(nm_inc_opt)$(signal_root)/info
signal_info_lst_binout := $(bin_path)/$(signal_prefix)_info_lst$(bin_ext)
signal_info_dfl_binout := $(bin_path)/$(signal_prefix)_info_dfl$(bin_ext)
signal_info_sig2str_h := $(inc_path)/sig2str.h
signal_info_sig2str_c := $(tmp_path)/sig2str.c
signal_info_lst_awk_in := $(tmp_path)/$(signal_prefix)_sig2str.awk.$(NM_SYSTEM).in

signal_info: $(signal_info_lst_binout) \
             $(signal_info_dfl_binout)

signal_info_test: signal_info_lst_test \
                  signal_info_dfl_test

ifeq ($(NM_SYSTEM), Darwin)
$(signal_info_lst_awk_in):
	kill -l|tr ' ' '\n'|sed -n -e'1,31p'>$@
else
$(signal_info_lst_awk_in): $(signal_root)/info/sig2str.awk.Linux.in
	cp $< $@
endif

signal_info_lst_test: $(signal_info_lst_binout)
	$<
signal_info_dfl_test: $(signal_info_dfl_binout)
	$<

$(signal_info_lst_binout): $(signal_root)/info/lst1.c \
                           $(signal_info_sig2str_c)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(signal_info_inc) $(bin_out)$@ $^

$(signal_info_dfl_binout): $(signal_root)/info/dfl1.c \
                           $(signal_info_sig2str_c)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(signal_info_inc) $(bin_out)$@ $^

$(signal_info_sig2str_c): $(signal_root)/info/sig2str.awk \
                          $(signal_info_lst_awk_in)
	awk -f $^ > $@




# io
signal_io_xfsz_binout := $(bin_path)/$(signal_prefix)_xfsz$(bin_ext)
signal_io_xfsz_n ?= 100
signal_io_xfsz_rl ?= 4
signal_io_xfsz_file := $(tmp_path)/$(signal_prefix)_xfsz.file

signal_io: $(signal_io_xfsz_binout)
signal_io_test: signal_io_xfsz_test

signal_io_xfsz_test: $(signal_io_xfsz_binout)
	-$< 0<${signal_root}/io/x1.c 2>&1 >${signal_io_xfsz_file}

$(signal_io_xfsz_binout): $(signal_root)/io/x1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) \
    -DBUF_SIZE=$(signal_io_xfsz_n) -DFIL_SIZE=$(signal_io_xfsz_rl) \
    $^ $(bin_out)$@

# job
signal_job_tstp_binout := $(bin_path)/$(signal_prefix)_job_tstp$(bin_ext)

signal_job: signal_job_tstp
signal_job_test: signal_job_tstp_test

signal_job_tstp: $(signal_job_tstp_binout)

signal_job_tstp_test: $(signal_job_tstp_binout)
	$< | head -n1 | xargs kill -TSTP

$(signal_job_tstp_binout): $(signal_root)/job/j1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



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

signal_pause: signal_pause_d \
              signal_pause_p1
signal_pause_test: signal_pause_d \
                   signal_pause_p1

signal_pause_d: $(signal_pause_d_binout)
signal_pause_p1: $(signal_pause_p1_binout)

signal_pause_d_test: $(signal_pause_d_binout)
	-$< |head -n1|xargs kill -KILL

signal_pause_p1_test: $(signal_pause_p1_binout)
	-$< |head -n1|xargs kill -KILL

$(signal_pause_d_binout): $(signal_root)/pause/d1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_pause_p1_binout): $(signal_root)/pause/d1.c \
                           $(signal_root)/pause/pause1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# queue
signal_queue_q1_binout := $(bin_path)/$(signal_prefix)_queue_q1$(bin_ext)
signal_queue_q2_binout := $(bin_path)/$(signal_prefix)_queue_q2$(bin_ext)
signal_queue_n ?= 1
signal_queue_deps = $(signal_queue_q1_binout)
signal_queue_test_deps = signal_queue_q1_test

signal_queue_deps += $(signal_queue_q2_binout)
signal_queue_test_deps += signal_queue_q2_test

ifeq ($(has_sigqueue),yes)
signal_queue: $(signal_queue_deps)
signal_queue_test: $(signal_queue_test_deps)
else
signal_queue:
	@echo "# skip $@ ..."
signal_queue_test: signal_queue
	@echo "# skip $@ ..."
endif

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

signal_safe: $(signal_safe_stdio_binout) \
             $(signal_safe_nre_binout) \
             $(signal_safe_re_binout)

signal_safe_test: signal_safe_stdio_test \
                  signal_safe_nre_test \
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
signal_sleep_s4_binout := $(bin_path)/$(signal_prefix)_sleep_s4$(bin_ext)
signal_sleep_n ?= 3
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

ifeq ($(has_clock_nanosleep), yes)
signal_sleep_deps += $(signal_sleep_s4_binout)
signal_sleep_test_deps += signal_sleep_s4_test
endif

signal_sleep: $(signal_sleep_d_binout)
signal_sleep_test: $(signal_sleep_test_deps)

signal_sleep_d_test: $(signal_sleep_d_binout)
	$< $(signal_sleep_n)
signal_sleep_s1_test: $(signal_sleep_s1_binout)
	$< $(signal_sleep_n)
signal_sleep_s2_test: $(signal_sleep_s2_binout)
	$< $(signal_sleep_n)
signal_sleep_s3_test: $(signal_sleep_s3_binout)
	$< $(signal_sleep_n)
signal_sleep_s4_test: $(signal_sleep_s4_binout)
	$< $(signal_sleep_n)

$(signal_sleep_d_binout): $(signal_root)/sleep/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_sleep_s1_binout): $(signal_root)/sleep/d.c \
                           $(signal_root)/sleep/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_s2_binout): $(signal_root)/sleep/d.c \
                           $(signal_root)/sleep/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_s3_binout): $(signal_root)/sleep/d.c \
                           $(signal_root)/sleep/s3.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_s4_binout): $(signal_root)/sleep/d.c \
                           $(signal_root)/sleep/s4.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# suspend
signal_suspend_raw_binout := $(bin_path)/$(signal_prefix)_suspend_raw$(bin_ext)
signal_suspend_wait_binout := $(bin_path)/$(signal_prefix)_suspend_wait$(bin_ext)
signal_suspend_flag_binout := $(bin_path)/$(signal_prefix)_suspend_flag$(bin_ext)
signal_suspend_stage_binout := $(bin_path)/$(signal_prefix)_suspend_stage$(bin_ext)
signal_suspend_n ?= 1
signal_suspend_file := $(tmp_path)/$(signal_prefix)_suspend_file

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
	$< 1 | tee $(signal_suspend_file)|head -n1|xargs kill -INT \
    && cat $(signal_suspend_file)
signal_suspend_wait_test: $(signal_suspend_wait_binout)
	-$< $(signal_suspend_n)
signal_suspend_flag_test: $(signal_suspend_flag_binout)
	$< 1 | tee $(signal_suspend_file) | head -n1 | xargs kill -QUIT \
    && cat $(signal_suspend_file)

signal_suspend_stage_test: $(signal_suspend_stage_binout)
	-$< $(signal_suspend_n)

$(signal_suspend_raw_binout): $(signal_root)/suspend/r.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_suspend_wait_binout): $(signal_root)/suspend/w.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_suspend_flag_binout): $(signal_root)/suspend/f.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_suspend_stage_binout): $(signal_root)/suspend/s.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# sync
signal_sync_bone_binout := $(bin_path)/$(signal_prefix)_sync_bone$(bin_ext)
signal_sync_file_binout := $(bin_path)/$(signal_prefix)_sync_file$(bin_ext)
signal_sync_file := $(tmp_path)/$(signal_prefix)_sync.file

signal_sync: $(signal_sync_bone_binout) \
             $(signal_sync_file_binout)
signal_sync_test: signal_sync_bone_test \
                  signal_sync_file_test

signal_sync_bone_test: $(signal_sync_bone_binout)
	$<
signal_sync_file_test: $(signal_sync_file_binout)
	$< $(signal_sync_file)

$(signal_sync_bone_binout): $(signal_root)/sync/d1.c \
                            $(signal_root)/sync/psync1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(signal_sync_file_binout): $(signal_root)/sync/d2.c \
                            $(signal_root)/sync/psync1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# system
signal_system_d_binout := $(bin_path)/$(signal_prefix)_system_d$(bin_ext)
signal_system_s1_binout := $(bin_path)/$(signal_prefix)_system_s1$(bin_ext)
signal_system_ed_in := "a\nNore\n.\n1p\nQ\n"

signal_system: $(signal_system_d_binout) \
               $(signal_system_s1_binout)
signal_system_test: signal_system_d_test \
                    signal_system_s1_test

signal_system_d_test: $(signal_system_d_binout)
	$< || test $$? -eq 1
	$< "date"
	printf $(signal_system_ed_in) | $< "/bin/ed"

signal_system_s1_test: $(signal_system_s1_binout)
	-$< || test $$? -eq 1
	$< "date"
	printf $(signal_system_ed_in) | $< "/bin/ed"

$(signal_system_d_binout): $(signal_root)/system/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_system_s1_binout): $(signal_root)/system/d.c \
                            $(signal_root)/system/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# timeout
signal_timeout_t1_binout := $(bin_path)/$(signal_prefix)_timeout_t1$(bin_ext)

signal_timeout: $(signal_timeout_t1_binout)
signal_timeout_test: signal_timeout_t1_test

signal_timeout_t1_test: $(signal_timeout_t1_binout)
	-echo "abc" | $<
	-echo "abc" | $< 2
	-$< 2

$(signal_timeout_t1_binout): $(signal_root)/timeout/d.c \
                             $(signal_root)/timeout/t1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# timer
signal_timer_d_binout := $(bin_path)/$(signal_prefix)_timer_d$(bin_ext)

signal_timer: $(signal_timer_d_binout)
signal_timer_test: signal_timer_d_test

signal_timer_d_test: $(signal_timer_d_binout)
	$<

$(signal_timer_d_binout): $(signal_root)/timer/d1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# wait
signal_wait1_binout := $(bin_path)/$(signal_prefix)_wait1$(bin_ext)

signal_wait: $(signal_wait1_binout)
signal_wait_test: signal_wait
	$(signal_wait1_binout)

$(signal_wait1_binout): $(signal_root)/wait/w1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
