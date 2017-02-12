
fibo_binout := $(bin_path)fibo$(bin_ext)

fibo_cflags := $(CFLAGS) $(INC) -I$(src_path)

fibo: $(fibo_binout)
fibo_test: fibo
	$(fibo_binout)
	$(fibo_binout) --static
	$(fibo_binout) --tail

$(fibo_binout): $(src_path)fibo.c
	$(CC) $(fibo_cflags) $^ $(bin_out)$@
