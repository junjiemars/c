
memory: alloc
memory_test: alloc_test


memory_binout := $(bin_path)memory$(bin_ext)

memory_cflags := $(CFLAGS) $(INC) -I$(src_root)utils

memory: $(memory_binout)
memory_test: memory
	$(memory_binout)

$(memory_binout): $(src_path)mem.c
	$(CC) $(memory_cflags) $^ $(bin_out)$@
