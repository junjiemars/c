

pointer_binout := $(bin_path)pointer$(bin_ext)


pointer: $(pointer_binout)

pointer_cflags += $(CFLAGS) $(INC)

ifeq ($(CC_NAME), gcc)
	pointer_cflags += -std=c99
endif


$(pointer_binout): $(src_path)p.c 
	$(CC) $(pointer_cflags) $^ $(bin_out)$@

pointer_test: pointer 
	$(pointer_binout)

