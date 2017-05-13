
ds: list
ds_test: list_test

list_binout := $(bin_path)list$(bin_ext)
list_test_binout := $(bin_path)list_test$(bin_ext)
list_inc := $(INC) -I$(src_path)/list
list: $(list_binout)
list_test: $(list_test_binout)
	$(list_test_binout)
$(list_binout): $(src_path)list/main.c $(src_path)list/list.c
	$(CC) $(CFLAGS) $(list_inc) $^ $(bin_out)$@
$(list_test_binout): $(src_path)list/test.c $(src_path)list/list.c
	$(CC) $(CFLAGS) $(list_inc) $^ $(bin_out)$@
