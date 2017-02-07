
array_binout := $(bin_path)array$(bin_ext)

array: $(array_binout)
array_test: array
	$(array_binout)

$(array_binout): $(src_path)a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

