
error_binout := $(bin_path)error$(bin_ext)
error_objout := $(obj_path)errro$(obj_ext)
error_cppout := $(tmp_path)error$(cpp_ext)


error: $(error_binout)
error_test: error
	$(error_binout) /tmp/xyz

error_cflags := $(CFLAGS) $(INC) -I$(root)utils

$(error_binout): $(error_cppout)
	$(LINK) $(LFLAGS) $^ $(bin_out)$@

$(error_cppout): $(src_path)e.c
	$(CPP) $(error_cflags) $^ > $@ 
