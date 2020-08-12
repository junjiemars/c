#
# ./configure --has-hi
#

hi_binout := $(bin_path)hi$(bin_ext)

hi: $(hi_binout)
hi_test: hi
	$(hi_binout)
	$(hi_binout) arlo

$(hi_binout): $(hi_root)hi.c 
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


