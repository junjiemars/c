

pointer_binout := $(bin_path)pointer$(bin_ext)
pointer_objout := $(tmp_path)pointer$(obj_ext)


pointer: $(pointer_binout)


$(pointer_objout): $(src_path)p.c
	$(CC) $(CFLAGS) $(INC) -c $^ $(obj_out)$@

$(pointer_binout): $(pointer_objout) 
	$(LINK) $^ $(bin_out)$@

pointer_test: pointer 
	$(pointer_binout)

