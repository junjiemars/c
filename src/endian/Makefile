
endian_cflags += $(CFLAGS) $(INC) -I$(src_path) -O2

endian_binout := $(bin_path)endian$(bin_ext)
endian_objout := $(tmp_path)endian$(obj_ext)

endian: $(endian_binout)

$(endian_objout): $(src_path)endian.c
	$(CC) -c $(endian_cflags) $(INC) $^ $(obj_out)$@

$(endian_binout): $(endian_objout)
	$(LINK) $^ $(bin_out)$@
