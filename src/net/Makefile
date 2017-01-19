
net: addr
net_test: addr_test

INC += -I$(src_path)

addr_binout := $(bin_path)addr$(bin_ext)
addr: $(addr_binout)
$(addr_binout): $(src_path)addr/addr.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
addr_test: addr
	$(addr_binout)

