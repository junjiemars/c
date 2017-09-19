
x86: 	bone                \
			call                \
			loop								\
			retval

x86_test: bone_test       \
					call_test				\
					loop						\
					retval_test


INC += -I$(x86_root)


# bone
bone_binout := $(bin_path)x86_bone$(bin_ext)

bone: $(bone_binout)
bone_test: bone

$(bone_binout): $(x86_root)bone/bone.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# retval
retval_binout := $(bin_path)x86_retval$(bin_ext)

retval: $(retval_binout)
retval_test: retval

$(retval_binout): $(x86_root)retval/retval.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# call
call_binout := $(bin_path)x86_call$(bin_ext)

call: $(call_binout)
call_test: call
	$(call_binout) 1 2 3

$(call_binout): $(x86_root)call/call.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# loop 
loop_binout := $(bin_path)x86_loop$(bin_ext)

loop: $(loop_binout)
loop_test: loop
	$(loop_binout)

$(loop_binout): $(x86_root)loop/loop.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


#@$(foreach f,$(stack_binout),$(f);)
