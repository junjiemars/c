#
# ./configure --has-signal
#


signal: signal_pause                            \
        signal_reentrant

signal_test: signal_pause_test                  \
             signal_reentrant_test


# env
signal_prefix := signal
INC += $(nm_inc_opt)$(signal_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME), msvc)
signal_pause:
	@echo "#skip ..."
signal_pause_test:
	@echo "#skip ..."
endif


# pause
signal_pause_binout := $(bin_path)/$(signal_prefix)_pause$(bin_ext)
signal_pause_pid := $(tmp_path)/$(signal_prefix)_pause.pid

signal_pause: $(signal_pause_binout)
signal_pause_test: signal_pause
	@echo "#skip ..."

$(signal_pause_binout): $(signal_root)/pause/p1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# reentrant
signal_ree_non1_binout := $(bin_path)/$(signal_prefix)_ree_non1$(bin_ext)

signal_reentrant: $(signal_ree_non1_binout)
signal_reentrant_test: signal_reentrant
	@echo "#skip ..."

$(signal_ree_non1_binout): $(signal_root)/reentrant/non1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# eof
