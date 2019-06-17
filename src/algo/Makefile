algo: _algo_ \
			algo_sizeof \
			bubble_sort \
			duff_device \
			dynamic_array \
			gcd \
			hash \
			is_unsigned_integer \
			is_unsigned_type \
			qsort \
			reverse \
			selection_sort

algo_test: _algo__test \
					 algo_sizeof_test \
					 bubble_sort_test \
					 duff_device_test \
					 dynamic_array_test \
					 gcd_test \
					 hash_test \
					 is_unsigned_integer_test \
					 is_unsigned_type_test \
					 qsort_test \
					 reverse_test \
					 selection_sort_test

algo_prefix := algo
INC += -I$(algo_root)

# _algo
_algo__binout := $(bin_path)$(algo_prefix)_algo_$(bin_ext)

_algo_: $(_algo__binout)
_algo__test: _algo_
	$(_algo__binout)

$(_algo__binout): $(algo_root)_algo_.c
	$(CC) $(CFLAGS) $(INC) $(nm_def_opt)_ALGO_=1 $^ $(bin_out)$@

# bubble sort
bubble_sort_binout := $(bin_path)$(algo_prefix)_bubble_sort$(bin_ext)

bubble_sort: $(bubble_sort_binout)
bubble_sort_test: bubble_sort
	$(bubble_sort_binout)

$(bubble_sort_binout): $(algo_root)_algo_.c \
                       $(algo_root)bubble_sort/bubble.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

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

# qsort
qsort_binout := $(bin_path)$(algo_prefix)_qsort$(bin_ext)

qsort: $(qsort_binout)
qsort_test: qsort
	$(qsort_binout)

$(qsort_binout): $(algo_root)qsort/qs.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

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

# selection sort
selection_sort_binout := $(bin_path)$(algo_prefix)_selection_sort$(bin_ext)

selection_sort: $(selection_sort_binout)
selection_sort_test: selection_sort
	$(selection_sort_binout)

$(selection_sort_binout): $(algo_root)_algo_.c \
                          $(algo_root)selection_sort/selection_sort.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
