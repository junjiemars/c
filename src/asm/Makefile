
asm_binout := $(bin_path)asm$(bin_ext)

asm: $(asm_binout)
asm_test: asm
	$(asm_binout) 10

$(asm_binout): $(src_path)asm.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
