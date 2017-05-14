

ptr: pp
ptr_test: pp_test

pp_binout := $(bin_path)pp$(bin_ext)
pp: $(pp_binout)
pp_test: pp
	$(pp_binout)
$(pp_binout): $(src_path)pp/pp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

#ptr_binout := $(bin_path)ptr$(bin_ext)
#
#
#ptr: $(ptr_binout)
#
#ptr_cflags += $(CFLAGS) $(INC)
#
#ifeq ($(CC_NAME), gcc)
#	ptr_cflags += -std=c99
#endif
#
#
#$(ptr_binout): $(src_path)p.c 
#	$(CC) $(ptr_cflags) $^ $(bin_out)$@
#
#ptr_test: ptr 
#	$(ptr_binout)

