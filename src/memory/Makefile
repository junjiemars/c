#
# ./configure --has-memory --with-std=c99
#

memory: memory_alloc                            \
        memory_bitfield                         \
        memory_bit                              \
        memory_byte                             \
        memory_copy                             \
        memory_endian                           \
        memory_generic                          \
        memory_layout                           \
        memory_rotate                           \
        memory_shift                            \
        memory_struct

memory_test: memory_alloc_test                  \
             memory_bitfield_test               \
             memory_bit_test                    \
             memory_byte_test                   \
             memory_copy_test                   \
             memory_endian_test                 \
             memory_generic_test                \
             memory_layout_test                 \
             memory_rotate_test                 \
             memory_shift_test                  \
             memory_struct_test

# env
memory_prefix := memory

INC += $(nm_inc_opt)$(memory_root) $(nm_inc_opt)$(root)/posix

ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(cflags_sanitize)
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
memory_alloc_a_binout := $(bin_path)/$(memory_prefix)_alloca$(bin_ext)
memory_alloc_je_binout := $(bin_path)/$(memory_prefix)_je$(bin_ext)
memory_alloc_m_binout := $(bin_path)/$(memory_prefix)_malloc$(bin_ext)
memory_alloc_c_binout := $(bin_path)/$(memory_prefix)_calloc$(bin_ext)
memory_alloc_re_binout := $(bin_path)/$(memory_prefix)_realloc$(bin_ext)
memory_alloc_align_binout := $(bin_path)/$(memory_prefix)_align$(bin_ext)

memory_alloc: memory_alloc_std                  \
              memory_alloc_je
memory_alloc_test: memory_alloc_std_test        \
                   memory_alloc_je_test

memory_alloc_std: $(memory_alloc_a_binout)      \
                    $(memory_alloc_m_binout)    \
                  $(memory_alloc_c_binout)      \
                  $(memory_alloc_re_binout)     \
                  $(memory_alloc_align_binout)
memory_alloc_std_test: memory_alloc_a_test      \
                       memory_alloc_m_test      \
                       memory_alloc_c_test      \
                       memory_alloc_re_test     \
                       memory_alloc_align_test


memory_alloc_a_test: $(memory_alloc_a_binout)
	$(memory_alloc_a_binout)

ifeq (YES, $(has_jemalloc))
memory_alloc_je: $(memory_alloc_je_binout)
memory_alloc_je_test: memory_alloc_je
	$(memory_alloc_je_binout)
else
memory_alloc_je:
	@echo "#skip memory_alloc_je_test, missing jemalloc."
memory_alloc_je_test: memory_alloc_je
endif # end of has_jemalloc

memory_alloc_m_test: $(memory_alloc_m_binout)
	$(memory_alloc_m_binout)
memory_alloc_c_test: $(memory_alloc_c_binout)
	$(memory_alloc_c_binout)
memory_alloc_re_test: $(memory_alloc_re_binout)
	$(memory_alloc_re_binout)
memory_alloc_align_test: $(memory_alloc_align_binout)
	$(memory_alloc_align_binout)

$(memory_alloc_a_binout): $(memory_root)/alloc/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_alloc_je_binout): $(memory_root)/alloc/je.c
	$(CC) $(CFLAGS) $(INC) $(jemalloc_cflags) $^ $(bin_out)$@ $(jemalloc_ldlibs)

$(memory_alloc_m_binout): $(memory_root)/alloc/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_alloc_c_binout): $(memory_root)/alloc/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_alloc_re_binout): $(memory_root)/alloc/re.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(memory_alloc_align_binout): $(memory_root)/alloc/align.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# bitfield
memory_bitfield_binout := $(bin_path)/$(memory_prefix)_bitfield$(bin_ext)

memory_bitfield: $(memory_bitfield_binout)
memory_bitfield_test: memory_bitfield
	$(memory_bitfield_binout)

