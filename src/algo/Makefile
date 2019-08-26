algo: _algo_ \
			algo_sizeof \
			algo_sort \
			duff_device \
			dynamic_array \
			gcd \
			hash \
			is_unsigned_integer \
			is_unsigned_type \
			reverse \
			algo_search \
			algo_strlen_utf8

algo_test: _algo__test \
					 algo_sizeof_test \
					 algo_sort_test \
					 duff_device_test \
					 dynamic_array_test \
					 gcd_test \
					 hash_test \
					 is_unsigned_integer_test \
					 is_unsigned_type_test \
					 reverse_test \
					 algo_search_test \
					 algo_strlen_utf8_test

algo_prefix := algo
INC += -I$(algo_root)

# _algo
_algo__binout := $(bin_path)$(algo_prefix)_algo_$(bin_ext)

_algo_: $(_algo__binout)
_algo__test: _algo_
	$(_algo__binout) x y z

$(_algo__binout): $(algo_root)_algo_.c
	$(CC) $(CFLAGS) $(INC) $(nm_def_opt)_ALGO_TEST_=1 $^ $(bin_out)$@


# duff device
duff_device_binout := $(bin_path)$(algo_prefix)_duff_device$(bin_ext)

duff_device: $(duff_device_binout)
duff_device_test: duff_device
	$(duff_device_binout)
	$(duff_device_binout) a
	$(duff_device_binout) a b
	$(duff_device_binout) a b c
	$(duff_device_binout) a b c d
	$(duff_device_binout) a b c d e
	$(duff_device_binout) a b c d e f
	$(duff_device_binout) a b c d e f g
	$(duff_device_binout) a b c d e f g h
	$(duff_device_binout) a b c d e f g h i

$(duff_device_binout): $(algo_root)duff_device/duff.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# dynamic array
dynamic_array_binout := $(bin_path)$(algo_prefix)_dynamic_array$(bin_ext)

dynamic_array: $(dynamic_array_binout)
dynamic_array_test: dynamic_array
	$(dynamic_array_binout)

$(dynamic_array_binout): $(algo_root)dynamic_array/da.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# gcd
gcd_binout := $(bin_path)$(algo_prefix)_gcd$(bin_ext)

gcd: $(gcd_binout)
gcd_test: gcd
	$(gcd_binout) 5 0
	$(gcd_binout) 206 40

$(gcd_binout): $(algo_root)gcd/gcd.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# hash
hash_kr1_binout := $(bin_path)$(algo_prefix)_hash_kr1$(bin_ext)
hash_kr2_binout := $(bin_path)$(algo_prefix)_hash_kr2$(bin_ext)
hash_djb2_binout := $(bin_path)$(algo_prefix)_hash_djb2$(bin_ext)
hash_sdbm_binout := $(bin_path)$(algo_prefix)_hash_sdbm$(bin_ext)
hash_jenkins_binout := $(bin_path)$(algo_prefix)_hash_jenkins$(bin_ext)

hash: $(hash_kr1_binout) \
			$(hash_kr2_binout) \
			$(hash_djb2_binout) \
			$(hash_sdbm_binout) \
			$(hash_jenkins_binout)
hash_test: hash
	$(hash_kr1_binout) "abcABC"
	$(hash_kr1_binout) "ABCabc"
	$(hash_kr2_binout) "abcABC"
	$(hash_kr2_binout) "ABCabc"
	$(hash_djb2_binout) "abcABC"
	$(hash_sdbm_binout) "abcABC"
	$(hash_jenkins_binout) "a"
	$(hash_jenkins_binout) "The quick brown"

$(hash_kr1_binout): $(algo_root)hash/kr1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(hash_kr2_binout): $(algo_root)hash/kr2.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(hash_djb2_binout): $(algo_root)hash/djb2.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(hash_sdbm_binout): $(algo_root)hash/sdbm.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(hash_jenkins_binout): $(algo_root)hash/jenkins.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# is unsigned integer
is_uint_binout := $(bin_path)$(algo_prefix)_is_uint$(bin_ext)
is_uint_cppout := $(tmp_path)$(algo_prefix)_is_uint$(cpp_ext)

is_unsigned_integer: $(is_uint_binout)
is_unsigned_integer_test: is_unsigned_integer
	$(is_uint_binout)

