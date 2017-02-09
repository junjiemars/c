
scope_binout := $(bin_path)scope$(bin_ext)

scope_cflags = $(CFLAGS)

ifeq ($(CC_NAME), msvc)
	scope_cflags += -Wv:18
endif

scope: $(scope_binout)
scope_test: scope
	$(scope_binout)

$(scope_binout): $(src_path)scope.c
	$(CC) $(scope_cflags) $(INC) $^ $(bin_out)$@
