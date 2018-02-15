
error: error_tuple
error_test: error_tuple_test

tuple_binout := $(bin_path)error_tuple$(bin_ext)
tuple_cppout := $(tmp_path)error_tuple$(cpp_ext)

error_tuple: $(tuple_binout)
error_tuple_test: error_tuple
	$(tuple_binout)

$(tuple_binout): $(tuple_cppout)
	$(LINK) $^ $(bin_out)$@

$(tuple_cppout): $(error_root)tuple/tuple.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

