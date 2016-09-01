
bits: $(bin_path)bits

$(tmp_path)bits.o: $(src_path)bits.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(bin_path)bits: $(tmp_path)bits.o
	$(LINK) $^ -o $@ 

