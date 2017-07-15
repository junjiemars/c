
prep_cflags += $(CFLAGS)

prep_binout := $(bin_path)prep$(bin_ext)
prep_objout := $(tmp_path)prep$(obj_ext)
prep_cppout := $(tmp_path)prep$(cpp_ext)

prep: $(prep_binout)
prep_test: prep
	$(prep_binout)

$(prep_cppout): $(src_path)prep.c
	$(CPP) $(nm_stage_pre) $(prep_cppflags) $^ > $@

$(prep_objout): $(prep_cppout)
	$(CC) $(nm_stage_c) $(prep_cflags) $^ $(obj_out)$@

$(prep_binout): $(prep_objout)
	$(LINK) $^ $(bin_out)$@
