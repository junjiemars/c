
cpu: cpu_info \
		 cpu_id

cpu_test: cpu_info_test \
					cpu_id_test

cpu_prefix := cpu

INC += -I$(cpu_root)


# info
cpu_info_binout := $(bin_path)$(cpu_prefix)_info$(bin_ext)

cpu_info: $(cpu_info_binout)

cpu_info_test: cpu_info
	$(cpu_info_binout)

$(cpu_info_binout): $(cpu_root)info/info.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# cpuid
cpu_id_binout := $(bin_path)$(cpu_prefix)_id$(bin_ext)

cpu_id: $(cpu_id_binout)
cpu_id_test: cpu_id
	$(cpu_id_binout)

$(cpu_id_binout): $(cpu_root)id/id.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
