# src/cpu

cpu: cpu_ls																			\
		 cpu_tile																		\
     cpu_time																		\
     cpu_vectorize

cpu_test: cpu_ls_test														\
          cpu_tile_test													\
          cpu_time_test													\
          cpu_vectorize_test

cpu_prefix := cpu

INC += -I$(cpu_root)

_VECTORIZE_ ?= 1


# ls
cpu_ls_binout := $(bin_path)/$(cpu_prefix)_ls$(bin_ext)

cpu_ls: $(cpu_ls_binout)

cpu_ls_test: cpu_ls
	$(cpu_ls_binout)

$(cpu_ls_binout): $(cpu_root)/ls/ls.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# tile
cpu_tile_basic_binout := $(bin_path)/$(cpu_prefix)_tile_basic$(bin_ext)

cpu_tile: $(cpu_tile_basic_binout)
cpu_tile_test: cpu_tile
	$(cpu_tile_basic_binout)

$(cpu_tile_basic_binout): $(cpu_root)/tile/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# time
cpu_time_basic_binout := $(bin_path)/$(cpu_prefix)_time_basic$(bin_exit)

cpu_time: $(cpu_time_basic_binout)
cpu_time_test: cpu_time
	$(cpu_time_basic_binout) 1

$(cpu_time_basic_binout): $(cpu_root)/time/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# vectorize
cpu_vectorize_loop_binout := $(bin_path)/$(cpu_prefix)_vectorize_loop$(bin_ext)

loop_vectorize_cflags := $(CFLAGS)
ifeq ($(_VECTORIZE_),1)
	loop_vectorize_cflags += $(loop_vectorizer_flags)
endif

cpu_vectorize: $(cpu_vectorize_loop_binout)
cpu_vectorize_test: cpu_vectorize
	$(cpu_vectorize_loop_binout)

$(cpu_vectorize_loop_binout): $(cpu_root)/vectorize/loop.c
	$(CC) $(loop_vectorize_cflags) $(INC) $^ $(bin_out)$@


