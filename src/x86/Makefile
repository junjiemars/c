
x86: 	bone                \
			branch							\
			call                \
			convert							\
			loop								\
			retval							\
			structure						\
			var	

x86_test: bone_test       \
					branch_test			\
					call_test				\
					convert_test		\
					loop						\
					retval_test			\
					structure_test	\
					var_test


INC += -I$(x86_root)


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


# variable
var_binout := $(bin_path)x86_var$(bin_ext)

var: $(var_binout)
var_test: var 
	$(var_binout)

$(var_binout): $(x86_root)var/var.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


#@$(foreach f,$(stack_binout),$(f);)
