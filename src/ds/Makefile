
ds_prefix := ds

ds: list stack
ds_test: list_test stack_test

INC += -I$(ds_root)

# list

list_binout := $(bin_path)$(ds_prefix)_list$(bin_ext)

list: $(list_binout)
list_test: list
	$(list_binout)
list_valgrind_test: list
	valgrind --leak-check=full --track-origins=yes $(list_binout)

$(list_binout): $(ds_root)list/test.c \
								$(ds_root)list/list.c \
								$(ds_root)list/list.h
	$(CC) $(CFLAGS) $(INC)  \
		$(ds_root)list/test.c \
		$(ds_root)list/list.c \
		$(bin_out)$@


# stack

stack_binout := $(bin_path)$(ds_prefix)_stack$(bin_ext)
stack_inc += $(INC) -I$(ds_root)list

stack: $(stack_binout)
stack_test: stack
	$(stack_binout)

stack_valgrind_test: stack
	valgrind --leak-check=full --track-origins=yes $(stack_binout)

$(stack_binout): $(ds_root)stack/test.c \
								 $(ds_root)stack/stack.c \
								 $(ds_root)list/list.c \
								 $(ds_root)stack/stack.h
	$(CC) $(CFLAGS) $(stack_inc) \
		$(ds_root)stack/test.c \
		$(ds_root)stack/stack.c \
		$(ds_root)list/list.c \
		$(bin_out)$@

