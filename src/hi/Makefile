
hi_binout := $(bin_path)hi$(bin_ext)

hi: $(hi_binout)
hi_test: hi
	$(hi_binout)
	$(hi_binout) arlo

$(hi_binout): $(src_path)hi.c 
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


