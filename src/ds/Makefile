# -*- mode:makefile-gmake -*-
#
# ./configure --has-ds
# make clean test
#


ds: double_linked_list                          \
    single_linked_list                          \
    ds_list                                     \
    ds_queue                                    \
    ds_stack                                    \
    ds_tree                                     \
    ds_calc                                     \
    ds_d2b                                      \
    ds_umbra_str

ds_test: double_linked_list_test                \
         single_linked_list_test                \
         ds_list_test                           \
         ds_queue_test                          \
         ds_stack_test                          \
         ds_tree_test                           \
         ds_calc_test                           \
         ds_d2b_test                            \
         ds_umbra_str_test

# env
ds_prefix := ds

INC += $(nm_inc_opt)$(ds_root) $(nm_inc_opt)$(root)/posix

ifeq (1, $(_MEMORY_))
ifeq (YES, $(has_sanitize))
CFLAGS += $(cflags_sanitize)
endif
endif


# list

double_linked_list_binout := $(bin_path)/$(ds_prefix)_double_linked_list$(bin_ext)

double_linked_list: $(double_linked_list_binout)
double_linked_list_test: double_linked_list
	$(double_linked_list_binout)
double_linked_list_valgrind_test: double_linked_list
	valgrind --leak-check=full --track-origins=yes $(double_linked_list_binout)

$(double_linked_list_binout): $(ds_root)/double_linked_list/test.c  \
                              $(ds_root)/double_linked_list/list.c  \
                              $(ds_root)/double_linked_list/list.h
	$(CC) $(CFLAGS) $(INC)                        \
    $(ds_root)/double_linked_list/test.c        \
    $(ds_root)/double_linked_list/list.c        \
    $(bin_out)$@

# single linked list
single_linked_list_binout := $(bin_path)/$(ds_prefix)_single_linked_list$(bin_ext)

single_linked_list: $(single_linked_list_binout)
single_linked_list_test: single_linked_list
	$(single_linked_list_binout)
single_linked_list_valgrind_test: single_linked_list
	valgrind --leak-check=full --track-origins=yes $(single_linked_list_binout)

$(single_linked_list_binout): $(ds_root)/single_linked_list/test.c    \
                              $(ds_root)/single_linked_list/list.c    \
                              $(ds_root)/single_linked_list/list.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)            \
    $(ds_root)/single_linked_list/test.c        \
    $(ds_root)/single_linked_list/list.c        \
    $(bin_out)$@

# list
list_link_bone_binout := $(bin_path)/$(ds_prefix)_list_link_bone$(bin_ext)
list_link_sorted_binout := $(bin_path)/$(ds_prefix)_list_link_sorted$(bin_ext)

ds_list: list_link
ds_list_test: list_link_test

list_link: list_link_bone \
           list_link_sorted

list_link_test: list_link_bone_test \
                list_link_sorted_test

list_link_bone: $(list_link_bone_binout)
list_link_sorted: $(list_link_sorted_binout)

list_link_bone_test: list_link_bone
	$(list_link_bone_binout)
list_link_sorted_test: list_link_sorted
	$(list_link_sorted_binout)

$(list_link_bone_binout): $(ds_root)/list/link_bone/test.c \
                          $(ds_root)/list/link_bone/list.h
	$(CC) $(CFLAGS) $(INC) \
    $(ds_root)/list/link_bone/test.c \
    $(bin_out)$@

$(list_link_sorted_binout): $(ds_root)/list/link_sorted/test.c \
				        						$(ds_root)/list/link_sorted/list.h
	$(CC) $(CFLAGS) $(INC) \
    $(ds_root)/list/link_sorted/test.c \
    $(bin_out)$@



# queue
ds_queue_binout := $(bin_path)/$(ds_prefix)_queue$(bin_ext)

ds_queue: $(ds_queue_binout)

ds_queue_test: ds_queue
	$(ds_queue_binout)

queue_valgrind_test: queue_valgrind_test

queue_valgrind_test: queue_array_test
	valgrind --leak-check=full --track-origins=yes $(queue_binout)

$(ds_queue_binout): $(ds_root)/queue/test.c     \
                    $(ds_root)/queue/queue.h
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@


# stack
ds_stack_binout := $(bin_path)/$(ds_prefix)_stack$(bin_ext)

ds_stack: $(ds_stack_binout)

ds_stack_test: ds_stack
	$(ds_stack_binout)

ds_stack_valgrind_array_test: ds_stack_test
		valgrind --leak-check=full --track-origins=yes $(ds_stabck_binout)

$(ds_stack_binout): $(ds_root)/stack/test.c     \
									  $(ds_root)/stack/stack.h
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@

# tree
ds_tree_bone_binout := $(bin_path)/$(ds_prefix)_tree_bone$(bin_ext)

ds_tree: $(ds_tree_bone_binout)
ds_tree_test: ds_tree_bone_test

ds_tree_bone_test: $(ds_tree_bone_binout)
	$<

$(ds_tree_bone_binout): $(ds_root)/tree/test.c      \
                        $(ds_root)/tree/bone/tb1.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@

# d2b
ds_d2b_binout := $(bin_path)/$(ds_prefix)_d2b$(bin_ext)

ds_d2b: $(ds_d2b_binout)
ds_d2b_test: ds_d2b
	$(ds_d2b_binout) "2, 8"
	$(ds_d2b_binout) "3, 8"
	$(ds_d2b_binout) "99999, 8"
	$(ds_d2b_binout) "-1, 8"

$(ds_d2b_binout): $(ds_root)/stack/array/stack.h  \
                  $(ds_root)/d2b/d2b.c
	$(CC) $(CFLAGS) $(INC) -I$(ds_root)/stack/array \
    $(ds_root)/d2b/d2b.c                          \
    $(bin_out)$@

# calc
ds_calc_binout := $(bin_path)/$(ds_prefix)_calc$(bin_ext)

ds_calc: $(ds_calc_binout)
ds_calc_test: ds_calc
	$(ds_calc_binout) "1+2+3="
	$(ds_calc_binout) "1+2+3*4/5="
	$(ds_calc_binout) "(2+3)*4="
	$(ds_calc_binout) "2*3^(4+5)="

$(ds_calc_binout): $(ds_root)/calc/calc.c       \
                   $(ds_root)/stack/stack.h     \
                   $(ds_root)/queue/queue.h
	$(CC) $(CFLAGS) $(INC)                        \
    -I$(ds_root)/stack                          \
    -I$(ds_root)/queue                          \
    $<                                          \
    $(bin_out)$@

# umbra str
ds_umbra_str_binout := $(bin_path)/$(ds_prefix)_umbra_str$(bin_ext)

ds_umbra_str: $(ds_umbra_str_binout)
ds_umbra_str_test: ds_umbra_str
	$(ds_umbra_str_binout)

$(ds_umbra_str_binout): $(ds_root)/umbra_str/us1.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@

# eof
