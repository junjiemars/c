

hi_binout := $(bin_path)hi$(nm_binext)
hi_objout := $(tmp_path)hi$(nm_objext)


hi: $(hi_binout)


$(hi_objout): $(src_path)hi.c
	$(CC) $(CFLAGS) $(NM_INCS) -c $^ $(nm_objout)$@

$(hi_binout): $(hi_objout)
	$(LINK) $^ $(nm_binout)$@

