
env_cflags += $(CFLAGS) $(INC) -I$(src_path) -O2
env_binout := $(bin_path)env$(bin_ext)
env_objout := $(tmp_path)env$(obj_ext)

env: $(env_binout)

$(env_objout): $(src_path)env.c
	$(CC) -c $(env_cflags) $^ $(obj_out)$@

$(env_binout): $(env_objout)
	$(LINK) $(LFLAGS) $^ $(bin_out)$@ 
