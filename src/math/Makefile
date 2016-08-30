
$(lib_path)math.o: $(src_path)math1.c
	$(CC) -c $(CFLAGS) -std=c99 -o $(lib_path)math.o $(src_path)math1.c

$(bin_path)math: $(lib_path)math.o
	$(LINK) -o $(bin_path)math $(lib_path)math.o
