
macro_cflags += $(CFLAGS) $(NM_INCS) -I$(src_path) -O2

macro_binout := $(bin_path)macro$(bin_ext)
macro_objout := $(tmp_path)macro$(obj_ext)

macro: $(macro_binout)

$(macro_objout): $(src_path)macro.c
	$(CC) -c $(macro_cflags) $^ $(obj_out)$@

$(macro_binout): $(macro_objout)
	$(LINK) $(LFLAGS) $^ $(bin_out)$@

