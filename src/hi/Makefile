
$(tmp_path)hi.o: $(src_path)hi.c
	$(CC) -c $(CFLAGS) $(CL_INCS) $(src_path)hi.c -o $(tmp_path)hi.o

$(bin_path)hi: $(tmp_path)hi.o
	$(LINK) -o $(bin_path)hi $(tmp_path)hi.o

