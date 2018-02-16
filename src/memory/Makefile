
memory: memory_alloc									\
				memory_array									\
				memory_bit		  							\
				memory_byte										\
				memory_copy										\
				memory_convert								\
				memory_endian									\
				memory_generic								\
				memory_rotate									\
				memory_stack									\
				memory_struct

memory_test: 	memory_alloc_test				\
							memory_array_test				\
							memory_bit_test					\
							memory_byte_test	   		\
							memory_copy_test				\
							memory_convert_test			\
							memory_endian_test			\
							memory_generic_test			\
							memory_rotate_test			\
							memory_stack_test				\
							memory_struct_test


INC += -I$(memory_root)

ifdef RISKY
CFLAGS += -DRISKY=$(RISKY)
#NO_STACK_ALIGN = 1
NO_STRUCT_ALIGN = 1
NO_STACK_PROTECTOR = 1
NO_FRAME_POINTER = 1
NO_INT_TO_POINTER_WARN = 1
NO_POINTER_TO_INT_WARN = 1
NO_FORTIFY_SOURCE = 1
endif

# ifdef NO_STRUCT_ALIGN
# endif

ifdef NO_STRUCT_ALIGN
ifeq ($(CC_NAME), msvc)
CFLAGS += -Zp1
else
CFLAGS += -fpack-struct=1
endif
endif

ifdef NO_STACK_ALIGN
ifeq ($(CC_NAME), msvc)
CFLAGS += -F1
else
CFLAGS += -mstack-alignment=1
endif
endif

ifdef NO_STACK_PROTECTOR
ifeq ($(CC_NAME), msvc)
CFLAGS += -GS-
else
CFLAGS += -fno-stack-protector
endif
endif

#ifdef NO_FRAME_POINTER
#endif

ifdef NO_INT_TO_POINTER_WARN
ifeq ($(CC_NAME), msvc)
#C4312: 'type cast': conversion from 'int' to 'binky *' of greater size
CFLAGS += -wd4312
else
CFLAGS += -Wno-int-to-pointer-cast
endif
endif

ifdef NO_POINTER_TO_INT_WARN
ifeq ($(CC_NAME), msvc)
#C4311: 'type cast': pointer truncation from 'int *' to 'int'
CFLAGS += -wd4311 
else
CFLAGS += -Wno-pointer-to-int-cast
endif
endif

ifdef NO_FORTIFY_SOURCE
ifeq ($(CC_NAME), clang)
CFLAGS += -D_FORTIFY_SOURCE=0
endif
endif


bin_prefix := memory_

# alloc
alloc_binout := $(bin_path)$(bin_prefix)alloc$(bin_ext)

memory_alloc: $(alloc_binout)
memory_alloc_test: memory_alloc
	$(alloc_binout)

$(alloc_binout): $(memory_root)alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# array
array_binout := $(bin_path)$(bin_prefix)array$(bin_ext)

memory_array: $(array_binout)
memory_array_test: memory_array
	$(array_binout)

$(array_binout): $(memory_root)array/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


#bit
bit_binout := $(bin_path)$(bin_prefix)bit$(bin_ext)

memory_bit: $(bit_binout)
memory_bit_test: memory_bit
	$(bit_binout)

bit_lflags += $(LFLAGS) $(INC)

$(bit_binout): $(memory_root)bit/bit.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# byte
byte_binout := $(bin_path)$(bin_prefix)byte$(bin_ext)
byte_cppout := $(tmp_path)byte$(cpp_ext)

memory_byte: $(byte_binout)
memory_byte_test: memory_byte
	$(byte_binout)

$(byte_binout): $(byte_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(byte_cppout): $(memory_root)byte/byte.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@


# copy
copy_binout := $(bin_path)$(bin_prefix)copy$(bin_ext)

memory_copy: $(copy_binout)
memory_copy_test: memory_copy
	$(copy_binout)

$(copy_binout): $(memory_root)copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# convert
convert_binout := $(bin_path)$(bin_prefix)convert$(bin_ext)

memory_convert: $(convert_binout)
memory_convert_test: memory_convert
	$(convert_binout)

$(convert_binout): $(memory_root)convert/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# endian
endian_binout := $(bin_path)$(bin_prefix)endian$(bin_ext)

memory_endian: $(endian_binout)
memory_endian_test: memory_endian
	$(endian_binout)

$(endian_binout): $(memory_root)endian/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# generic
generic_binout := $(bin_path)$(bin_prefix)generic$(bin_ext)

memory_generic: $(generic_binout)
memory_generic_test: memory_generic
	$(generic_binout)

$(generic_binout): $(memory_root)generic/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# rotate
rotate_binout := $(bin_path)$(bin_prefix)rotate$(bin_ext)

memory_rotate: $(rotate_binout)
memory_rotate_test: memory_rotate
	$(rotate_binout)
rotate_valgrind_test: rotate
	valgrind --leak-check=full --track-origins=yes $(rotate_binout)

$(rotate_binout): $(memory_root)rotate/rotate.h \
									$(memory_root)rotate/rotate.c \
									$(memory_root)rotate/r.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ \
		$(memory_root)rotate/rotate.c \
		$(memory_root)rotate/r.c


# stack
stack_binout := $(bin_path)$(bin_prefix)stack$(bin_ext)

memory_stack: $(stack_binout)
memory_stack_test: memory_stack
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
struct_binout := $(bin_path)$(bin_prefix)struct$(bin_ext)

memory_struct: $(struct_binout)
memory_struct_test: memory_struct
	$(struct_binout)

$(struct_binout): $(memory_root)struct/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
