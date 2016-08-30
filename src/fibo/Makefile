
# will affect global CFLAGS
# CFLAGS += -std=c99
$(lib_path)fibo.o: $(src_path)fibo.c
	$(CC) -c $(CFLAGS) -std=c99 -o $(lib_path)fibo.o $(src_path)fibo.c

$(bin_path)fibo: $(lib_path)fibo.o
	$(LINK) -o $(bin_path)fibo $(lib_path)fibo.o
