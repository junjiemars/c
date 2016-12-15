
str_binout := $(bin_path)str$(bin_ext)

str: $(str_binout)

$(str_binout): $(src_path)str.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@

str_test: str
	$(str_binout)
