

hi: $(bin_path)hi$(nm_binext)

$(tmp_path)hi$(nm_objext): $(src_path)hi.c
	$(CC) $(CFLAGS) $(CL_INCS) -c $^ $(nm_objout)$@

$(bin_path)hi$(nm_binext): $(tmp_path)hi$(nm_objext)
	$(LINK) $(tmp_path)hi$(nm_objext) $(nm_binout)$(bin_path)hi$(nm_binext)

