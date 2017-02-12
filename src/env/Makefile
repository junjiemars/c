
env_binout := $(bin_path)env$(bin_ext)
env_objout := $(tmp_path)env$(obj_ext)

env_cflags += $(CFLAGS) $(INC) -I$(src_path)

$(env_objout): $(src_path)env.c
	$(CC) -c $(env_cflags) $^ $(obj_out)$@

$(env_binout): $(env_objout)
	$(LINK) $(LFLAGS) $^ $(bin_out)$@ 

env: $(env_binout)
env_test: env
	$(env_binout) --COUNT=2 --TEXT=Bonjour
	COUNT=2 $(env_binout)
	COUNT=3 TEXT="Bonjor" $(env_binout)
	COUNT=2 $(env_binout) --TEXT=Bonjour
