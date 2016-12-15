
erf_binout := $(bin_path)erf$(bin_ext)
erf_objout := $(tmp_path)erf$(obj_ext)

erf: $(erf_binout)

erf_lflags += $(LFLAGS) -lm

$(erf_objout): $(src_path)erf.c
	$(CC) $(CFLAGS) -c $^ $(obj_out)$@

$(erf_binout): $(erf_objout)
	$(LINK) $(erf_lflags) $^ $(bin_out)$@

erf_test: erf
	$(erf_binout)
