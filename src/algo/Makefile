algo: is_unsigned_integer \
			is_unsigned_type

algo_test: is_unsigned_integer_test \
					 is_unsigned_type_test


algo_prefix := algo
INC += -I$(algo_root)


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