$(is_uint_binout): $(is_uint_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(is_uint_cppout): $(algo_root)is_unsigned_integer/is_uint.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# is unsigned type
is_utype_binout := $(bin_path)$(algo_prefix)_is_utype$(bin_ext)
is_utype_cppout := $(tmp_path)$(algo_prefix)_is_utype$(cpp_ext)

is_unsigned_type: $(is_utype_binout)
is_unsigned_type_test: is_unsigned_type
	$(is_utype_binout)

$(is_utype_binout): $(is_utype_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(is_utype_cppout): $(algo_root)is_unsigned_type/is_utype.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# reverse
reverse_string_binout := $(bin_path)$(algo_prefix)_reverse_string$(bin_ext)
reverse_linked_list_binout := $(bin_path)$(algo_prefix)_reverse_linked_list$(bin_ext)

reverse: $(reverse_string_binout) $(reverse_linked_list_binout)
reverse_test: reverse_string_test reverse_linked_list_test

reverse_string_test: $(reverse_string_binout)
	$(reverse_string_binout)
reverse_linked_list_test: $(reverse_linked_list_binout)
	$(reverse_linked_list_binout)

$(reverse_string_binout): $(algo_root)reverse/rev_str.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(reverse_linked_list_binout): $(algo_root)reverse/rev_linked_list.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# sizeof
algo_sizeof_binout := $(bin_path)$(algo_prefix)_sizeof$(bin_ext)
algo_sizeof_cppout := $(tmp_path)$(algo_prefix)_sizeof$(cpp_ext)

algo_sizeof: $(algo_sizeof_binout)
algo_sizeof_test: algo_sizeof
	$(algo_sizeof_binout)

$(algo_sizeof_binout): $(algo_sizeof_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(algo_sizeof_cppout): $(algo_root)sizeof/s.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# search
search_linear_binout := $(bin_path)$(algo_prefix)_search_linear$(bin_ext)
search_bsearch_binout := $(bin_path)$(algo_prefix)_search_bsearch$(bin_ext)
search_binary_binout := $(bin_path)$(algo_prefix)_search_binary$(bin_ext)

algo_search: $(search_linear_binout)  \
             $(search_bsearch_binout) \
             $(search_binary_binout)
algo_search_test: search_linear_test  \
                  search_bsearch_test \
                  search_binary_test

search_linear_test: $(search_linear_binout)
	$(search_linear_binout)
search_bsearch_test: $(search_bsearch_binout)
	$(search_bsearch_binout)
search_binary_test: $(search_binary_binout)
	$(search_binary_binout)

$(search_linear_binout): $(algo_root)_algo_.c \
												 $(algo_root)search/linear.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(search_bsearch_binout): $(algo_root)_algo_.c \
												 $(algo_root)search/bs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(search_binary_binout): $(algo_root)_algo_.c \
												 $(algo_root)search/binary.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# sort
sort_bubble_binout := $(bin_path)$(algo_prefix)_sort_bubble$(bin_ext)
sort_insertion_binout := $(bin_path)$(algo_prefix)_sort_insertion$(bin_ext)
sort_qsort_binout := $(bin_path)$(algo_prefix)_sort_qsort$(bin_ext)
sort_selection_binout := $(bin_path)$(algo_prefix)_sort_selection$(bin_ext)

algo_sort: $(sort_bubble_binout)     \
					 $(sort_insertion_binout)  \
           $(sort_qsort_binout)      \
           $(sort_selection_binout)

algo_sort_test: sort_bubble_test     \
								sort_insertion_test  \
                sort_qsort_test      \
                sort_selection_test

sort_bubble_test: $(sort_bubble_binout)
	$(sort_bubble_binout)
sort_insertion_test: $(sort_insertion_binout)
	$(sort_insertion_binout)
sort_qsort_test: $(sort_qsort_binout)
	$(sort_qsort_binout)
sort_selection_test: $(sort_selection_binout)
	$(sort_selection_binout)

$(sort_bubble_binout): $(algo_root)_algo_.c \
                       $(algo_root)sort/bubble.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(sort_insertion_binout): $(algo_root)_algo_.c \
													$(algo_root)sort/insertion.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(sort_qsort_binout): $(algo_root)sort/qs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(sort_selection_binout): $(algo_root)_algo_.c \
                          $(algo_root)sort/selection.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# strlen_utf8
algo_strlen_utf8_binout := $(bin_path)$(algo_prefix)_strlen_utf8$(bin_ext)

algo_strlen_utf8: $(algo_strlen_utf8_binout)
algo_strlen_utf8_test: algo_strlen_utf8
	$(algo_strlen_utf8_binout)

$(algo_strlen_utf8_binout): $(algo_root)/strlen_utf8/l.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
