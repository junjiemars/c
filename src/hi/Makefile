

hi: $(bin_path)hi$(cl_binext)

$(tmp_path)hi$(cl_objext): $(src_path)hi.c
	$(CC) $(CFLAGS) $(CL_INCS) -c $^ $(cl_objout)$@

$(bin_path)hi$(cl_binext): $(tmp_path)hi$(cl_objext)
	$(LINK) $(tmp_path)hi$(cl_objext) $(cl_binout)$(bin_path)hi$(cl_binext)

