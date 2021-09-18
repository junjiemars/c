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

x86_prefix = x86

INC += -I$(x86_root)


ifdef RISKY
CFLAGS += -DRISKY=$(RISKY)
#NO_STACK_ALIGN = 1
NO_STRUCT_ALIGN = 1
NO_STACK_PROTECTOR = 1
NO_FRAME_POINTER = 1
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

x86_branch: $(branch_binout)
x86_branch_test: x86_branch

$(branch_binout): $(x86_root)/branch/branch.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# call
call_binout := $(bin_path)/$(x86_prefix)_call$(bin_ext)

x86_call: $(call_binout)
x86_call_test: x86_call
	$(call_binout) 1 2 3

$(call_binout): $(x86_root)/call/call.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


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
pointer_binout := $(bin_path)/x86_pointer$(bin_ext)

x86_pointer: $(pointer_binout)
x86_pointer_test: x86_pointer
	$(pointer_binout)

$(pointer_binout): $(x86_root)/pointer/pointer.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# retval
retval_binout := $(bin_path)/x86_retval$(bin_ext)

x86_retval: $(retval_binout)
x86_retval_test: x86_retval

$(retval_binout): $(x86_root)/retval/retval.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# structure
structure_binout := $(bin_path)/x86_structure$(bin_ext)

x86_structure: $(structure_binout)
x86_structure_test: x86_structure

$(structure_binout): $(x86_root)/structure/structure.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


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
