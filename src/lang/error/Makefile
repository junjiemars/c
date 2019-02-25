
INC += -I$(error_root)

error: basic \
			 tuple

error_test: basic_test \
						tuple_test

# basic
basic_binout := $(bin_path)error_basic$(bin_ext)

basic: $(basic_binout)
basic_test: basic
	$(basic_binout) $(CURDIR)/Makefilex
	$(basic_binout) $(CURDIR)/Makefile

$(basic_binout): $(error_root)/basic/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# tuple
tuple_binout := $(bin_path)error_tuple$(bin_ext)
tuple_cppout := $(tmp_path)error_tuple$(cpp_ext)

tuple: $(tuple_binout)
tuple_test: tuple
	$(tuple_binout)

$(tuple_binout): $(tuple_cppout)
	$(LINK) $^ $(bin_out)$@

$(tuple_cppout): $(error_root)tuple/tuple.c
	$(CPP) $(CFLAGS) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

