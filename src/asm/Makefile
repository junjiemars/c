
asm_binout := $(bin_path)asm$(bin_ext)

asm: $(asm_binout)
asm_test: asm
	$(asm_binout) 255

$(asm_binout): $(src_path)a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
