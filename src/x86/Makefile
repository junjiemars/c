
x86: stack
x86_test: stack_test

INC += -I$(src_path)

stack_binout := $(bin_path)stack_bone$(bin_ext) \
								$(bin_path)stack_retval$(bin_ext) \
								$(bin_path)stack_loop$(bin_ext)
stack: $(stack_binout)
stack_test: stack
	@$(foreach f,$(stack_binout),$(f);)

$(bin_path)stack_bone$(bin_ext): $(src_path)stack/bone.c
$(bin_path)stack_retval$(bin_ext): $(src_path)stack/retval.c
$(bin_path)stack_loop$(bin_ext): $(src_path)stack/loop.c

$(stack_binout): 
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

