# -*- mode:makefile-gmake -*-
#
# ./configure --has-algo
# make clean test
#

algo: _algo_                                    \
      algo_compress                             \
      algo_coroutine                            \
      algo_duff_device                          \
      algo_dynamic_array                        \
      algo_fibonacci                            \
      algo_gcd                                  \
      algo_hash                                 \
      algo_is_unsigned_integer                  \
      algo_is_unsigned_type                     \
      algo_levenshtein                          \
      algo_limits                               \
      algo_loop                                 \
      algo_merge                                \
      algo_num                                  \
      algo_permute                              \
      algo_prime                                \
      algo_real                                 \
      algo_reverse                              \
      algo_search                               \
      algo_sizeof                               \
      algo_sort                                 \
      algo_strlen_utf8                          \
      algo_strscpy

algo_test: _algo_test                           \
           algo_compress_test                   \
           algo_coroutine_test                  \
           algo_duff_device_test                \
           algo_dynamic_array_test              \
           algo_fibonacci_test                  \
           algo_gcd_test                        \
           algo_hash_test                       \
           algo_is_unsigned_integer_test        \
           algo_is_unsigned_type_test           \
           algo_levenshtein_test                \
           algo_limits_test                     \
           algo_loop_test                       \
           algo_merge_test                      \
           algo_num_test                        \
           algo_permute_test                    \
           algo_prime                           \
           algo_real_test                       \
           algo_reverse_test                    \
           algo_search_test                     \
           algo_sizeof_test                     \
           algo_sort_test                       \
           algo_strlen_utf8_test                \
           algo_strscpy_test



# env
algo_prefix := algo

INC += $(nm_inc_opt)$(algo_root) $(nm_inc_opt)$(root)/posix

ifeq ($(use_sanitize), yes)
CFLAGS += $(f_sanitize)
endif

ifeq ($(NM_SYSTEM), Linux)
LDLIBS += -lm
endif

ifeq ($(CC_NAME), msvc)
posix_getopt_c := $(root)/posix/getopt.c
endif # end of msvc



# _algo
_algo_binout := $(bin_path)/$(algo_prefix)_algo_$(bin_ext)

_algo_: $(_algo_binout)
_algo_test: _algo_
	$(_algo_binout)

$(_algo_binout): $(algo_root)/_algo_.c
	$(CC) $(CFLAGS) $(INC) $(nm_def_opt)_ALGO_TEST_=1 $^ $(bin_out)$@

# compress
algo_compress_binout := $(bin_path)/$(algo_prefix)_compress$(bin_ext)

algo_compress: $(algo_compress_binout)
algo_compress_test: algo_compress
	$(algo_compress_binout) abbccc
	$(algo_compress_binout) 'a122333____^^(((('

$(algo_compress_binout): $(algo_root)/compress/c1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# coroutine
algo_coroutine_binout := $(bin_path)/$(algo_prefix)_coroutine$(bin_ext)

algo_coroutine: $(algo_coroutine_binout)
algo_coroutine_test: algo_coroutine
	$(algo_coroutine_binout)

$(algo_coroutine_binout): $(algo_root)/coroutine/cr1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# duff device
algo_duff_device_binout := $(bin_path)/$(algo_prefix)_duff_device$(bin_ext)
algo_duff_device_asmout := $(tmp_path)/$(algo_prefix)_duff_device$(asm_ext)

algo_duff_device: $(algo_duff_device_binout)
algo_duff_device_test: algo_duff_device
	$(algo_duff_device_binout)
	$(algo_duff_device_binout) 1
	$(algo_duff_device_binout) 2
	$(algo_duff_device_binout) 3
	$(algo_duff_device_binout) 4
	$(algo_duff_device_binout) 5
	$(algo_duff_device_binout) 6
	$(algo_duff_device_binout) 7
	$(algo_duff_device_binout) 8
	$(algo_duff_device_binout) 9

