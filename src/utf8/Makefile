
utf8_binout := $(bin_path)utf8$(nm_binext)
utf8_objout := $(tmp_path)utf8$(nm_objext)

utf8: $(utf8_binout)

$(utf8_objout): $(src_path)utf8.c
	$(CC) $(CFLAGS) $(NM_INCS) -c $^ $(nm_objout)$@

$(utf8_binout): $(utf8_objout)
	$(LINK) $^ $(nm_binout)$@

