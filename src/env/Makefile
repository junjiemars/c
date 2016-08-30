
CFLAGS += -std=c99

$(lib_path)env.o: $(src_path)env.c
	$(CC) -c $(CFLAGS) -o $(lib_path)env.o $(src_path)env.c 

$(bin_path)env: $(lib_path)env.o
	$(LINK) -o $(bin_path)env $(lib_path)env.o
