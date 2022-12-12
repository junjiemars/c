#
# ./configure --has-x86
#


x86: x86_array                                  \
     x86_bone                                   \
     x86_branch                                 \
     x86_call                                   \
     x86_convert                                \
     x86_loop                                   \
     x86_pointer                                \
     x86_retval                                 \
     x86_structure                              \
     x86_typecast                               \
     x86_var

x86_test: x86_array_test                        \
          x86_bone_test                         \
          x86_branch_test                       \
          x86_call_test                         \
          x86_convert_test                      \
          x86_loop                              \
          x86_pointer_test                      \
          x86_retval_test                       \
          x86_structure_test                    \
          x86_typecast_test                     \
          x86_var_test

# env
x86_prefix = x86

INC += $(nm_inc_opt)$(x86_root) $(nm_inc_opt)$(root)/posix


ifdef RISKY
CFLAGS += -DRISKY=$(RISKY)
#NO_STACK_ALIGN = 1
NO_STRUCT_ALIGN = 1
NO_STACK_PROTECTOR = 1
NO_FRAME_POINTER = 1
NO_RED_ZONE=1
NO_INT_TO_POINTER_WARN = 1
NO_POINTER_TO_INT_WARN = 1
endif

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

ifeq ($(NO_FRAME_POINTER),1)
ifeq ($(CC_NAME), msvc)
ASFLAGS += -Oy
else
ASFLAGS += -fomit-frame-pointer
endif
endif

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


# array
x86_array_binout := $(bin_path)/$(x86_prefix)_array$(bin_ext)

x86_array: $(x86_array_binout)
x86_array_test: x86_array
	$(x86_array_binout)

$(x86_array_binout): $(x86_root)/array/array.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# bone
bone_binout := $(bin_path)/x86_bone$(bin_ext)

x86_bone: $(bone_binout)
x86_bone_test: x86_bone

$(bone_binout): $(x86_root)/bone/bone.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# branch
branch_binout := $(bin_path)/x86_branch$(bin_ext)
branch_objout := $(tmp_path)/x86_branch$(obj_ext)
branch_asmout := $(tmp_path)/x86_branch$(asm_ext)

x86_branch: $(branch_binout)
x86_branch_test: x86_branch

$(branch_binout): $(branch_objout)
	$(LINK) $(LDFLAGS) $^ $(bin_out)$@

$(branch_objout): $(branch_asmout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(branch_asmout): $(x86_root)/branch/branch.c
	$(ASM) $(ASFLAGS) $(INC) $(nm_stage_asm) $^ $(asm_out)$@


# call
x86_call_binout := $(bin_path)/$(x86_prefix)_call$(bin_ext)
x86_call_cppout := $(tmp_path)/$(x86_prefix)_call$(cpp_ext)
x86_call_asmout := $(tmp_path)/$(x86_prefix)_call$(asm_ext)
x86_call_objout := $(tmp_path)/$(x86_prefix)_call$(obj_ext)

x86_call: $(x86_call_binout)
x86_call_test: x86_call
	$(call_binout)

$(x86_call_binout): $(x86_call_objout)
	$(LINK) $(LDFLAGS) $^ $(bin_out)$@

$(x86_call_objout): $(x86_call_asmout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(x86_call_asmout): $(x86_call_cppout)
	$(ASM) $(ASFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(x86_call_cppout): $(x86_root)/call/call.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# convert
convert_binout := $(bin_path)/$(x86_prefix)_convert$(bin_ext)

x86_convert: $(convert_binout)
x86_convert_test: x86_convert
	$(convert_binout)

$(convert_binout): $(x86_root)/convert/convert.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# loop
loop_binout := $(bin_path)/x86_loop$(bin_ext)

x86_loop: $(loop_binout)
x86_loop_test: x86_loop
	$(loop_binout)

$(loop_binout): $(x86_root)/loop/loop.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# pointer
x86_pointer_binout := $(bin_path)/$(x86_prefix)_pointer$(bin_ext)
x86_pointer_cppout := $(tmp_path)/$(x86_prefix)_pointer$(cpp_ext)
x86_pointer_asmout := $(tmp_path)/$(x86_prefix)_pointer$(asm_ext)
x86_pointer_objout := $(tmp_path)/$(x86_prefix)_pointer$(obj_ext)

x86_pointer: $(x86_pointer_binout)
x86_pointer_test: x86_pointer
	$(x86_pointer_binout)

$(x86_pointer_binout): $(x86_pointer_objout)
	$(LINK) $(LDFLAGS) $^ $(bin_out)$@

$(x86_pointer_objout): $(x86_pointer_asmout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(bin_out)$@

$(x86_pointer_asmout): $(x86_pointer_cppout)
	$(ASM) $(ASFLAGS) $(nm_stage_asm) $^ $(bin_out)$@

$(x86_pointer_cppout): $(x86_root)/pointer/pointer.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(bin_out)$@


# retval
x86_retval_binout := $(bin_path)/$(x86_prefix)_retval$(bin_ext)
x86_retval_objout := $(tmp_path)/$(x86_prefix)_retval$(obj_ext)
x86_retval_asmout := $(tmp_path)/$(x86_prefix)_retval$(asm_ext)
x86_retval_cppout := $(tmp_path)/$(x86_prefix)_retval$(cpp_ext)

x86_retval: $(x86_retval_binout)
x86_retval_test: x86_retval

$(x86_retval_binout): $(x86_retval_objout)
	$(LINK) $^ $(bin_out)$@

$(x86_retval_objout): $(x86_retval_asmout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(x86_retval_asmout): $(x86_retval_cppout)
	$(ASM) $(ASFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(x86_retval_cppout): $(x86_root)/retval/retval.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# structure
x86_structure_binout := $(bin_path)/$(x86_prefix)_structure$(bin_ext)
x86_structure_cppout := $(tmp_path)/$(x86_prefix)_structure$(cpp_ext)
x86_structure_asmout := $(tmp_path)/$(x86_prefix)_structure$(asm_ext)
x86_structure_objout := $(tmp_path)/$(x86_prefix)_structure$(obj_ext)

x86_structure: $(x86_structure_binout)
x86_structure_test: x86_structure
	$(x86_structure_binout)

$(x86_structure_binout): $(x86_structure_objout)
	$(LINK) $(LDFLAGS) $^ $(bin_out)$@

$(x86_structure_objout): $(x86_structure_asmout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(x86_structure_asmout): $(x86_structure_cppout)
	$(ASM) $(ASFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(x86_structure_cppout): $(x86_root)/structure/structure.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# typecast
typecast_binout := $(bin_path)/x86_typecast$(bin_ext)

x86_typecast: $(typecast_binout)
x86_typecast_test: x86_typecast

$(typecast_binout): $(x86_root)/typecast/typecast.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# variable
var_binout := $(bin_path)/x86_var$(bin_ext)

x86_var: $(var_binout)
x86_var_test: x86_var
	$(var_binout)

$(var_binout): $(x86_root)/var/var.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


#@$(foreach f,$(stack_binout),$(f);)


# eof
