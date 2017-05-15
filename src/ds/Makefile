
ds: list
ds_test: list_test

INC += -I$(src_path)

list_binout := $(bin_path)list$(bin_ext)
list_inc := $(INC) -I$(src_path)/list
list: $(list_binout)
list_test: list
	$(list_binout)
$(list_binout): $(src_path)list/test.c $(src_path)list/list.c
	$(CC) $(CFLAGS) $(list_inc) $^ $(bin_out)$@
