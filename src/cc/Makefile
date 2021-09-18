#
# ./configure --has-cc
# make clean test
#

cc: cc_recursive_descent                        \
    cc_cdecl                                    \
    cc_lexer


cc_test: cc_recursive_descent_test              \
         cc_cdecl_test                          \
         cc_lexer_test


cc_prefix := cc
INC += -I$(cc_root)

# recursive descent
cc_rdp_binout := $(bin_path)$(cc_prefix)_rdp$(bin_ext)

cc_recursive_descent: $(cc_rdp_binout)
cc_recursive_descent_test: cc_recursive_descent
	$(cc_rdp_binout)

$(cc_rdp_binout): $(cc_root)/recursive_descent/rdp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# cdecl
cc_cdecl_binout := $(bin_path)$(cc_prefix)_cdecl$(bin_ext)
cc_cdecl_cppout := $(tmp_path)$(cc_prefix)_cdecl$(cpp_ext)

cc_cdecl: $(cc_cdecl_binout)
cc_cdecl_test: cc_cdecl
	$(cc_cdecl_binout) "void (*signal(int sig, void (*func)(int)))(int)"

$(cc_cdecl_binout): $(cc_cdecl_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(cc_cdecl_cppout): $(cc_root)/cdecl/c1.c
	$(CC) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# lexer
cc_lexer_binout := $(bin_path)$(cc_prefix)_lexer$(bin_ext)

cc_lexer: $(cc_lexer_binout)
cc_lexer_test: cc_lexer
	$(cc_lexer_binout) "123 + 345 - 100 * 2 / 4"

$(cc_lexer_binout): $(cc_root)/lexer/lexer.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
