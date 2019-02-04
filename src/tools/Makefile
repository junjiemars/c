tools: t_nm

tools_test: t_nm_test

INC += -I$(tools_root)
tools_prefix := tools

# nm
nm_binout := $(bin_path)$(tools_prefix)_nm$(bin_ext)

t_nm: $(nm_binout)
t_nm_test: t_nm
	$(nm_binout)

$(nm_binout): $(tools_root)nm/n1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
