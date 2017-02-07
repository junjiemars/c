
random_binout := $(bin_path)random$(bin_ext)

random: $(random_binout)
random_test: random
	$(random_binout)

$(random_binout): $(src_path)r.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ 
