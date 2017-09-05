
x86:  call				\
			stack
x86_test: call_test				\
					stack_test

INC += -I$(x86_root)

# call
call_binout := $(bin_path)call$(bin_ext)

call: $(call_binout)
call_test: call
	$(call_binout) 1 2 3

$(call_binout): $(x86_root)call/call.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
	
# stack
stack_binout := $(bin_path)stack_bone$(bin_ext) \
								$(bin_path)stack_retval$(bin_ext) \
								$(bin_path)stack_loop$(bin_ext)
stack: $(stack_binout)
stack_test: stack
	@$(foreach f,$(stack_binout),$(f);)

$(bin_path)stack_bone$(bin_ext): $(x86_root)stack/bone.c
$(bin_path)stack_retval$(bin_ext): $(x86_root)stack/retval.c
$(bin_path)stack_loop$(bin_ext): $(x86_root)stack/loop.c

$(stack_binout): 
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

