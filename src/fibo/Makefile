
fibo_cflags += $(CFLAGS) $(NM_INCS) -I$(src_path) -O2
fibo_binout := $(bin_path)fibo$(bin_ext)
fibo_objout := $(tmp_path)fibo$(obj_ext)

fibo: $(fibo_binout)

$(fibo_objout): $(src_path)fibo.c
	$(CC) -c $(fibo_cflags) $^ $(obj_out)$@

$(fibo_binout): $(fibo_objout)
	$(LINK) $^ $(bin_out)$@
