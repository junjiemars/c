
INC += -I$(error_root)

error: error_basic \
			 error_tuple

error_test: error_basic_test \
						error_tuple_test

# basic
basic_binout := $(bin_path)error_basic$(bin_ext)

error_basic: $(basic_binout)
error_basic_test: error_basic
	$(basic_binout) $(CURDIR)/Makefilex
	$(basic_binout) $(CURDIR)/Makefile

$(basic_binout): $(error_root)/basic/e.c
	$(CC) $(INC) $^ $(bin_out)$@

# tuple
tuple_binout := $(bin_path)error_tuple$(bin_ext)
tuple_cppout := $(tmp_path)error_tuple$(cpp_ext)

error_tuple: $(tuple_binout)
error_tuple_test: error_tuple
	$(tuple_binout)

$(tuple_binout): $(tuple_cppout)
	$(LINK) $^ $(bin_out)$@

$(tuple_cppout): $(error_root)tuple/tuple.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

