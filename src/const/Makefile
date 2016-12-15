
# ./configure --has-const --without-warn

const_binout := $(bin_path)const$(bin_ext)

const: $(const_binout)

$(const_binout): $(src_path)const.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@

const_test: const
	$(const_binout)
