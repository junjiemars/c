
memory: alloc								\
				copy
memory_test: 	alloc_test								\
							copy_test

INC += -I$(src_path)

# alloc
alloc_binout := $(bin_path)alloc$(bin_ext)

alloc: $(alloc_binout)
alloc_test: alloc
	$(alloc_binout)

$(alloc_binout): $(src_path)alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# copy
copy_binout := $(bin_path)copy$(bin_ext)

copy: $(copy_binout)
copy_test: copy
	$(copy_binout)

$(copy_binout): $(src_path)copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
