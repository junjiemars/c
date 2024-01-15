#
# ./configure --has-core
#
#

core:
	core_pipe

core_test:
	core_pipe_test

# env
core_prefix := core
# INC += $(nm_inc_opt)$(root)/posix

# core_pipe
core_pipe_binout := $(bin_path)/$(core_prefix)_pipe$(bin_ext)
core_pipe_dump_binout := $(bin_path)/$(core_prefix)_pipe_dump$(bin_ext)

core_pipe: $(core_pipe_binout) \
           $(core_pipe_dump_binout)
core_pipe_test: core_pipe
	echo "XXX"

$(core_pipe_binout): $(core_root)/pipe/p1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(core_pipe_dump_binout): $(core_root)/pipe/d1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# eof
