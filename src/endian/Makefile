
$(tmp_path)endian.o: $(src_path)endian.c
	$(CC) -c $(CFLAGS) -o $(tmp_path)endian.o $(src_path)endian.c

$(bin_path)endian: $(tmp_path)endian.o
	$(LINK) -o $(bin_path)endian $(tmp_path)endian.o
