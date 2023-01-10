#
# ./configure --has-signal
#


ifeq ($(CC_NAME), msvc)
signal:
	@echo "#skip ..."
signal_test:
	@echo "#skip ..."
else


signal: signal_alarm                            \
        signal_kill                             \
        signal_reentrant                        \
        signal_set                              \
        signal_sleep                            \
        signal_timeout                          \
        signal_wait                             \
        signal_pause                            \
        sigal_child                             \
        signal_info                             \
        signal_suspend                          \
        signal_sync                             \
        signal_abort                            \
        signal_system                           \
        signal_job

signal_test: signal_alarm_test                  \
             signal_kill_test                   \
             signal_reentrant_test              \
             signal_set_test                    \
             signal_sleep_test                  \
             signal_timeout_test                \
             signal_wait_test                   \
             signal_pause_test                  \
             signal_child_test                  \
             signal_info_test                   \
             signal_suspend_test                \
             signal_sync_test                   \
             signal_abort_test                  \
             signal_system_test                 \
             signal_job_test

endif														# msvc


# env
signal_prefix := signal
INC += $(nm_inc_opt)$(signal_root) $(nm_inc_opt)$(root)/posix


# alarm
signal_alarm_o_binout := $(bin_path)/$(signal_prefix)_alarm_a$(bin_ext)
signal_alarm_n_binout := $(bin_path)/$(signal_prefix)_alarm_n$(bin_ext)

signal_alarm: $(signal_alarm_n_binout)          \
              $(signal_alarm_n_binout)


signal_alarm_test: signal_alarm_o_test          \
                   signal_alarm_n_test


signal_alarm_o_test: $(signal_alarm_o_binout)
	$<

signal_alarm_n_test: $(signal_alarm_n_binout)
	$<

$(signal_alarm_o_binout): $(signal_root)/alarm/o.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_alarm_n_binout): $(signal_root)/alarm/n.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# kill
signal_kill_binout := $(bin_path)/$(signal_prefix)_kill$(bin_ext)

signal_kill: $(signal_kill_binout)
signal_kill_test: signal_kill
	$(signal_kill_binout)

$(signal_kill_binout): $(signal_root)/kill/k1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# reentrant
signal_reentrant_n_binout := $(bin_path)/$(signal_prefix)_reentrant_n$(bin_ext)
signal_reentrant_n_cppout := $(tmp_path)/$(signal_prefix)_reentrant_n$(cpp_ext)
signal_reentrant_r_binout := $(bin_path)/$(signal_prefix)_reentrant_r$(bin_ext)


signal_reentrant: $(signal_reentrant_n_binout)  \
                  $(signal_reentrant_r_binout)

signal_reentrant_test: signal_reentrant_n_test  \
                       signal_reentrant_r_test

signal_reentrant_n_test: $(signal_reentrant_n_binout)
	@echo "skip..."
	# $< root daemon

signal_reentrant_r_test: $(signal_reentrant_r_binout)
	@echo "skip..."
	# $< root daemon

$(signal_reentrant_n_binout): $(signal_reentrant_n_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(signal_reentrant_n_cppout): $(signal_root)/reentrant/r.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

$(signal_reentrant_r_binout): $(signal_root)/reentrant/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_REENTRANT_=1 $^ $(bin_out)$@


# set
signal_set1_binout := $(bin_path)/$(signal_prefix)_set1$(bin_ext)
signal_set2_binout := $(bin_path)/$(signal_prefix)_set2$(bin_ext)

signal_set: $(signal_set1_binout)               \
            $(signal_set2_binout)
signal_set_test: signal_set1_test               \
                 signal_set2_test

signal_set1_test: $(signal_set1_binout)
	$<

signal_set2_test: $(signal_set2_binout)
	$< | cat -
	# press  or kill -QUIT to generate SIGQUIT

$(signal_set1_binout): $(signal_root)/set/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_set2_binout): $(signal_root)/set/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# sleep
signal_sleep_raw_binout := $(bin_path)/$(signal_prefix)_sleep_raw$(bin_ext)
signal_sleep_1_binout := $(bin_path)/$(signal_prefix)_sleep_1$(bin_ext)
signal_sleep_2_binout := $(bin_path)/$(signal_prefix)_sleep_2$(bin_ext)

signal_sleep: $(signal_sleep_raw_binout)        \
              $(singal_sleep_1_binout)           \
              $(signal_sleep_2_binout)
signal_sleep_test: signal_sleep_raw_test        \
                   signal_sleep_1_test           \
                   signal_sleep_2_test

signal_sleep_raw_test: $(signal_sleep_raw_binout)
	$< 1

signal_sleep_1_test: $(signal_sleep_1_binout)
	$< 1

signal_sleep_2_test: $(signal_sleep_2_binout)
	$< 1

$(signal_sleep_raw_binout): $(signal_root)/sleep/d.c  \
                            $(signal_root)/sleep/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_1_binout): $(signal_root)/sleep/d.c  \
                          $(signal_root)/sleep/r.c  \
                          $(signal_root)/sleep/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep_2_binout): $(signal_root)/sleep/d.c  \
                          $(signal_root)/sleep/r.c  \
                          $(signal_root)/sleep/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# timeout
