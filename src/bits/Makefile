
bits_cflags += $(CFLAGS) $(INC) -I$(src_path) -O2

bits_binout := $(bin_path)bits$(bin_ext)
bits_objout := $(tmp_path)bits$(obj_ext)

bits: $(bits_binout)

$(bits_objout): $(src_path)bits.c
	$(CC) $(bits_cflags) -c $^ $(obj_out)$@

$(bits_binout): $(bits_objout)
	$(LINK) $^ $(bin_out)$@ 

