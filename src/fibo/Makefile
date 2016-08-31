

$(tmp_path)fibo.o: $(src_path)fibo.c
	$(CC) -c $(CFLAGS) -std=c99 -o $(tmp_path)fibo.o $(src_path)fibo.c

$(bin_path)fibo: $(tmp_path)fibo.o
	$(LINK) -o $(bin_path)fibo $(tmp_path)fibo.o