$(memory_bitfield_binout): $(memory_root)/bitfield/bitfield.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# bit
memory_bit_binout := $(bin_path)/$(memory_prefix)_bit$(bin_ext)

memory_bit: $(memory_bit_binout)
memory_bit_test: memory_bit
	$(memory_bit_binout)

$(memory_bit_binout): $(memory_root)/bit/bit.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# byte
memory_byte_binout := $(bin_path)/$(memory_prefix)_byte$(bin_ext)
memory_byte_cppout := $(tmp_path)/byte$(cpp_ext)

memory_byte: $(memory_byte_binout)
memory_byte_test: memory_byte
	$(memory_byte_binout)

$(memory_byte_binout): $(memory_byte_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(memory_byte_cppout): $(memory_root)/byte/byte.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@


# copy
mem_copy_binout := $(bin_path)/$(memory_prefix)_copy$(bin_ext)

memory_copy: $(mem_copy_binout)
memory_copy_test: memory_copy
	$(mem_copy_binout) 5698 10

$(mem_copy_binout): $(memory_root)/copy/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# endian
memory_endian_binout := $(bin_path)/$(memory_prefix)_endian$(bin_ext)

memory_endian: $(memory_endian_binout)
memory_endian_test: memory_endian
	$(memory_endian_binout)

$(memory_endian_binout): $(memory_root)/endian/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# generic
memory_generic_binout := $(bin_path)/$(memory_prefix)_generic$(bin_ext)

memory_generic: $(memory_generic_binout)
memory_generic_test: memory_generic
	$(memory_generic_binout)

$(memory_generic_binout): $(memory_root)/generic/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# layout
ifdef STACK_SIZE
ifeq ($(CC_NAME), clang)
ldflags_layout := -Wl,-stack_size -Wl,0x10000
endif
endif

memory_layout_size_binout := $(bin_path)/$(memory_prefix)_layout_size$(bin_ext)

memory_layout: $(memory_layout_size_binout)
memory_layout_test: memory_layout
	$(memory_layout_size_binout)

$(memory_layout_size_binout): $(memory_root)/layout/size.c
	$(CC) $(CFLAGS) $(INC) $^ $(ldflags_layout) $(bin_out)$@

# rotate
memory_rotate_binout := $(bin_path)/$(memory_prefix)_rotate$(bin_ext)

memory_rotate: $(memory_rotate_binout)
memory_rotate_test: memory_rotate
	$(memory_rotate_binout)
memory_rotate_valgrind_test: memory_rotate
	valgrind --leak-check=full --track-origins=yes $(memory_rotate_binout)

$(memory_rotate_binout): $(memory_root)/rotate/rotate.h   \
                           $(memory_root)/rotate/rotate.c \
                         $(memory_root)/rotate/r.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@						\
		$(memory_root)/rotate/rotate.c								\
		$(memory_root)/rotate/r.c


# shift
memory_shift_binout := $(bin_path)/$(memory_prefix)_memory_shift$(bin_ext)

memory_shift: $(memory_shift_binout)
memory_shift_test: memory_shift
	$(memory_shift_binout)

$(memory_shift_binout): $(memory_root)/shift/shift.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# struct
memory_struct_binout := $(bin_path)/$(memory_prefix)_struct$(bin_ext)

memory_struct: $(memory_struct_binout)
memory_struct_test: memory_struct
	$(memory_struct_binout)

$(memory_struct_binout): $(memory_root)/struct/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


.PHONY: memory_alloc memory_alloc_test          \
        memory_bit memory_bit_test              \
        memory_bitfield memory_bitfield_test    \
        memory_byte memory_byte_test            \
        memory_copy memory_copy_test            \
        memory_endian memory_endian_test        \
        memory_generic memory_generic_test      \
        memory_layout memory_layout_test        \
        memory_rotate memory_rotate_test        \
        memory_shift memory_shift_test          \
        memory_struct memory_struct_test

# eof
