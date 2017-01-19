
net: addr
net_test: addr_test

INC += -I$(src_path)
LFLAGS += -lsocket -lnsl

addr_binout := $(bin_path)addr$(bin_ext)
addr: $(addr_binout)
$(addr_binout): $(src_path)addr/addr.c
	$(CC) $(INC) $(LFLAGS) $^ $(bin_out)$@
addr_test: addr
	$(addr_binout)

