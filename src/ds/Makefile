
ds: singly
ds_test: singly_test

INC += -I$(src_path)

singly_binout := $(bin_path)singly$(bin_ext)
singly_inc := $(INC) -I$(src_path)/singly
singly: $(singly_binout)
singly_test: singly
	$(singly_binout)
$(singly_binout): $(src_path)singly/test.c $(src_path)singly/list.c
	$(CC) $(CFLAGS) $(singly_inc) $^ $(bin_out)$@
