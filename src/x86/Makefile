
x86: stack
x86_test: stack_test

INC += -I$(src_path)

stack_binout := $(bin_path)stack$(bin_ext)
stack: $(stack_binout)

stack_test: stack
	$(stack_binout)
$(stack_binout): $(src_path)stack/stack.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

