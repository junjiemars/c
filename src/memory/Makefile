
memory: alloc						\
				array						\
				bit		  				\
				byte						\
				copy						\
				convert					\
				endian					\
				generic					\
				stack						\
				struct

memory_test: 	alloc_test				\
							array_test				\
							bit_test					\
							byte_test	   			\
							copy_test					\
							convert_test			\
							endian_test				\
							generic_test			\
							stack_test				\
							struct_test


INC += -I$(memory_root)

# alloc
alloc_binout := $(bin_path)alloc$(bin_ext)

alloc: $(alloc_binout)
alloc_test: alloc
	$(alloc_binout)

$(alloc_binout): $(memory_root)alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# array
array_binout := $(bin_path)array$(bin_ext)

array: $(array_binout)
array_test: array
	$(array_binout)

$(array_binout): $(memory_root)array/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


#bit
bit_binout := $(bin_path)bit$(bin_ext)

bit: $(bit_binout)
bit_test: bit
	$(bit_binout)

bit_lflags += $(LFLAGS) $(INC)

$(bit_binout): $(memory_root)bit/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# byte
byte_binout := $(bin_path)byte$(bin_ext)
byte_cppout := $(tmp_path)byte$(cpp_ext)

byte: $(byte_binout)
byte_test: byte
	$(byte_binout)

$(byte_binout): $(byte_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(byte_cppout): $(memory_root)byte/b.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@


# copy
copy_binout := $(bin_path)copy$(bin_ext)

copy: $(copy_binout)
copy_test: copy
	$(copy_binout)

$(copy_binout): $(memory_root)copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# convert
convert_binout := $(bin_path)convert$(bin_ext)

convert: $(convert_binout)
convert_test: convert
	$(convert_binout)

$(convert_binout): $(memory_root)convert/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# endian
endian_binout := $(bin_path)endian$(bin_ext)

endian: $(endian_binout)
endian_test: endian
	$(endian_binout)

$(endian_binout): $(memory_root)endian/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# generic
generic_binout := $(bin_path)generic$(bin_ext)

generic: $(generic_binout)
generic_test: generic
	$(generic_binout)

$(generic_binout): $(memory_root)generic/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stack
stack_binout := $(bin_path)stack$(bin_ext)

stack: $(stack_binout)
stack_test: stack
	$(stack_binout)
stack_valgrind_test: stack
	valgrind --leak-check=full --track-origins=yes $(stack_binout)

$(stack_binout): $(memory_root)stack/stack.h \
								 $(memory_root)stack/c.c \
								 $(memory_root)stack/stack.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ \
		$(memory_root)stack/stack.c \
		$(memory_root)stack/c.c


# struct
struct_binout := $(bin_path)struct$(bin_ext)

struct: $(struct_binout)
struct_test: struct
	$(struct_binout)

$(struct_binout): $(memory_root)struct/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
