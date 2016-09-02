

hi: $(bin_path)hi

$(tmp_path)hi.o: $(src_path)hi.c
	$(CC) $(CFLAGS) $(CL_INCS) -c $^ -o $@

$(bin_path)hi: $(tmp_path)hi.o
	$(LINK) $(tmp_path)hi.o -o $(bin_path)hi

