

pointer_binout := $(bin_path)pointer$(bin_ext)
pointer_objout := $(tmp_path)pointer$(obj_ext)


pointer: $(pointer_binout)

pointer_cflags += $(CFLAGS) $(INC)

ifeq ($(CC_NAME), gcc)
	pointer_cflags += -std=c99
endif

$(pointer_objout): $(src_path)p.c
	$(CC) $(pointer_cflags) -c $^ $(obj_out)$@

$(pointer_binout): $(pointer_objout) 
	$(LINK) $^ $(bin_out)$@

pointer_test: pointer 
	$(pointer_binout)

