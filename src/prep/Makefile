
prep_cppflags += -I$(src_path) 
prep_cflags += $(CFLAGS)

prep_binout := $(bin_path)prep$(bin_ext)
prep_objout := $(tmp_path)prep$(obj_ext)
prep_cppout := $(tmp_path)prep$(cpp_ext)

prep: $(prep_binout)

$(prep_cppout): $(src_path)prep.c
	$(CPP) $(prep_cppflags) $^ > $@

$(prep_objout): $(prep_cppout)
	$(CC) -c $(prep_cflags) $^ $(obj_out)$@

$(prep_binout): $(prep_objout)
	$(LINK) $(LFLAGS) $^ $(bin_out)$@