ifeq ($(CC_NAME), msvc)
$(algo_duff_device_binout): $(algo_root)/duff_device/duff.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

else
$(algo_duff_device_binout): $(algo_duff_device_asmout)
	$(CC) $^ $(bin_out)$@

$(algo_duff_device_asmout): $(algo_root)/duff_device/duff.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_asm) $^ $(asm_out)$@
endif

# dynamic array
algo_dynamic_array_binout := $(bin_path)/$(algo_prefix)_dynamic_array$(bin_ext)

algo_dynamic_array: $(algo_dynamic_array_binout)
algo_dynamic_array_test: algo_dynamic_array
	$(algo_dynamic_array_binout)

$(algo_dynamic_array_binout): $(algo_root)/dynamic_array/da.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# fibonacci
algo_fibonacci_binout := $(bin_path)/$(algo_prefix)_fibonacci$(bin_ext)

algo_fibonacci: $(algo_fibonacci_binout)
algo_fibonacci_test: algo_fibonacci
	$(algo_fibonacci_binout) 5

$(algo_fibonacci_binout): $(algo_root)/fibonacci/fibo.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# gcd
algo_gcd_binout := $(bin_path)/$(algo_prefix)_gcd$(bin_ext)

algo_gcd: $(algo_gcd_binout)
algo_gcd_test: algo_gcd
	$(algo_gcd_binout) 5 0
	$(algo_gcd_binout) 30 45

$(algo_gcd_binout): $(algo_root)/gcd/gcd.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# hash
algo_hash_bone_binout := $(bin_path)/$(algo_prefix)_hash_bone$(bin_ext)
algo_hash_kr1_binout := $(bin_path)/$(algo_prefix)_hash_kr1$(bin_ext)
algo_hash_kr2_binout := $(bin_path)/$(algo_prefix)_hash_kr2$(bin_ext)
algo_hash_djb2_binout := $(bin_path)/$(algo_prefix)_hash_djb2$(bin_ext)
algo_hash_sdbm_binout := $(bin_path)/$(algo_prefix)_hash_sdbm$(bin_ext)
algo_hash_jenkins_binout := $(bin_path)/$(algo_prefix)_hash_jenkins$(bin_ext)

algo_hash: algo_hash_bone                       \
           algo_hash_kr1                        \
           algo_hash_kr2                        \
           algo_hash_djb2                       \
           algo_hash_sdbm                       \
           algo_hash_jenkins

algo_hash_test: algo_hash_bone_test             \
                algo_hash_kr1_test              \
                algo_hash_kr2_test              \
                algo_hash_djb2_test             \
                algo_hash_sdbm_test             \
                algo_hash_jenkins_test

algo_hash_bone: $(algo_hash_bone_binout)
algo_hash_num: $(algo_hash_num_binout)
algo_hash_str: $(algo_hash_str_binout)
algo_hash_kr1: $(algo_hash_kr1_binout)
algo_hash_kr2: $(algo_hash_kr2_binout)
algo_hash_djb2: $(algo_hash_djb2_binout)
algo_hash_sdbm: $(algo_hash_sdbm_binout)
algo_hash_jenkins: $(algo_hash_jenkins_binout)

algo_hash_bone_test: algo_hash_bone_num_test \
                     algo_hash_bone_str_test
algo_hash_bone_num_test: $(algo_hash_bone_binout)
	echo "25 28 29 23 26 35 22 31 21 26 25 21 31 32 26 20 36 21 27 24 43" | $<
algo_hash_bone_str_test: $(algo_hash_bone_binout)
	echo "abc acb aaa abc bbb bcb bbc zoo bbbb" | $< --read=string
algo_hash_kr1_test: $(algo_hash_kr1_binout)
	echo "abc acb" | $<
algo_hash_kr2_test: $(algo_hash_kr2_binout)
	echo "abc acb" | $<
algo_hash_djb2_test: $(algo_hash_djb2_binout)
	echo "abc acb" | $<
