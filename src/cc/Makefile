cc: recursive_descent \
		cdecl \
		lexer


cc_test: recursive_descent_test \
				 cdecl_test \
				 lexer_test


cc_prefix := cc
INC += -I$(cc_root)

# recursive descent
rdp_binout := $(bin_path)$(cc_prefix)_rdp$(bin_ext)

recursive_descent: $(rdp_binout)
recursive_descent_test: recursive_descent
	$(rdp_binout)

$(rdp_binout): $(cc_root)recursive_descent/rdp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# cdecl
cdecl_binout := $(bin_path)$(cc_prefix)_cdecl$(bin_ext)
cdecl_cppout := $(tmp_path)$(cc_prefix)_cdecl$(cpp_ext)

cdecl: $(cdecl_binout)
cdecl_test: cdecl
	$(cdecl_binout) "char *(*x(char*, int))[3]"

$(cdecl_binout): $(cdecl_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(cdecl_cppout): $(cc_root)cdecl/c1.c
	$(CC) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# lexer
lexer_binout := $(bin_path)$(cc_prefix)_lexer$(bin_ext)

lexer: $(lexer_binout)
lexer_test: lexer
	$(lexer_binout) "123 + 345 - 100 * 2 / 4"

$(lexer_binout): $(cc_root)lexer/lexer.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
