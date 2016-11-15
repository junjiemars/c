
prep_cflags += $(CFLAGS) $(NM_INCS) -I$(src_path) 

prep_binout := $(bin_path)prep$(bin_ext)
prep_objout := $(tmp_path)prep$(obj_ext)
prep_cppout := $(tmp_path)prep$(cpp_ext)

prep: $(prep_binout)

$(prep_cppout): $(src_path)prep.c
	$(CPP) $(prep_cflags) $^ > $@

$(prep_objout): $(prep_cppout)
	$(CC) -c $(prep_cppflags) $^ $(obj_out)$@

$(prep_binout): $(prep_objout)
	$(LINK) $^ $(bin_out)$@
