
error_binout := $(bin_path)error$(bin_ext)

error: $(error_binout)
error_test: error
	$(error_binout) /tmp/xyz

error_cflags := $(CFLAGS) $(INC) -I$(src_root)posix

$(error_binout): $(src_path)e.c
	$(CC) $(error_cflags) $^ $(bin_out)$@

