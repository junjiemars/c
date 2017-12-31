 
x86: 	array								\
			bone                \
			branch							\
			call                \
			convert							\
			loop								\
			pointer 						\
			retval							\
			structure						\
			typecast						\
			var	

x86_test: array_test			\
					bone_test       \
					branch_test			\
					call_test				\
					convert_test		\
					loop						\
					pointer_test 		\
					retval_test			\
					structure_test	\
					typecast_test		\
					var_test


INC += -I$(x86_root)

ifdef RISKY
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
array_binout := $(bin_path)x86_array$(bin_ext)

array: $(array_binout)
array_test: array
	$(array_binout)

$(array_binout): $(x86_root)array/array.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# bone
bone_binout := $(bin_path)x86_bone$(bin_ext)

bone: $(bone_binout)
bone_test: bone

$(bone_binout): $(x86_root)bone/bone.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# branch
branch_binout := $(bin_path)x86_branch$(bin_ext)

branch: $(branch_binout)
branch_test: branch

$(branch_binout): $(x86_root)branch/branch.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# call
call_binout := $(bin_path)x86_call$(bin_ext)

call: $(call_binout)
call_test: call
	$(call_binout) 1 2 3

$(call_binout): $(x86_root)call/call.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# convert
convert_binout := $(bin_path)x86_convert$(bin_ext)

convert: $(convert_binout)
convert_test: convert
	$(convert_binout)

$(convert_binout): $(x86_root)convert/convert.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# loop 
loop_binout := $(bin_path)x86_loop$(bin_ext)

loop: $(loop_binout)
loop_test: loop
	$(loop_binout)

$(loop_binout): $(x86_root)loop/loop.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# pointer
pointer_binout := $(bin_path)x86_pointer$(bin_ext)

pointer: $(pointer_binout)
pointer_test: pointer
	$(pointer_binout)

$(pointer_binout): $(x86_root)pointer/pointer.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# retval
retval_binout := $(bin_path)x86_retval$(bin_ext)

retval: $(retval_binout)
retval_test: retval

$(retval_binout): $(x86_root)retval/retval.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# structure
structure_binout := $(bin_path)x86_structure$(bin_ext)

structure: $(structure_binout)
structure_test: structure

$(structure_binout): $(x86_root)structure/structure.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# typecast
typecast_binout := $(bin_path)x86_typecast$(bin_ext)

typecast: $(typecast_binout)
typecast_test: typecast

$(typecast_binout): $(x86_root)typecast/typecast.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# variable
var_binout := $(bin_path)x86_var$(bin_ext)

var: $(var_binout)
var_test: var 
	$(var_binout)

$(var_binout): $(x86_root)var/var.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


#@$(foreach f,$(stack_binout),$(f);)
