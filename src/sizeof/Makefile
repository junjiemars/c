
sizeof_binout := $(bin_path)sizeof$(bin_ext)

sizeof: $(sizeof_binout)

$(sizeof_binout): $(src_path)sizeof.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@

sizeof_test: sizeof
	$(sizeof_binout)