algo_hash_sdbm_test: $(algo_hash_sdbm_binout)
	echo "abc acb" | $<
algo_hash_jenkins_test: $(algo_hash_jenkins_binout)
	echo "abc acb" | $<

$(algo_hash_bone_binout): $(algo_root)/hash/bone.c \
                          $(posix_getopt_c)
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(algo_hash_kr1_binout): $(algo_root)/hash/kr1.c \
                         $(algo_root)/hash/_hash_.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(algo_hash_kr2_binout): $(algo_root)/hash/kr2.c \
                         $(algo_root)/hash/_hash_.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(algo_hash_djb2_binout): $(algo_root)/hash/djb2.c \
                          $(algo_root)/hash/_hash_.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(algo_hash_sdbm_binout): $(algo_root)/hash/sdbm.c \
                          $(algo_root)/hash/_hash_.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(algo_hash_jenkins_binout): $(algo_root)/hash/jenkins.c \
                             $(algo_root)/hash/_hash_.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# is unsigned integer
algo_is_uint_binout := $(bin_path)/$(algo_prefix)_is_uint$(bin_ext)
algo_is_uint_cppout := $(tmp_path)/$(algo_prefix)_is_uint$(cpp_ext)

algo_is_unsigned_integer: $(algo_is_uint_binout)
algo_is_unsigned_integer_test: algo_is_unsigned_integer
	$(algo_is_uint_binout)

