
$(lib_path)endian.o: $(src_path)endian.c
	$(CC) -c $(CFLAGS) -o $(lib_path)endian.o $(src_path)endian.c

$(bin_path)endian: $(lib_path)endian.o
	$(LINK) -o $(bin_path)endian $(lib_path)endian.o
