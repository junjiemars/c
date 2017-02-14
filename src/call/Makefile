
call_binout := $(bin_path)call$(bin_ext)

call_cflags = $(CFLAGS) $(INC)

call: $(call_binout)
call_test: call
	$(call_binout) 1 2

$(call_binout): $(src_path)/call.c
	$(CC) $(call_cflags) $^ $(bin_out)$@
	
