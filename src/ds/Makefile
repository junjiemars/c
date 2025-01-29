# -*- mode:makefile-gmake -*-
#
# ./configure --has-ds
# make clean test
#

ds: ds_dl_list                                  \
    ds_sl_list                                  \
    ds_list                                     \
    ds_queue                                    \
    ds_stack                                    \
    ds_tree                                     \
    ds_calc                                     \
    ds_d2b                                      \
    ds_python                                   \
    ds_string

ds_test: ds_dl_list_test                        \
         ds_sl_list_test                        \
         ds_list_test                           \
         ds_queue_test                          \
         ds_stack_test                          \
         ds_tree_test                           \
         ds_calc_test                           \
         ds_d2b_test                            \
         ds_python_test                         \
         ds_string_test

# env
ds_prefix := ds

INC += $(nm_inc_opt)$(ds_root) $(nm_inc_opt)$(root)/posix

ifeq ($(use_sanitize), yes)
CFLAGS += $(f_sanitize)
endif



# dl_list: double linked list
ds_dl_list_binout := $(bin_path)/$(ds_prefix)_dl_list$(bin_ext)

ds_dl_list: $(ds_dl_list_binout)
ds_dl_list_test: ds_dl_list
	$(ds_dl_list_binout)
ds_dl_list_valgrind_test: ds_dl_list
	valgrind --leak-check=full --track-origins=yes $(ds_dl_list_binout)

$(ds_dl_list_binout): $(ds_root)/double_linked_list/test.c  \
                      $(ds_root)/double_linked_list/list.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# sl_list: single linked list
ds_sl_list_binout := $(bin_path)/$(ds_prefix)_ds_sl_list$(bin_ext)

ds_sl_list: $(ds_sl_list_binout)
ds_sl_list_test: ds_sl_list
	$(ds_sl_list_binout)
ds_sl_list_valgrind_test: ds_sl_list
	valgrind --leak-check=full --track-origins=yes $(ds_sl_list_binout)

$(ds_sl_list_binout): $(ds_root)/single_linked_list/test.c  \
                      $(ds_root)/single_linked_list/list.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(bin_out)$@ $^



# list
ds_list_link_bone_binout := $(bin_path)/$(ds_prefix)_list_link_bone$(bin_ext)
ds_list_link_sorted_binout := $(bin_path)/$(ds_prefix)_list_link_sorted$(bin_ext)

ds_list: ds_list_link_bone                         \
         ds_list_link_sorted
ds_list_test: ds_list_link_bone_test \
              ds_list_link_sorted_test

ds_list_link_bone: $(ds_list_link_bone_binout)
ds_list_link_sorted: $(ds_list_link_sorted_binout)

ds_list_link_bone_test: ds_list_link_bone
	$(ds_list_link_bone_binout)
ds_list_link_sorted_test: ds_list_link_sorted
	$(ds_list_link_sorted_binout)

$(ds_list_link_bone_binout): $(ds_root)/list/link_bone/test.c \
                             $(ds_root)/list/link_bone/list.h
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $<

$(ds_list_link_sorted_binout): $(ds_root)/list/link_sorted/test.c \
                               $(ds_root)/list/link_sorted/list.h
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $<



# queue
ds_queue_binout := $(bin_path)/$(ds_prefix)_queue$(bin_ext)

ds_queue: $(ds_queue_binout)

ds_queue_test: ds_queue
	$(ds_queue_binout)

queue_valgrind_test: ds_queue_test
	valgrind --leak-check=full --track-origins=yes $(ds_queue_binout)

$(ds_queue_binout): $(ds_root)/queue/test.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $<



# stack
ds_stack_binout := $(bin_path)/$(ds_prefix)_stack$(bin_ext)

ds_stack: $(ds_stack_binout)

ds_stack_test: ds_stack
	$(ds_stack_binout)

ds_stack_valgrind_test: ds_stack_test
	valgrind --leak-check=full --track-origins=yes $(ds_stabck_binout)

$(ds_stack_binout): $(ds_root)/stack/test.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $<



# tree
ds_tree_binary_binout := $(bin_path)/$(ds_prefix)_tree_binary$(bin_ext)
ds_tree_tenary_binout := $(bin_path)/$(ds_prefix)_tree_tenary$(bin_ext)

ds_tree: $(ds_tree_binary_binout)               \
         $(ds_tree_tenary_binout)
ds_tree_test: ds_tree_binary_test               \
              ds_tree_tenary_test

ds_tree_binary_test: $(ds_tree_binary_binout)
	$<
ds_tree_tenary_test: $(ds_tree_tenary_binout)
	$<

$(ds_tree_binary_binout): $(ds_root)/tree/test.c  \
                          $(ds_root)/tree/tb1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(ds_tree_tenary_binout): $(ds_root)/tree/test.c  \
                          $(ds_root)/tree/te1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# d2b
ds_d2b_binout := $(bin_path)/$(ds_prefix)_d2b$(bin_ext)

ds_d2b: $(ds_d2b_binout)
ds_d2b_test: ds_d2b
	$(ds_d2b_binout) "2, 8"
	$(ds_d2b_binout) "3, 8"
	$(ds_d2b_binout) "99999, 8"
	$(ds_d2b_binout) "-1, 8"

$(ds_d2b_binout): $(ds_root)/d2b/d2b.c \
                  $(ds_root)/stack/array/stack.h
	$(CC) $(CFLAGS) $(INC) \
    -I$(ds_root)/stack/array \
    $(bin_out)$@ $<

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
	$(CC) $(CFLAGS) $(INC) \
    -I$(ds_root)/stack \
    -I$(ds_root)/queue \
    $(bin_out)$@ $<

# python
ds_python_pystr_binout := $(bin_path)/$(ds_prefix)_python_pystr$(bin_ext)

ds_python: $(ds_python_pystr_binout)
ds_python_test: ds_python
	$(ds_python_pystr_binout)

$(ds_python_pystr_binout): $(ds_root)/python/pystr1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $<



# string
ds_string_umbra_binout := $(bin_path)/$(ds_prefix)_string_umbra$(bin_ext)

ds_string: ds_string_umbra
ds_string_test: ds_string_umbra_test

ds_string_umbra: $(ds_string_umbra_binout)
ds_string_umbra_test: ds_string_umbra
	$(ds_string_umbra_binout)

$(ds_string_umbra_binout): $(ds_root)/string/umbra1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $<



.PYHONY: ds_dl_list ds_dl_list_test             \
         ds_sl_list ds_sl_list_test             \
         ds_list ds_list_test                   \
         ds_queue ds_queue_test                 \
         ds_stack ds_stack_test                 \
         ds_tree ds_tree_test                   \
         ds_calc ds_calc_test                   \
         ds_d ds_d_test 2b b_test               \
         ds_python ds_python_test               \
         ds_umbra_str ds_umbra_str_test


# eof
