# src/cpu

cpu: cpu_info																		\
		 cpu_id																			\
		 cpu_tile

cpu_test: cpu_info_test													\
	  		  cpu_id_test														\
          cpu_tile_test

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

# tile
cpu_tile_basic_binout := $(bin_path)$(cpu_prefix)_tile_basic$(bin_ext)

cpu_tile: $(cpu_tile_basic_binout)
cpu_tile_test: cpu_tile
	$(cpu_tile_basic_binout)

$(cpu_tile_basic_binout): $(cpu_root)tile/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
