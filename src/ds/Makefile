
ds: singly_list
ds_test: singly_list_test

INC += -I$(src_path)

singly_list_binout := $(bin_path)singly_list$(bin_ext)
singly_list_inc := $(INC) -I$(src_path)/singly_list
singly_list: $(singly_list_binout)
singly_list_test: singly_list
	$(singly_list_binout)
$(singly_list_binout): $(src_path)singly_list/test.c $(src_path)singly_list/list.c
	$(CC) $(CFLAGS) $(singly_list_inc) $^ $(bin_out)$@
