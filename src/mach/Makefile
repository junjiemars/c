#
# ./configure --has-mach --with-std=c99
#

mach: mach_alloc                                \
      mach_bitfield                             \
      mach_bit                                  \
      mach_byte                                 \
      mach_copy                                 \
      mach_endian                               \
      mach_generic                              \
      mach_layout                               \
      mach_rotate                               \
      mach_shift                                \
      mach_struct

mach_test: mach_alloc_test                      \
           mach_bitfield_test                   \
           mach_bit_test                        \
           mach_byte_test                       \
           mach_copy_test                       \
           mach_endian_test                     \
           mach_generic_test                    \
           mach_layout_test                     \
           mach_rotate_test                     \
           mach_shift_test                      \
           mach_struct_test

# env
mach_prefix := mach

INC += $(nm_inc_opt)$(mach_root) $(nm_inc_opt)$(root)/posix

ifdef _MEMORY_
	CFLAGS += $(f_sanitize)
endif


ifdef _RISKY_
CFLAGS += -D_RISKY_=$(_RISKY_)
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
mach_alloc_a_binout := $(bin_path)/$(mach_prefix)_alloca$(bin_ext)
mach_alloc_je_binout := $(bin_path)/$(mach_prefix)_je$(bin_ext)
mach_alloc_m_binout := $(bin_path)/$(mach_prefix)_malloc$(bin_ext)
mach_alloc_c_binout := $(bin_path)/$(mach_prefix)_calloc$(bin_ext)
mach_alloc_re_binout := $(bin_path)/$(mach_prefix)_realloc$(bin_ext)
mach_alloc_align_binout := $(bin_path)/$(mach_prefix)_align$(bin_ext)

mach_alloc: mach_alloc_std                      \
            mach_alloc_je
mach_alloc_test: mach_alloc_std_test            \
                 mach_alloc_je_test

mach_alloc_std: $(mach_alloc_a_binout)          \
                $(mach_alloc_m_binout)          \
                $(mach_alloc_c_binout)          \
                $(mach_alloc_re_binout)         \
                $(mach_alloc_align_binout)
mach_alloc_std_test: mach_alloc_a_test          \
                     mach_alloc_m_test          \
                     mach_alloc_c_test          \
                     mach_alloc_re_test         \
                     mach_alloc_align_test


mach_alloc_a_test: $(mach_alloc_a_binout)
	$(mach_alloc_a_binout)

ifeq (YES, $(has_jemalloc))
mach_alloc_je: $(mach_alloc_je_binout)
mach_alloc_je_test: mach_alloc_je
	$(mach_alloc_je_binout)
else
mach_alloc_je:
	@echo "#skip mach_alloc_je_test, missing jemalloc."
mach_alloc_je_test: mach_alloc_je
endif # end of has_jemalloc

mach_alloc_m_test: $(mach_alloc_m_binout)
	$(mach_alloc_m_binout)
mach_alloc_c_test: $(mach_alloc_c_binout)
	$(mach_alloc_c_binout)
mach_alloc_re_test: $(mach_alloc_re_binout)
	$(mach_alloc_re_binout)
mach_alloc_align_test: $(mach_alloc_align_binout)
	$(mach_alloc_align_binout)

$(mach_alloc_a_binout): $(mach_root)/alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(mach_alloc_je_binout): $(mach_root)/alloc/je.c
	$(CC) $(CFLAGS) $(INC) $(jemalloc_cflags) $^ $(bin_out)$@ $(jemalloc_ldlibs)

$(mach_alloc_m_binout): $(mach_root)/alloc/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(mach_alloc_c_binout): $(mach_root)/alloc/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(mach_alloc_re_binout): $(mach_root)/alloc/re.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(mach_alloc_align_binout): $(mach_root)/alloc/align.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# bitfield
mach_bitfield_binout := $(bin_path)/$(mach_prefix)_bitfield$(bin_ext)

mach_bitfield: $(mach_bitfield_binout)
mach_bitfield_test: mach_bitfield
	$(mach_bitfield_binout)

$(mach_bitfield_binout): $(mach_root)/bitfield/bitfield.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# bit
mach_bit_binout := $(bin_path)/$(mach_prefix)_bit$(bin_ext)

