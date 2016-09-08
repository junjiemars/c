
math: geo $(bin_path)math$(nm_binext)



math_cflags = $(CFLAGS) $(NM_INCS) -std=c99
math_ldflags += $(NM_LDS)


$(tmp_path)math$(nm_objext): $(src_path)math1.c
	$(CC) $(math_cflags) -c $^ $(nm_objout)$@


$(bin_path)math$(nm_binext): $(tmp_path)math$(nm_objext)
	$(LINK) $(math_ldflags) $^ -lgeo $(nm_binout)$@
