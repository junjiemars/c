
modern: 0 3.0 3.2

modern_test: 0_test 3.0_test 3.2_test

INC += -I$(src_path)

0_binout := $(bin_path)m0$(bin_ext)
0: $(0_binout)
$(0_binout): $(src_path)0/level0.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@
0_test: 0
	$(0_binout)

3.0_binout := $(bin_path)m30$(bin_ext)
3.0: $(3.0_binout)
$(3.0_binout): $(src_path)3.0/30.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
3.0_test: 3.0
	$(3.0_binout) a b c

3.2_binout := $(bin_path)m32$(bin_ext)
3.2: $(3.2_binout)
$(3.2_binout): $(src_path)3.2/32.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
3.2_test: 3.2
	$(3.2_binout)
