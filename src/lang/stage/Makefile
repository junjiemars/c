
pcalr_binout := $(bin_path)pcalr$(bin_ext)

pcalr: $(pcalr_binout)

pcalr_test: pcalr
	$(pcalr_binout)

$(pcalr_binout): $(tmp_path)pcalr$(obj_ext)
	$(LINK) $(LFLAGS) $^ $(bin_out)$@

$(tmp_path)pcalr$(obj_ext): $(tmp_path)pcalr$(asm_ext)
	$(AS) $(CFLAGS) -c $^ $(obj_out)$@

$(tmp_path)pcalr$(asm_ext): $(tmp_path)pcalr$(cpp_ext)
	$(CAS) $^ $(asm_out)$@

$(tmp_path)pcalr$(cpp_ext): $(src_path)pcalr.c
	$(CPP) $(CFLAGS) $(INC) $^ > $@
