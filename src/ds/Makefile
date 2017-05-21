
ds: list stack
ds_test: list_test stack_test

INC += -I$(src_path)

list_binout := $(bin_path)list$(bin_ext)
list_inc := $(INC) -I$(src_path)list
list: $(list_binout)
list_test: list
	$(list_binout)
list_valgrind_test: list
	valgrind --leak-check=full --track-origins=yes $(list_binout)
$(list_binout): $(src_path)list/test.c \
								$(src_path)list/list.c
	$(CC) $(CFLAGS) $(list_inc) $^ $(bin_out)$@

stack_binout := $(bin_path)stack$(bin_ext)
stack_inc := $(INC) -I$(src_path)list -I$(src_path)stack
stack: $(stack_binout)
stack_test: stack
	$(stack_binout)
stack_valgrind_test: stack
	valgrind --leak-check=full --track-origins=yes $(stack_binout)
$(stack_binout): $(src_path)stack/test.c \
								 $(src_path)stack/stack.c \
								 $(src_path)list/list.c
	$(CC) $(CFLAGS) $(stack_inc) $^ $(bin_out)$@
