
env: $(bin_path)env$(nm_binext)

env_cflags += $(CFLAGS) $(NM_INCS) -I$(src_path)

$(tmp_path)env$(nm_objext): $(src_path)env.c
	$(CC) -c $(env_cflags) $^ $(nm_objout)$@


$(bin_path)env$(nm_binext): $(tmp_path)env$(nm_objext)
	$(LINK) $^ $(nm_binout)$@ 
