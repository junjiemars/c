
fn_binout := $(bin_path)fn$(bin_ext)

fn: $(fn_binout)
fn_test: fn
	$(fn_binout)

$(fn_binout): $(src_path)f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
