
modern: 0

modern_test: 0_test

0_binout := $(bin_path)m0$(bin_ext)

0: $(0_binout)

$(0_binout): $(src_path)0/level0.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@

0_test: 0
	$(0_binout)
