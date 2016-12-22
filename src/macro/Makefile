

macro_binout := $(bin_path)macro$(bin_ext)
macro_cppout := $(tmp_path)macro$(cpp_ext)

macro: $(macro_binout)

macro_cflags += $(CFLAGS) $(INC) -I$(src_path)

$(macro_cppout): $(src_path)macro.c
	$(CPP) $(macro_cflags) $^ > $@

$(macro_binout): $(macro_cppout)
	$(CC) $(macro_cflags) $^ $(bin_out)$@

macro_test: macro
	$(macro_binout)

