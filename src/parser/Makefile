parser: recursive_descent \
				cdecl \


parser_test: recursive_descent_test
						 cdecl_test


parser_prefix := parser
INC += -I$(parser_root)

# recursive descent
rdp_binout := $(bin_path)$(parser_prefix)_rdp$(bin_ext)

recursive_descent: $(rdp_binout)
recursive_descent_test: recursive_descent
	$(rdp_binout)

$(rdp_binout): $(parser_root)recursive_descent/rdp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# cdecl
cdecl_binout := $(bin_path)$(parser_prefix)_cdecl$(bin_ext)

cdecl: $(cdecl_binout)
cdecl_test: cdecl
	$(cdecl_binout)

$(cdecl_binout): $(parser_root)cdecl/c1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
