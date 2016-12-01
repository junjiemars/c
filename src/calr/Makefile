
calr_binout := $(bin_path)calr$(bin_ext)

calr: $(calr_binout)

calr_test: calr
	$(calr_binout)

$(calr_binout): $(tmp_path)calr$(obj_ext)
	$(LINK) $(LFLAGS) $^ $(bin_out)$@

$(tmp_path)calr$(obj_ext): $(tmp_path)calr$(asm_ext)
	$(CC) $(CFLAGS) -c $^ $(obj_out)$@

$(tmp_path)calr$(asm_ext): $(tmp_path)calr$(cpp_ext)
	$(ASM) $^ $(asm_out)$@

$(tmp_path)calr$(cpp_ext): $(src_path)calr.c
	$(CPP) $(CFLAGS) $(INC) $^ $(cpp_out)$@
