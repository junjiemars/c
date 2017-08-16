
memory: alloc								\
				array								\
				bit		  						\
				byte								\
				copy								\
				convert

memory_test: 	alloc_test								\
							array_test								\
							bit_test									\
							byte_test	   							\
							copy_test									\
							convert_test

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


#bit
bit_binout := $(bin_path)bit$(bin_ext)

bit: $(bit_binout)
bit_test: bit
	$(bit_binout)

bit_lflags += $(LFLAGS) $(INC)

$(bit_binout): $(src_path)bit/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# byte
byte_binout := $(bin_path)byte$(bin_ext)
byte_cppout := $(tmp_path)byte$(cpp_ext)

byte: $(byte_binout)
byte_test: byte
	$(byte_binout)

$(byte_binout): $(byte_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(byte_cppout): $(src_path)byte/b.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@


# copy
copy_binout := $(bin_path)copy$(bin_ext)

copy: $(copy_binout)
copy_test: copy
	$(copy_binout)

$(copy_binout): $(src_path)copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# convert
convert_binout := $(bin_path)convert$(bin_ext)

convert: $(convert_binout)
convert_test: convert
	$(convert_binout)

$(convert_binout): $(src_path)convert/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


