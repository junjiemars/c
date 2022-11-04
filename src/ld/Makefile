#
# ./configure --has-ld
#


ifeq ($(CC_NAME), msvc)
io:
	@echo "#skip ..."
io_test:
	@echo "#skip ..."
else


ld: ld_bone                                     \
    ld_entry                                    \
    ld_nostartfiles                             \
    ld_nostdlib                                 \
    ld_stage                                    \
    ld_static                                   \
    ld_tiny                                     \
    ld_wrap

ld_test: ld_bone_test                           \
         ld_entry_test                          \
         ld_nostartfiles_test                   \
         ld_nostdlib_test                       \
         ld_stage_test                          \
         ld_static_test                         \
         ld_tiny_test                           \
         ld_wrap_test

endif

# env
ld_prefix := ld
INC += $(nm_inc_opt)$(ld_root) $(nm_inc_opt)$(root)/posix

ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif


# bone
ld_bone_binout := $(bin_path)/$(ld_prefix)_bone$(bin_ext)
ld_bone_m_objout := $(tmp_path)/$(ld_prefix)_bone_m$(obj_ext)
ld_bone_a_objout := $(tmp_path)/$(ld_prefix)_bone_a$(obj_ext)

ld_bone: $(ld_bone_binout)
ld_bone_test: ld_bone
	$(ld_bone_binout)

$(ld_bone_binout): $(ld_bone_m_objout)          \
                   $(ld_bone_a_objout)
	$(LINK) $^ $(bin_out) $@

$(ld_bone_m_objout): $(ld_root)/bone/m.c
	$(CC) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(ld_bone_a_objout): $(ld_root)/bone/a.c
	$(CC) $(INC) $(nm_stage_c) $^ $(obj_out)$@


# entry
ld_entry_binout := $(bin_path)/$(ld_prefix)_entry$(bin_ext)
ld_entry_objout := $(tmp_path)/$(ld_prefix)_entry$(obj_ext)

ifeq ($(ld_entry_opt),)
ld_entry:
	@echo "#skip ld_entry_test ..."
ld_entry_test: ld_entry
else
ld_entry: $(ld_entry_binout)
ld_entry_test: ld_entry
	$(ld_entry_binout) "abc"
endif

$(ld_entry_binout): $(ld_root)/entry/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_nostartfiles_opt) $(ld_entry_opt)_main1

$(ld_entry_objout): $(ld_root)/entry/e.c
	$(CC) $(INC) $^ $(nm_stage_c) $(obj_out)$@


# nostartfiles
ld_nostartfiles_binout := $(bin_path)/$(ld_prefix)_nostartfiles$(bin_ext)

ifeq ($(ld_nostartfiles_opt),)
ld_nostartfiles:
	@echo "#skip ld_nostartfiles_test ..."
ld_nostartfiles_test: ld_nostartfiles
else
ld_nostartfiles: $(ld_nostartfiles_binout)
ld_nostartfiles_test: ld_nostartfiles
	$(ld_nostartfiles_binout)
endif

$(ld_nostartfiles_binout): $(ld_root)/nostartfiles/nosfs.c
	$(CC) $(INC) $^ $(bin_out)$@ $(ld_nostartfiles_opt)

# stage
ld_stage_binout := $(bin_path)/$(ld_prefix)_stage$(bin_ext)
ld_stage_objout := $(tmp_path)/$(ld_prefix)_stage$(obj_ext)
ld_stage_asmout := $(tmp_path)/$(ld_prefix)_stage$(asm_ext)
ld_stage_cppout := $(tmp_path)/$(ld_prefix)_stage$(cpp_ext)
ld_stage_f_objout := $(tmp_path)/$(ld_prefix)_stage_f$(obj_ext)
ld_stage_f_asmout := $(tmp_path)/$(ld_prefix)_stage_f$(asm_ext)
ld_stage_f_cppout := $(tmp_path)/$(ld_prefix)_stage_f$(cpp_ext)


ld_stage: $(ld_stage_binout)
ld_stage_test: ld_stage
	$(ld_stage_binout)

$(ld_stage_binout): $(ld_stage_objout) $(ld_stage_f_objout)
	$(CC) $^ $(bin_out)$@

$(ld_stage_objout): $(ld_stage_asmout)
	$(CC) $(nm_stage_c) $^ $(obj_out)$@

$(ld_stage_f_objout): $(ld_stage_f_asmout)
	$(CC) $(nm_stage_c) $^ $(obj_out)$@

$(ld_stage_asmout): $(ld_stage_cppout)
	$(AS) $(ASFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(ld_stage_f_asmout): $(ld_stage_f_cppout)
	$(AS) $(ASFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(ld_stage_cppout): $(ld_root)/stage/s1.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

$(ld_stage_f_cppout): $(ld_root)/stage/f1.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# static
ld_static_binout := $(bin_path)/$(ld_prefix)_static$(bin_ext)

ifeq ($(ld_static_opt),)
ld_static:
	@echo "#skip ld_static_test ..."
ld_static_test: ld_static
else
ld_static: $(ld_static_binout)
ld_static_test: ld_static
	$(ld_static_binout) "abc"
endif

$(ld_static_binout): $(ld_root)/static/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_static_opt)


# nostdlib
ld_nostdlib_binout := $(bin_path)/$(ld_prefix)_nostdlib$(bin_ext)

ifeq ($(ld_nostdlib_opt),)
ld_nostdlib:
	@echo "#skip ld_nostdlib_test ..."
ld_nostdlib_test: ld_nostdlib
else
ld_nostdlib: $(ld_nostdlib_binout)
ld_nostdlib_test: ld_nostdlib
	$(ld_nostdlib_binout)
endif

$(ld_nostdlib_binout): $(ld_root)/nostdlib/nostd.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_nostdlib_opt) $(nm_lib_opt)c


# tiny
ld_tiny_binout := $(bin_path)/$(ld_prefix)_tiny$(bin_ext)
ld_tiny_objout := $(bin_path)/$(ld_prefix)_tiny$(obj_ext)

ld_tiny: $(ld_tiny_binout)
ld_tiny_test: ld_tiny
	$(ld_tiny_binout)

$(ld_tiny_binout): $(ld_tiny_objout)
	$(LINK) $^ $(bin_out)$@

$(ld_tiny_objout): $(ld_root)/tiny/t.c
	$(CC) $(INC) $(nm_stage_c) $^ $(bin_out)$@


# wrap
ld_wrap_binout := $(bin_path)/$(ld_prefix)_wrap$(bin_ext)

ifeq ($(ld_wrap_opt),)
ld_wrap:
	@echo "#skip ld_wrap_test ..."
ld_wrap_test: ld_wrap
else
ld_wrap_flags = $(ld_wrap_opt)malloc $(ld_wrap_opt)free
ld_wrap: $(ld_wrap_binout)
ld_wrap_test: ld_wrap
	$(ld_wrap_binout)
endif

$(ld_wrap_binout): $(ld_root)/wrap/w.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ld_wrap_flags)

# eof
