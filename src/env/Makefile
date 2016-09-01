
env: $(bin_path)env

env_cflags := -std=c99

$(tmp_path)env.o: $(src_path)env.c
	$(CC) -c $(CFLAGS) $(env_cflags) \
        -o $(tmp_path)env.o $(src_path)env.c 

$(bin_path)env: $(tmp_path)env.o
	$(LINK) -o $(bin_path)env $(tmp_path)env.o
