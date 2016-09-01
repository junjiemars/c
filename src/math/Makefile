
math: geo $(bin_path)math



math_cflags := $(CFLAGS) -std=c99 $(CL_INCS)
math_ldflags := $(CL_LDS)


$(tmp_path)math.o: $(src_path)math1.c
	$(CC) $(math_cflags) -c $^ -o $@


$(bin_path)math: $(tmp_path)math.o 
	$(LINK) $(math_ldflags) $^ -lgeo -o $@
