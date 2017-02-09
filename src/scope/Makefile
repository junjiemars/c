
scope_binout := $(bin_path)scope$(bin_ext)

scope: $(scope_binout)
scope_test: scope
	$(scope_binout)

$(scope_binout): $(src_path)scope.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
