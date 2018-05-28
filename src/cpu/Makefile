
cpu: cache_line_size

cpu_test: cache_line_size_test

cpu_prefix := cpu

INC += -I$(cpu_root)



# cache_line_size
cache_line_size_binout := $(bin_path)$(cpu_prefix)_cache_line_size$(bin_ext)

cache_line_size: $(cache_line_size_binout)

cache_line_size_test: cache_line_size
	$(cache_line_size_binout)

$(cache_line_size_binout): $(cpu_root)cache_line_size/line.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

