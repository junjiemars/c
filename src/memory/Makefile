
memory: alloc
memory_test: alloc_test

INC += -I$(src_path)

# alloc
alloc_binout := $(bin_path)alloc$(bin_ext)

alloc: $(alloc_binout)
alloc_test: alloc
	$(alloc_binout)

$(alloc_binout): $(src_path)alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
