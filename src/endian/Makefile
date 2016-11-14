
endian_cflags += $(CFLAGS) $(NM_INCS) -I$(src_path) -O2

endian_binout := $(bin_path)endian$(bin_ext)
endian_objout := $(tmp_path)endian$(obj_ext)

endian: $(endian_binout)

$(endian_objout): $(src_path)endian.c
	$(CC) -c $(endian_cflags) $(NM_INCS) $^ $(obj_out)$@

$(endian_binout): $(endian_objout)
	$(LINK) $^ $(bin_out)$@
