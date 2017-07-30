
memory: alloc								\
				array								\
				bytes								\
				copy
memory_test: 	alloc_test								\
							array_test								\
							bytes_test								\
							copy_test

INC += -I$(src_path)

# alloc
alloc_binout := $(bin_path)alloc$(bin_ext)

alloc: $(alloc_binout)
alloc_test: alloc
	$(alloc_binout)

$(alloc_binout): $(src_path)alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# array
array_binout := $(bin_path)array$(bin_ext)

array: $(array_binout)
array_test: array
	$(array_binout)

$(array_binout): $(src_path)array/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# bytes
bytes_binout := $(bin_path)bytes$(bin_ext)
bytes_cppout := $(tmp_path)bytes$(cpp_ext)

bytes: $(bytes_binout)
bytes_test: bytes
	$(bytes_binout)

$(bytes_binout): $(bytes_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(bytes_cppout): $(src_path)bytes/b.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

# copy
copy_binout := $(bin_path)copy$(bin_ext)

copy: $(copy_binout)
copy_test: copy
	$(copy_binout)

$(copy_binout): $(src_path)copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