signal_timeout1_binout := $(bin_path)/$(signal_prefix)_timeout1$(bin_ext)

signal_timeout: $(signal_timeout1_binout)
signal_timeout_test: signal_timeout1_test

signal_timeout1_test: $(signal_timeout1_binout)
	# $<
	echo "a" | $<

$(signal_timeout1_binout): $(signal_root)/timeout/t1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# wait
signal_wait1_binout := $(bin_path)/$(signal_prefix)_wait1$(bin_ext)

signal_wait: $(signal_wait1_binout)
signal_wait_test: signal_wait
	@echo "#skip ..."

$(signal_wait1_binout): $(signal_root)/wait/w1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# pause
signal_pause_binout := $(bin_path)/$(signal_prefix)_pause$(bin_ext)
signal_pause_pid := $(tmp_path)/$(signal_prefix)_pause.pid

signal_pause: $(signal_pause_binout)
signal_pause_test: signal_pause
	@echo "#skip ..."

$(signal_pause_binout): $(signal_root)/pause/p1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# child
signal_child_proc_binout := $(bin_path)/$(signal_prefix)_child_proc$(bin_ext)
signal_child_chld_binout := $(bin_path)/$(signal_prefix)_child_chld$(bin_ext)

signal_child: $(signal_child_proc_binout)       \
              $(signal_child_chld_binout)
signal_child_test: signal_child_proc_test         \
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
signal_info_name1_binout := $(bin_path)/$(signal_prefix)_name1$(bin_ext)

signal_info: $(signal_info_name1_binout)

signal_info_test: signal_info_name1_test

signal_info_name1_test: $(signal_info_name1_binout)
	$<

$(signal_info_name1_binout): $(signal_root)/info/n1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# suspend
signal_suspend_raw_binout := $(bin_path)/$(signal_prefix)_suspend_raw$(bin_ext)
signal_suspend_wrong_binout := $(bin_path)/$(signal_prefix)_suspend_wrong$(bin_ext)
signal_suspend_flag_binout := $(bin_path)/$(signal_prefix)_suspend_flag$(bin_ext)
signal_suspend_stage_binout := $(bin_path)/$(signal_prefix)_suspend_stage$(bin_ext)

signal_suspend: $(signal_suspend_raw_binout)    \
                $(signal_suspend_wrong_binout)  \
                $(signal_suspend_flag_binout)   \
                signal_suspend_stage
signal_suspend_test: signal_suspend_raw_test    \
                     signal_suspend_wrong_test  \
                     signal_suspend_flag_test   \
                     signal_suspend_stage_test

signal_suspend_stage: $(signal_suspend_stage_binout)

signal_suspend_raw_test: $(signal_suspend_raw_binout)
	# $<
	@echo "#skip ..."

signal_suspend_wrong_test: $(signal_suspend_wrong_binout)
	# $<
	@echo "#skip ..."

signal_suspend_flag_test: $(signal_suspend_flag_binout)
	# $<
	@echo "#skip ..."

signal_suspend_stage_test: $(signal_suspend_stage_binout)
	# $<
	@echo "#skip ..."

$(signal_suspend_raw_binout): $(signal_root)/suspend/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_suspend_wrong_binout): $(signal_root)/suspend/w.c
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

# abort
signal_abort_raw_binout := $(bin_path)/$(signal_prefix)_abort_raw$(bin_ext)
signal_abort_posix_binout := $(bin_path)/$(signal_prefix)_abort_posix$(bin_ext)

signal_abort: $(signal_abort_raw_binout)        \
              $(signal_abort_posix_binout)
signal_abort_test: signal_abort_raw_test        \
                   signal_abort_posix_test

signal_abort_raw_test: $(signal_abort_raw_binout)
	-$<

signal_abort_posix_test: $(signal_abort_posix_binout)
	-$<

$(signal_abort_raw_binout): $(signal_root)/abort/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_abort_posix_binout): $(signal_root)/abort/a1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# system
signal_system_dri_binout := $(bin_path)/$(signal_prefix)_system_dri$(bin_ext)
signal_system_art_binout := $(bin_path)/$(signal_prefix)_system_art$(bin_ext)

signal_system: $(signal_system_dri_binout)      \
               $(signal_system_art_binout)
signal_system_test: signal_system_dri_test      \
                    signal_system_art_test

signal_system_dri_test: $(signal_system_dri_binout)
	# $< "/bin/ed"
	$< "date"
	@echo "#skip ..."

signal_system_art_test: $(signal_system_art_binout)
	# $< "/bin/ed"
	$< "date"
	# @echo "#skip ..."

$(signal_system_dri_binout): $(signal_root)/system/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_system_art_binout): $(signal_root)/system/d.c   \
                             $(signal_root)/system/s.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# job
signal_job_tstp_binout := $(bin_path)/$(signal_prefix)_job_tstp$(bin_ext)

signal_job: signal_job_tstp
signal_job_test: signal_job_tstp_test

signal_job_tstp: $(signal_job_tstp_binout)

signal_job_tstp_test: $(signal_job_tstp_binout)
	# $<
	@echo "#skip ..."

$(signal_job_tstp_binout): $(signal_root)/job/j1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# eof
