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
        signal_reentrant                        \
        signal_set                              \
        signal_sleep                            \
        signal_timeout                          \
        signal_wait                             \
        signal_pause                            \
        sigal_child

signal_test: signal_alarm_test                  \
             signal_reentrant_test              \
             signal_set_test                    \
             signal_sleep_test                  \
             signal_timeout_test                \
             signal_wait_test                   \
             signal_pause_test                  \
             signal_child_test

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


# reentrant
signal_reentrant_n_binout := $(bin_path)/$(signal_prefix)_reentrant_n$(bin_ext)
signal_reentrant_n_cppout := $(tmp_path)/$(signal_prefix)_reentrant_n$(cpp_ext)
signal_reentrant_r_binout := $(bin_path)/$(signal_prefix)_reentrant_r$(bin_ext)


signal_reentrant: $(signal_reentrant_n_binout)  \
                  $(signal_reentrant_r_binout)

signal_reentrant_test: signal_reentrant_n_test  \
                       signal_reentrant_r_test

signal_reentrant_n_test: $(signal_reentrant_n_binout)
	$< root daemon

signal_reentrant_r_test: $(signal_reentrant_r_binout)
	$< root daemon

$(signal_reentrant_n_binout): $(signal_reentrant_n_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(signal_reentrant_n_cppout): $(signal_root)/reentrant/r.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

$(signal_reentrant_r_binout): $(signal_root)/reentrant/r.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -D_REENTRANT_=1 $^ $(bin_out)$@


# set
signal_set1_binout := $(bin_path)/$(signal_prefix)_set1$(bin_ext)
signal_set2_binout := $(bin_path)/$(signal_prefix)_set2$(bin_ext)
signal_set1_source := $(tmp_path)/$(signal_prefix)_set1.c
signal_set1_awk := $(signal_root)/set/s1.awk
signal_set1_awk_in := $(signal_root)/set/s1.awk.in


signal_set: $(signal_set1_binout)               \
            $(signal_set2_binout)
signal_set_test: signal_set1_test               \
                 signal_set2_test

signal_set1_test: $(signal_set1_binout)
	$<
signal_set2_test: $(signal_set2_binout)
	$< | cat -
	# press  or kill -QUIT to generate SIGQUIT

$(signal_set1_binout): $(signal_set1_source)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_set2_binout): $(signal_root)/set/s2.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_set1_source): $(signal_set1_awk)       \
                       $(signal_set1_awk_in)
	awk -f $^ > $@


# sleep
signal_sleep1_binout := $(bin_path)/$(signal_prefix)_sleep1$(bin_ext)
signal_sleep2_binout := $(bin_path)/$(signal_prefix)_sleep2$(bin_ext)

signal_sleep: $(signal_sleep1_binout)           \
              $(signal_sleep2_binout)
signal_sleep_test: signal_sleep1_test           \
                   signal_sleep2_test

signal_sleep1_test: $(signal_sleep1_binout)
	$< 1

signal_sleep2_test: $(signal_sleep2_binout)
	$< 1

$(signal_sleep1_binout): $(signal_root)/sleep/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(signal_sleep2_binout): $(signal_root)/sleep/s2.c
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
signal_child_binout := $(bin_path)/$(signal_prefix)_child$(bin_ext)

signal_child: $(signal_child_binout)
signal_child_test: signal_child
	$(signal_child_binout)

$(signal_child_binout): $(signal_root)/child/c1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
