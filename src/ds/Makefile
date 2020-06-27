#
# ./configure --has-ds
# make clean test
#

ds_prefix := ds
INC += -I$(ds_root)

ds: double_linked_list													\
		single_linked_list													\
		stack																				\
    tree

ds_test: double_linked_list_test								\
				 single_linked_list_test								\
				 stack_test															\
         tree_test

# list

double_linked_list_binout := $(bin_path)$(ds_prefix)_double_linked_list$(bin_ext)

double_linked_list: $(double_linked_list_binout)
double_linked_list_test: double_linked_list
	$(double_linked_list_binout)
double_linked_list_valgrind_test: double_linked_list
	valgrind --leak-check=full --track-origins=yes $(double_linked_list_binout)

$(double_linked_list_binout): $(ds_root)double_linked_list/test.c \
							    					  $(ds_root)double_linked_list/list.c \
															$(ds_root)double_linked_list/list.h
	$(CC) $(CFLAGS) $(INC)  \
		$(ds_root)double_linked_list/test.c \
		$(ds_root)double_linked_list/list.c \
		$(bin_out)$@

# single linked list
single_linked_list_binout := $(bin_path)$(ds_prefix)_single_linked_list$(bin_ext)

single_linked_list: $(single_linked_list_binout)
single_linked_list_test: single_linked_list
	$(single_linked_list_binout)
single_linked_list_valgrind_test: single_linked_list
	valgrind --leak-check=full --track-origins=yes $(single_linked_list_binout)

$(single_linked_list_binout): $(ds_root)single_linked_list/test.c \
												      $(ds_root)single_linked_list/list.c \
													 	  $(ds_root)single_linked_list/list.h
	$(CC) $(CFLAGS) $(INC) \
		$(ds_root)single_linked_list/test.c \
		$(ds_root)single_linked_list/list.c \
		$(bin_out)$@


# stack
stack_array_binout := $(bin_path)$(ds_prefix)_stack_array$(bin_ext)
stack_linklist_binout := $(bin_path)$(ds_prefix)_stack_linklist$(bin_ext)

stack: $(stack_array_binout)										\
       $(stack_linklist_binout)
stack_test: stack_array_test										\
            stack_linklist_test
stack_valgrind_test: stack_array_test
	valgrind --leak-check=full --track-origins=yes $(stack_array_binout)

stack_array_test: $(stack_array_binout)
	$(stack_array_binout)
stack_linklist_test: $(stack_linklist_binout)
	$(stack_linklist_binout)

$(stack_array_binout): $(ds_root)stack/test_stack_array.c	\
                       $(ds_root)stack/stack_array.c			\
								       $(ds_root)stack/stack_array.h
	$(CC) $(CFLAGS) $(INC)												\
    $(ds_root)stack/stack_array.c								\
    $(ds_root)stack/test_stack_array.c					\
    $(bin_out)$@

$(stack_linklist_binout): $(ds_root)stack/linklist/test.c		\
								          $(ds_root)stack/linklist/stack.h
	$(CC) $(CFLAGS) $(INC)												\
    $(ds_root)stack/linklist/test.c							\
    $(bin_out)$@

# tree
