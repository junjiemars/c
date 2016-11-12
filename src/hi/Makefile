

hi_binout := $(bin_path)hi$(bin_ext)
hi_objout := $(tmp_path)hi$(obj_ext)


hi: $(hi_binout)


$(hi_objout): $(src_path)hi.c
	$(CC) $(CFLAGS) $(NM_INCS) -c $^ $(obj_out)$@

$(hi_binout): $(hi_objout)
	$(LINK) $^ $(bin_out)$@

