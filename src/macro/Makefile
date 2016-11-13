

macro_binout := $(bin_path)macro$(bin_ext)
macro_objout := $(tmp_path)macro$(obj_ext)


macro: $(macro_binout)


$(macro_objout): $(src_path)macro.c
	$(CC) $(CFLAGS) $(NM_INCS) -c $^ $(obj_out)$@

$(macro_binout): $(macro_objout)
	$(LINK) $^ $(bin_out)$@

