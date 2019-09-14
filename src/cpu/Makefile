
cpu: cpu_info

cpu_test: cpu_info_test

cpu_prefix := cpu

INC += -I$(cpu_root)



# info
cpu_info_binout := $(bin_path)$(cpu_prefix)_info$(bin_ext)

cpu_info: $(cpu_info_binout)

cpu_info_test: cpu_info
	$(cpu_info_binout)

$(cpu_info_binout): $(cpu_root)info/info.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

