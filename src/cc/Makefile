#
# ./configure --has-cc
#

cc: cc_calc                                     \
	  cc_cdecl                                    \
    cc_recursive_descent


cc_test: cc_calc_test                           \
         cc_cdecl_test                          \
         cc_recursive_descent_test


# env
cc_prefix := cc
INC += $(nm_inc_opt)$(cc_root) $(nm_inc_opt)$(root)/posix

# calc
cc_calc_binout := $(bin_path)$(cc_prefix)_calc$(bin_ext)

cc_calc: $(cc_calc_binout)
cc_calc_test: cc_calc
	$(cc_calc_binout) "123 + 345 - 100 * 2 / 4"

$(cc_calc_binout): $(cc_root)/calc/calc.c
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

# recursive descent
cc_rdp_binout := $(bin_path)$(cc_prefix)_rdp$(bin_ext)

cc_recursive_descent: $(cc_rdp_binout)
cc_recursive_descent_test: cc_recursive_descent
	$(cc_rdp_binout)

$(cc_rdp_binout): $(cc_root)/recursive_descent/rdp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
