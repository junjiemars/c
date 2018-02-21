
ds_prefix := ds
INC += -I$(ds_root)

ds: double_list              \
		stack

ds_test: double_list_test    \
				 stack_test

# list

double_list_binout := $(bin_path)$(ds_prefix)_double_list$(bin_ext)

double_list: $(double_list_binout)
double_list_test: double_list
	$(double_list_binout)
double_list_valgrind_test: double_list
	valgrind --leak-check=full --track-origins=yes $(double_list_binout)

$(double_list_binout): 	$(ds_root)double_list/test.c \
							    			$(ds_root)double_list/list.c \
												$(ds_root)double_list/list.h
	$(CC) $(CFLAGS) $(INC)  \
		$(ds_root)double_list/test.c \
		$(ds_root)double_list/list.c \
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

