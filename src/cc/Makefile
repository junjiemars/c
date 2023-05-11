#
# ./configure --has-cc --with-error=no
#

cc: cc_calc                                     \
	  cc_cdecl                                    \
    cc_recursive_descent                        \
    cc_tutor


cc_test: cc_calc_test                           \
         cc_cdecl_test                          \
         cc_recursive_descent_test              \
         cc_tutor_test


# env
cc_prefix := cc
INC += $(nm_inc_opt)$(cc_root) $(nm_inc_opt)$(root)/posix



# calc
cc_calc_raw_binout := $(bin_path)/$(cc_prefix)_calc_raw$(bin_ext)
cc_calc_bison_binout := $(bin_path)/$(cc_prefix)_calc_bison$(bin_ext)
cc_calc_bison_c_out := $(tmp_path)/$(cc_prefix)_calc_b1.c
cc_calc_bison_h_out := $(inc_path)/$(cc_prefix)_calc_b1.h

cc_calc: $(cc_calc_raw_binout)                  \
         $(cc_calc_bison_binout)
cc_calc_test: cc_calc_raw_test                  \
              cc_calc_bison_test

cc_calc_raw_test: $(cc_calc_raw_binout)
	$< "123 + 345 - 100 * 2 / 4"

cc_calc_bison_test: $(cc_calc_bison_binout)
	$< "123 + 345 - 100 * 2 / 4"

$(cc_calc_raw_binout): $(cc_root)/calc/r1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cc_calc_bison_binout): $(cc_calc_bison_c_out) \
                         $(cc_root)/calc/b1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cc_calc_bison_c_out): $(cc_root)/calc/b1.y
	bison -H$(cc_calc_bison_h_out) -o$@ $^



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
cc_rdp_binout := $(bin_path)/$(cc_prefix)_rdp$(bin_ext)

cc_recursive_descent: $(cc_rdp_binout)
cc_recursive_descent_test: cc_recursive_descent
	$(cc_rdp_binout)

$(cc_rdp_binout): $(cc_root)/recursive_descent/rdp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# tutor
cc_tutor1_binout := $(bin_path)/$(cc_prefix)_tutor1$(bin_ext)
cc_tutor1_lexout := $(cc_root)/tutor/t1_lex.yy.c
cc_tutor2_binout := $(bin_path)/$(cc_prefix)_tutor2$(bin_ext)
cc_tutor2_lexout := $(cc_root)/tutor/t2_lex.yy.c

cc_tutor: $(cc_tutor1_binout)                   \
          $(cc_tutor2_binout)

cc_tutor_test: cc_tutor1_test                   \
               cc_tutor2_test

cc_tutor1_test: $(cc_tutor1_binout)
	$< <$(cc_root)/tutor/t1.lex

cc_tutor2_test: $(cc_tutor2_binout)
	$< <$(cc_root)/tutor/t2.lex

$(cc_tutor1_binout): $(cc_tutor1_lexout)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cc_tutor1_lexout): $(cc_root)/tutor/t1.lex
	lex -o $@ $<

$(cc_tutor2_binout): $(cc_tutor2_lexout)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(cc_tutor2_lexout): $(cc_root)/tutor/t2.lex
	lex -o $@ $<



.PHONY: cc_tutor_test cc_tutor1_test

# eof
