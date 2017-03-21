


factorial_binout := $(bin_path)factorial$(bin_ext)

sicp: $(factorial_binout)
sicp_test: sicp
	$(factorial_binout) 10


$(factorial_binout): $(src_path)factorial/f.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@
