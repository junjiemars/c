
prep_cflags += $(CFLAGS) $(NM_INCS) -I$(src_path) -O2

prep_binout := $(bin_path)prep$(bin_ext)
prep_objout := $(tmp_path)prep$(obj_ext)
prep_preout := $(tmp_path)prep.i

prep: $(prep_binout)

$(prep_preout): $(src_path)prep.c
	$(CPP) $(prep_cflags) $^ > $@

$(prep_objout): $(prep_preout)
	$(CC) -c $(prep_c99_cflags) $^ $(obj_out)$@

$(prep_binout): $(prep_objout)
	$(LINK) $^ $(bin_out)$@