mach_bit: $(mach_bit_binout)
mach_bit_test: mach_bit
	$(mach_bit_binout)

$(mach_bit_binout): $(mach_root)/bit/bit.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# byte
mach_byte_binout := $(bin_path)/$(mach_prefix)_byte$(bin_ext)
mach_byte_cppout := $(tmp_path)/byte$(cpp_ext)
mach_byte_qry_binout := $(bin_path)/$(mach_prefix)_byte_qry$(bin_ext)

mach_byte: $(mach_byte_binout)                  \
           $(mach_byte_qry_binout)
mach_byte_test: mach_byte_test                  \
                mach_byte_qry_test

mach_byte_test: $(mach_byte_binout)
	$<
mach_byte_qry_test: $(mach_byte_qry_binout)
	$< int 123 2
	$< float 3.88 A
	$< float 3.8800004 A
	$< float 3.8800006 A
	$< float 3.8800008 A

$(mach_byte_binout): $(mach_byte_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(mach_byte_cppout): $(mach_root)/byte/byte.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

$(mach_byte_qry_binout): $(mach_root)/byte/q.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# copy
mem_copy_binout := $(bin_path)/$(mach_prefix)_copy$(bin_ext)

mach_copy: $(mem_copy_binout)
mach_copy_test: mach_copy
	$(mem_copy_binout) 5698 10

$(mem_copy_binout): $(mach_root)/copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# endian
mach_endian_binout := $(bin_path)/$(mach_prefix)_endian$(bin_ext)

mach_endian: $(mach_endian_binout)
mach_endian_test: mach_endian
	$(mach_endian_binout)

$(mach_endian_binout): $(mach_root)/endian/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# generic
mach_generic_binout := $(bin_path)/$(mach_prefix)_generic$(bin_ext)

mach_generic: $(mach_generic_binout)
mach_generic_test: mach_generic
	$(mach_generic_binout)

$(mach_generic_binout): $(mach_root)/generic/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# layout
ifdef STACK_SIZE
ifeq ($(CC_NAME), clang)
ldflags_layout := -Wl,-stack_size -Wl,0x10000
endif
endif

mach_layout_size_binout := $(bin_path)/$(mach_prefix)_layout_size$(bin_ext)

mach_layout: $(mach_layout_size_binout)
mach_layout_test: mach_layout
	$(mach_layout_size_binout)

$(mach_layout_size_binout): $(mach_root)/layout/size.c
	$(CC) $(CFLAGS) $(INC) $^ $(ldflags_layout) $(bin_out)$@

# rotate
mach_rotate_binout := $(bin_path)/$(mach_prefix)_rotate$(bin_ext)

mach_rotate: $(mach_rotate_binout)
mach_rotate_test: mach_rotate
	$(mach_rotate_binout)
mach_rotate_valgrind_test: mach_rotate
	valgrind --leak-check=full --track-origins=yes $(mach_rotate_binout)

$(mach_rotate_binout): $(mach_root)/rotate/rotate.h \
                       $(mach_root)/rotate/rotate.c \
                       $(mach_root)/rotate/r.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@						\
		$(mach_root)/rotate/rotate.c								\
		$(mach_root)/rotate/r.c


# shift
mach_shift_binout := $(bin_path)/$(mach_prefix)_mach_shift$(bin_ext)

mach_shift: $(mach_shift_binout)
mach_shift_test: mach_shift
	$(mach_shift_binout)

$(mach_shift_binout): $(mach_root)/shift/shift.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# struct
mach_struct_binout := $(bin_path)/$(mach_prefix)_struct$(bin_ext)

mach_struct: $(mach_struct_binout)
mach_struct_test: mach_struct
	$(mach_struct_binout)

$(mach_struct_binout): $(mach_root)/struct/s.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


.PHONY: mach_alloc mach_alloc_test          \
        mach_bit mach_bit_test              \
        mach_bitfield mach_bitfield_test    \
        mach_byte mach_byte_test            \
        mach_copy mach_copy_test            \
        mach_endian mach_endian_test        \
        mach_generic mach_generic_test      \
        mach_layout mach_layout_test        \
        mach_rotate mach_rotate_test        \
        mach_shift mach_shift_test          \
        mach_struct mach_struct_test

# eof
