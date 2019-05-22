
memory: alloc \
				bitfield \
				bit \
				byte \
				copy \
				endian \
				generic \
				rotate \
				shift \
				struct

memory_test: 	alloc_test \
							bitfield_test \
							bit_test \
							byte_test \
							copy_test \
							endian_test \
							generic_test \
							rotate_test \
							shift_test \
							struct_test

memory_prefix := memory

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


# alloc
alloc_a_binout := $(bin_path)$(memory_prefix)_alloca$(bin_ext)
alloc_m_binout := $(bin_path)$(memory_prefix)_malloc$(bin_ext)
alloc_c_binout := $(bin_path)$(memory_prefix)_calloc$(bin_ext)
alloc_re_binout := $(bin_path)$(memory_prefix)_realloc$(bin_ext)
alloc_align_binout := $(bin_path)$(memory_prefix)_memalign$(bin_ext)

alloc: $(alloc_a_binout) \
			 $(alloc_m_binout) \
       $(alloc_c_binout) \
       $(alloc_re_binout) \
			 $(alloc_align_binout)

alloc_test: alloca_test \
					  malloc_test \
						calloc_test \
						realloc_test \
						align_test

alloca_test: $(alloc_a_binout)
	$(alloc_a_binout)
malloc_test: $(alloc_m_binout)
	$(alloc_m_binout)
calloc_test: $(alloc_c_binout)
	$(alloc_c_binout)
realloc_test: $(alloc_re_binout)
	$(alloc_re_binout)
align_test: $(alloc_align_binout)
	$(alloc_align_binout)

$(alloc_a_binout): $(memory_root)alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(alloc_m_binout): $(memory_root)alloc/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(alloc_c_binout): $(memory_root)alloc/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(alloc_re_binout): $(memory_root)alloc/re.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(alloc_align_binout): $(memory_root)alloc/align.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

#bitfield
bitfield_binout := $(bin_path)$(memory_prefix)_bitfield$(bin_ext)

bitfield: $(bitfield_binout)
bitfield_test: bitfield
	$(bitfield_binout)

$(bitfield_binout): $(memory_root)bitfield/bitfield.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# bit
bit_binout := $(bin_path)$(memory_prefix)_bit$(bin_ext)

bit: $(bit_binout)
bit_test: bit
	$(bit_binout)

$(bit_binout): $(memory_root)bit/bit.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# byte
byte_binout := $(bin_path)$(memory_prefix)_byte$(bin_ext)
byte_cppout := $(tmp_path)byte$(cpp_ext)

byte: $(byte_binout)
byte_test: byte
	$(byte_binout)

$(byte_binout): $(byte_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(byte_cppout): $(memory_root)byte/byte.c
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


# rotate
rotate_binout := $(bin_path)$(memory_prefix)_rotate$(bin_ext)

rotate: $(rotate_binout)
rotate_test: rotate
	$(rotate_binout)
rotate_valgrind_test: rotate
	valgrind --leak-check=full --track-origins=yes $(rotate_binout)

$(rotate_binout): $(memory_root)rotate/rotate.h \
									$(memory_root)rotate/rotate.c \
									$(memory_root)rotate/r.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ \
		$(memory_root)rotate/rotate.c \
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
