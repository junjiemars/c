

io_binout := $(bin_path)io$(bin_ext)

io: $(io_binout)

io_inc := $(INC) -I$(src_path) -I$(src_path)file
io_c := $(src_path)file/sum.c

$(io_binout): $(io_c) $(src_path)shell.c 
	$(CC) $(CFLAGS) $(io_inc) $^ $(bin_out)$@

io_test: io
	$(io_binout) --help
	$(io_binout) --type=file --input=$(tmp_path)seq.txt --output=$(tmp_path)sum.txt