$(algo_is_uint_binout): $(algo_is_uint_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(algo_is_uint_cppout): $(algo_root)/is_unsigned_integer/is_uint.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# is unsigned type
algo_is_utype_binout := $(bin_path)/$(algo_prefix)_is_utype$(bin_ext)
algo_is_utype_cppout := $(tmp_path)/$(algo_prefix)_is_utype$(cpp_ext)

algo_is_unsigned_type: $(algo_is_utype_binout)
algo_is_unsigned_type_test: algo_is_unsigned_type
	$(algo_is_utype_binout)

$(algo_is_utype_binout): $(algo_is_utype_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(algo_is_utype_cppout): $(algo_root)/is_unsigned_type/is_utype.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# levenshtein
algo_levenshtein_binout := $(bin_path)/$(algo_prefix)_levenshtein$(bin_ext)

algo_levenshtein: $(algo_levenshtein_binout)
algo_levenshtein_test: algo_levenshtein
	$(algo_levenshtein_binout) "abc" "abc"
	$(algo_levenshtein_binout) "AB" "ABCDEF"
	$(algo_levenshtein_binout) "GUMBO" "GAMBOL"
	$(algo_levenshtein_binout) "GAMBOL" "GUMBO"
	$(algo_levenshtein_binout) "LAWYQQKPGKA" "YWCQPGK"

$(algo_levenshtein_binout): $(algo_root)/levenshtein/ld.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# limits
algo_limits_raw_binout := $(bin_path)/$(algo_prefix)_limits_raw$(bin_ext)

algo_limits: $(algo_limits_raw_binout)
algo_limits_test: algo_limits_raw_test

algo_limits_raw_test: $(algo_limits_raw_binout)
	$<

$(algo_limits_raw_binout): $(algo_root)/limits/raw1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# loop
algo_loop_tile_binout := $(bin_path)/$(algo_prefix)_loop_tile$(bin_ext)
algo_loop_invar_binout := $(bin_path)/$(algo_prefix)_loop_invar$(bin_ext)
algo_loop_hoist_binout := $(bin_path)/$(algo_prefix)_loop_hoist$(bin_ext)

algo_loop: $(algo_loop_tile_binout)             \
           $(algo_loop_invar_binout)            \
           $(algo_loop_hoist_binout)
algo_loop_test: algo_loop_tile_test             \
                algo_loop_invar_test            \
                algo_loop_hoist_test

algo_loop_tile_test: $(algo_loop_tile_binout)
	$<
algo_loop_invar_test: $(algo_loop_invar_binout)
	$<
algo_loop_hoist_test: $(algo_loop_hoist_binout)
	$<

$(algo_loop_tile_binout): $(algo_root)/loop/tile.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(algo_loop_invar_binout): $(algo_root)/loop/invar.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(algo_loop_hoist_binout): $(algo_root)/loop/hoist.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# merge
algo_merge_binout := $(bin_path)/$(algo_prefix)_merge$(bin_ext)

algo_merge: $(algo_merge_binout)
algo_merge_test: algo_merge
	$(algo_merge_binout)

$(algo_merge_binout): $(algo_root)/_algo_.c     \
                      $(algo_root)/merge/m1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# num
algo_num_int_binout := $(bin_path)/$(algo_prefix)_int$(bin_ext)

algo_num: $(algo_num_int_binout)
algo_num_test: algo_num
	$(algo_num_int_binout) 2835 1
	$(algo_num_int_binout) 2835 2
	$(algo_num_int_binout) 2835 3
	$(algo_num_int_binout) 2835 4

$(algo_num_int_binout): $(algo_root)/_algo_.c   \
                        $(algo_root)/num/n1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# permute
algo_permute_raw_binout := $(bin_path)/$(algo_prefix)_permute_raw$(bin_ext)

algo_permute: $(algo_permute_raw_binout)
algo_permute_test: algo_permute
	$(algo_permute_raw_binout)

$(algo_permute_raw_binout): $(algo_root)/_algo_.c				\
                            $(algo_root)/permute/p1.c 	\
                            $(algo_root)/permute/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# prime
algo_prime_binout := $(bin_path)/$(algo_prefix)_prime$(bin_ext)

algo_prime: $(algo_prime_binout)
algo_prime_test: algo_prime
	$(algo_prime_binout) 1 64

$(algo_prime_binout): $(algo_root)/prime/p1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)



# real
algo_real_r1_binout := $(bin_path)/$(algo_prefix)_real_r1$(bin_ext)
algo_real_r2_binout := $(bin_path)/$(algo_prefix)_real_r2$(bin_ext)

algo_real: $(algo_real_r1_binout) \
           $(algo_real_r2_binout)
algo_real_test: algo_real_r1_test \
                algo_real_r2_test

algo_real_r1_test: $(algo_real_r1_binout)
	$<
algo_real_r2_test: $(algo_real_r2_binout)
	$<

$(algo_real_r1_binout): $(algo_root)/real/r1.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(algo_real_r2_binout): $(algo_root)/real/r2.c \
                        $(algo_root)/real/real_test.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



# reverse
algo_reverse_string_binout := $(bin_path)/$(algo_prefix)_reverse_string$(bin_ext)
algo_reverse_linked_list_binout := $(bin_path)/$(algo_prefix)_reverse_linked_list$(bin_ext)

algo_reverse: $(algo_reverse_string_binout)       \
              $(algo_reverse_linked_list_binout)
algo_reverse_test: algo_reverse_string_test       \
                   algo_reverse_linked_list_test

algo_reverse_string_test: $(algo_reverse_string_binout)
	$(algo_reverse_string_binout)
algo_reverse_linked_list_test: $(algo_reverse_linked_list_binout)
	$(algo_reverse_linked_list_binout)

$(algo_reverse_string_binout): $(algo_root)/reverse/rev_str.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(algo_reverse_linked_list_binout): $(algo_root)/reverse/rev_linked_list.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# sizeof
algo_sizeof_binout := $(bin_path)/$(algo_prefix)_sizeof$(bin_ext)
algo_sizeof_cppout := $(tmp_path)/$(algo_prefix)_sizeof$(cpp_ext)

algo_sizeof: $(algo_sizeof_binout)
algo_sizeof_test: algo_sizeof
	$(algo_sizeof_binout)

$(algo_sizeof_binout): $(algo_sizeof_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(algo_sizeof_cppout): $(algo_root)/sizeof/s.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# search
algo_s_linear_binout := $(bin_path)/$(algo_prefix)_search_linear$(bin_ext)
algo_s_binary_binout := $(bin_path)/$(algo_prefix)_search_binary$(bin_ext)

algo_search: $(algo_s_linear_binout)            \
             $(algo_s_binary_binout)
algo_search_test: algo_s_linear_test            \
                  algo_s_binary_test

algo_s_linear_test: $(algo_s_linear_binout)
	$(algo_s_linear_binout)
algo_s_binary_test: $(algo_s_binary_binout)
	$(algo_s_binary_binout)

$(algo_s_linear_binout): $(algo_root)/_algo_.c    \
                         $(algo_root)/search/ls.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(algo_s_binary_binout): $(algo_root)/_algo_.c    \
                         $(algo_root)/search/bs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# sort
sort_bubble_binout := $(bin_path)/$(algo_prefix)_sort_bubble$(bin_ext)
sort_insert_binout := $(bin_path)/$(algo_prefix)_sort_insert$(bin_ext)
sort_qsort_binout := $(bin_path)/$(algo_prefix)_sort_qsort$(bin_ext)
sort_qsort_glibc_binout := $(bin_path)/$(algo_prefix)_sort_qsort_glibc$(bin_ext)
sort_select_binout := $(bin_path)/$(algo_prefix)_sort_select$(bin_ext)

algo_sort: $(algo_root)/_algo_h                 \
           $(algo_root)/sort/sort.h             \
           $(sort_bubble_binout)                \
           $(sort_insert_binout)                \
           $(sort_qsort_binout)                 \
           $(sort_qsort_glibc_binout)           \
           $(sort_select_binout)

algo_sort_test: sort_bubble_test                \
                sort_insert_test                \
                sort_qsort_test                 \
                sort_qsort_glibc_test           \
                sort_select_test

sort_bubble_test: $(sort_bubble_binout)
	$(sort_bubble_binout)
sort_insert_test: $(sort_insert_binout)
	$(sort_insert_binout)

sort_qsort: $(sort_qsort_binout)
sort_qsort_test: $(sort_qsort_binout)
	$(sort_qsort_binout)

sort_qsort_glibc: $(sort_qsort_glibc_binout)
sort_qsort_glibc_test: $(sort_qsort_glibc_binout)
	$(sort_qsort_glibc_binout)

sort_select_test: $(sort_select_binout)
	$(sort_select_binout)

$(sort_bubble_binout): $(algo_root)/_algo_.c      \
                       $(algo_root)/sort/bubble.c \
                       $(algo_root)/sort/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(sort_insert_binout): $(algo_root)/_algo_.c      \
                       $(algo_root)/sort/insert.c \
                       $(algo_root)/sort/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(sort_qsort_binout): $(algo_root)/_algo_.c     \
                      $(algo_root)/sort/qsort.c \
                      $(algo_root)/sort/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


$(sort_qsort_glibc_binout): $(algo_root)/_algo_.c     \
                      $(algo_root)/sort/qsort_glibc.c \
                      $(algo_root)/sort/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(sort_select_binout): $(algo_root)/_algo_.c      \
                       $(algo_root)/sort/select.c \
                       $(algo_root)/sort/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# strlen_utf8
algo_strlen_utf8_binout := $(bin_path)/$(algo_prefix)_strlen_utf8$(bin_ext)

algo_strlen_utf8: $(algo_strlen_utf8_binout)
algo_strlen_utf8_test: algo_strlen_utf8
	$(algo_strlen_utf8_binout)

$(algo_strlen_utf8_binout): $(algo_root)/strlen_utf8/l.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# strscpy
algo_strscpy_binout := $(bin_path)/$(algo_prefix)_strscpy$(bin_ext)

algo_strscpy: $(algo_strscpy_binout)
algo_strscpy_test: algo_strscpy
	$(algo_strscpy_binout)

$(algo_strscpy_binout): $(algo_root)/strscpy/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

.PHONY: _algo_ _algo_test
