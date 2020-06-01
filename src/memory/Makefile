# ./configure --has-memory

memory: memory_alloc														\
				bitfield																\
				memory_bit															\
				memory_byte															\
				copy																		\
				endian																	\
				generic																	\
				layout																	\
				rotate																	\
				shift																		\
				struct

memory_test: 	memory_alloc_test									\
							bitfield_test											\
				      memory_bit_test										\
				      memory_byte_test									\
				      copy_test													\
				      endian_test												\
				      generic_test											\
				      layout_test												\
				      rotate_test												\
				      shift_test												\
				      struct_test

memory_prefix := memory

INC += -I$(memory_root) -I$(root)posix

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


# alloc
memory_alloc_a_binout := $(bin_path)$(memory_prefix)_alloca$(bin_ext)
memory_alloc_m_binout := $(bin_path)$(memory_prefix)_malloc$(bin_ext)
memory_alloc_c_binout := $(bin_path)$(memory_prefix)_calloc$(bin_ext)
memory_alloc_re_binout := $(bin_path)$(memory_prefix)_realloc$(bin_ext)
memory_align_binout := $(bin_path)$(memory_prefix)_align$(bin_ext)

memory_alloc: $(memory_alloc_a_binout)					\
			 		    $(memory_alloc_m_binout)					\
              $(memory_alloc_c_binout)					\
              $(memory_alloc_re_binout)					\
			        $(memory_align_binout)

memory_alloc_test: memory_alloc_a_test					\
					         memory_alloc_m_test					\
						       memory_alloc_c_test					\
						       memory_alloc_re_test					\
						       memory_align_test

memory_alloc_a_test: $(memory_alloc_a_binout)
	$(memory_alloc_a_binout)
memory_alloc_m_test: $(memory_alloc_m_binout)
	$(memory_alloc_m_binout)
memory_alloc_c_test: $(memory_alloc_c_binout)
	$(memory_alloc_c_binout)
memory_alloc_re_test: $(memory_alloc_re_binout)
	$(memory_alloc_re_binout)
memory_align_test: $(memory_align_binout)
	$(memory_align_binout)

$(memory_alloc_a_binout): $(memory_root)alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_alloc_m_binout): $(memory_root)alloc/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_alloc_c_binout): $(memory_root)alloc/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_alloc_re_binout): $(memory_root)alloc/re.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_align_binout): $(memory_root)alloc/align.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

#bitfield
bitfield_binout := $(bin_path)$(memory_prefix)_bitfield$(bin_ext)

bitfield: $(bitfield_binout)
bitfield_test: bitfield
	$(bitfield_binout)

$(bitfield_binout): $(memory_root)bitfield/bitfield.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# bit
memory_bit_binout := $(bin_path)$(memory_prefix)_bit$(bin_ext)

bit: $(memory_bit_binout)
memory_bit_test: bit
	$(memory_bit_binout)

$(memory_bit_binout): $(memory_root)bit/bit.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# byte
memory_byte_binout := $(bin_path)$(memory_prefix)_byte$(bin_ext)
memory_byte_cppout := $(tmp_path)byte$(cpp_ext)

byte: $(memory_byte_binout)
memory_byte_test: byte
	$(memory_byte_binout)

$(memory_byte_binout): $(memory_byte_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(memory_byte_cppout): $(memory_root)byte/byte.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@


# copy
copy_binout := $(bin_path)$(memory_prefix)_copy$(bin_ext)

copy: $(copy_binout)
copy_test: copy
	$(copy_binout)

$(copy_binout): $(memory_root)copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# endian
endian_binout := $(bin_path)$(memory_prefix)_endian$(bin_ext)

endian: $(endian_binout)
endian_test: endian
	$(endian_binout)

$(endian_binout): $(memory_root)endian/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# generic
generic_binout := $(bin_path)$(memory_prefix)_generic$(bin_ext)

generic: $(generic_binout)
generic_test: generic
	$(generic_binout)

$(generic_binout): $(memory_root)generic/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# layout

ifdef STACK_SIZE
ifeq ($(CC_NAME), clang)
ldflags_layout := -Wl,-stack_size -Wl,0x10000
endif
endif

layout_size_binout := $(bin_path)$(memory_prefix)_layout_size$(bin_ext)

layout: $(layout_size_binout)
layout_test: layout
	$(layout_size_binout)

$(layout_size_binout): $(memory_root)layout/size.c
	$(CC) $(CFLAGS) $(INC) $^ $(ldflags_layout) $(bin_out)$@

# rotate
rotate_binout := $(bin_path)$(memory_prefix)_rotate$(bin_ext)

rotate: $(rotate_binout)
rotate_test: rotate
	$(rotate_binout)
rotate_valgrind_test: rotate
	valgrind --leak-check=full --track-origins=yes $(rotate_binout)

$(rotate_binout): $(memory_root)rotate/rotate.h	\
				  $(memory_root)rotate/rotate.c	\
				  $(memory_root)rotate/r.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@			\
		$(memory_root)rotate/rotate.c			\
		$(memory_root)rotate/r.c


# shift
shift_binout := $(bin_path)$(memory_prefix)_shift$(bin_ext)

shift: $(shift_binout)
shift_test: shift
	$(shift_binout)

$(shift_binout): $(memory_root)shift/shift.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# struct
struct_binout := $(bin_path)$(memory_prefix)_struct$(bin_ext)

struct: $(struct_binout)
struct_test: struct
	$(struct_binout)

$(struct_binout): $(memory_root)struct/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
