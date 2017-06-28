
x86: stack_bone stack_loop
x86_test: stack_bone_test stack_loop_test

INC += -I$(src_path)

stack_bone_binout := $(bin_path)stack_bone$(bin_ext)
stack_bone: $(stack_bone_binout)

stack_loop_binout := $(bin_path)stack_loop$(bin_ext)
stack_loop: $(stack_loop_binout)

stack_bone_test: stack_bone
	$(stack_bone_binout)
$(stack_bone_binout): $(src_path)stack/bone.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

stack_loop_test: stack_loop
	$(stack_loop_binout)
$(stack_loop_binout): $(src_path)stack/loop.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

