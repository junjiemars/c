#
# ./configure --has-ds
# make clean test
#

ds_prefix := ds
INC += -I$(ds_root)

ds: double_linked_list													\
		single_linked_list													\
    list																				\
    queue																				\
		stack																				\
    tree																				\
    ds_calc																			\
    ds_d2b

ds_test: double_linked_list_test								\
				 single_linked_list_test								\
         list_test															\
         queue_test															\
				 stack_test															\
         tree_test															\
         ds_calc_test														\
         ds_d2b_test

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

# list
list_link_binout := $(bin_path)$(ds_prefix)_list_link$(bin_ext)
list_sort_binout := $(bin_path)$(ds_prefix)_list_sort$(bin_ext)

list: list_link																	\
      list_sort
list_test: list_link_test												\
           list_sort_test

list_link: $(list_link_binout)
list_sort: $(list_sort_binout)

list_link_test: list_link
	$(list_link_binout)
list_sort_test: list_sort
	$(list_sort_binout)

list_valgrind_test: list_link_test							\
                    list_sort_test
	valgrind --leak-check=full --track-origins=yes $(list_link_binout)
	valgrind --leak-check=full --track-origins=yes $(list_sort_binout)

$(list_link_binout): $(ds_root)list/link/test.c	\
										 $(ds_root)list/link/list.h
	$(CC) $(CFLAGS) $(INC)												\
		$(ds_root)list/link/test.c									\
		$(bin_out)$@

$(list_sort_binout): $(ds_root)list/link/test.c	\
										 $(ds_root)list/link/list.h
	$(CC) $(CFLAGS) $(INC) -DSORT=-1							\
		$(ds_root)list/link/test.c									\
		$(bin_out)$@


# queue
queue_array_binout := $(bin_path)$(ds_prefix)_queue_array$(bin_ext)

queue: $(queue_array_binout)

queue_test: queue_array_test

queue_valgrind_test: queue_valgrind_array_test

queue_valgrind_array_test: queue_array_test
	valgrind --leak-check=full --track-origins=yes $(queue_array_binout)

queue_array_test: $(queue_array_binout)
	$(queue_array_binout)

$(queue_array_binout): $(ds_root)queue/array/test.c		\
								       $(ds_root)queue/array/queue.h
	$(CC) $(CFLAGS) $(INC)												\
    $(ds_root)queue/array/test.c								\
    $(bin_out)$@


# stack
stack_array_binout := $(bin_path)$(ds_prefix)_stack_array$(bin_ext)
stack_linklist_binout := $(bin_path)$(ds_prefix)_stack_linklist$(bin_ext)
stack_d2b_binout := $(bin_path)$(ds_prefix)_stack_d2b$(bin_ext)

stack: $(stack_array_binout)										\
       $(stack_linklist_binout)									\
       $(stack_d2b_binout)											\

stack_test: stack_array_test										\
            stack_linklist_test									\
            stack_d2b_test											\

stack_valgrind_test: stack_valgrind_array_test 		\
                     stack_valgrind_linklist_test

stack_valgrind_array_test: stack_array_test
	valgrind --leak-check=full --track-origins=yes $(stack_array_binout)
stack_valgrind_linklist_test: stack_linklist_test
	valgrind --leak-check=full --track-origins=yes $(stack_linklist_binout)

stack_array_test: $(stack_array_binout)
	$(stack_array_binout)
stack_linklist_test: $(stack_linklist_binout)
	$(stack_linklist_binout)
stack_d2b_test: $(stack_d2b_binout)
	$(stack_d2b_binout) "2, 8"
	$(stack_d2b_binout) "3, 8"
	$(stack_d2b_binout) "99999, 8"
	$(stack_d2b_binout) "-1, 8"

$(stack_array_binout): $(ds_root)stack/array/test.c		\
								       $(ds_root)stack/array/stack.h
	$(CC) $(CFLAGS) $(INC)												\
    $(ds_root)stack/array/test.c								\
    $(bin_out)$@

$(stack_linklist_binout): $(ds_root)stack/linklist/test.c		\
								          $(ds_root)stack/linklist/stack.h
	$(CC) $(CFLAGS) $(INC)												\
    $(ds_root)stack/linklist/test.c							\
    $(bin_out)$@

$(stack_d2b_binout): $(ds_root)stack/array/stack.h	\
                     $(ds_root)stack/d2b.c
	$(CC) $(CFLAGS) $(INC) -I$(ds_root)stack/array	\
    $(ds_root)stack/d2b.c													\
    $(bin_out)$@

# tree

# d2b
ds_d2b_binout := $(bin_path)$(ds_prefix)_d2b$(bin_ext)

ds_d2b: $(ds_d2b_binout)
ds_d2b_test: ds_d2b
	$(ds_d2b_binout) "2, 8"
	$(ds_d2b_binout) "3, 8"
	$(ds_d2b_binout) "99999, 8"
	$(ds_d2b_binout) "-1, 8"

$(ds_d2b_binout): $(ds_root)stack/array/stack.h	\
                  $(ds_root)d2b/d2b.c
	$(CC) $(CFLAGS) $(INC) -I$(ds_root)stack/array	\
    $(ds_root)d2b/d2b.c														\
    $(bin_out)$@

# calc
ds_calc_binout := $(bin_path)$(ds_prefix)_calc$(bin_ext)

ds_calc: $(ds_calc_binout)
ds_calc_test: ds_calc
	$(ds_calc_binout) "1+2+3"
	$(ds_calc_binout) "1+2+3*4/5"
	$(ds_calc_binout) "(2+3)*4"
	$(ds_calc_binout) "2*3^(4+5)"

$(ds_calc_binout): $(ds_root)stack/array/stack.h		\
                   $(ds_root)queue/array/queue.h		\
                   $(ds_root)calc/calc.c
	$(CC) $(CFLAGS) $(INC)												\
    -I$(ds_root)stack/array											\
    -I$(ds_root)queue/array											\
    $(ds_root)calc/calc.c												\
    $(bin_out)$@
