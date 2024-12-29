# -*- mode:makefile-gmake -*-
#
# ./configure --has-flex -Wno-unused-function
# make --keep-going --no-builtin-rules --debug=b clean test
#


flex: flex_ast                                  \
      flex_basic                                \
      flex_c                                    \
      flex_calc                                 \
      flex_infix                                \
      flex_fn                                   \
      flex_lang                                 \
      flex_rpn                                  \
      flex_wc

flex_test: flex_ast_test                        \
           flex_basic_test                      \
           flex_c_test                          \
           flex_calc_test                       \
           flex_fn_test                         \
           flex_infix_test                      \
           flex_lang_test                       \
           flex_rpn_test                        \
           flex_wc_test



# env
flex_prefix := flex

INC += $(nm_inc_opt)$(flex_root) $(nm_inc_opt)$(root)/posix

YYDEBUG=0
ifeq ($(nm_build_opt),)
CFLAGS += $(f_sanitize)
YYDEBUG=1
endif

ifeq (Linux, $(NM_SYSTEM))
CFLAGS += -D_POSIX_C_SOURCE=200809L
endif # end of Linux

flex_lib_math := $(nm_lib_opt)m

has_flex_bison := NO
ifeq (YES, $(has_flex))
ifeq (YES, $(has_bison))
has_flex_bison := YES
endif
endif



# ast: ast on fn
flex_ast_binout := $(bin_path)/$(flex_prefix)_ast$(bin_ext)
flex_ast_yout := $(flex_root)/ast/fcalc.tab.c
flex_ast_yhtml := $(flex_root)/ast/fcalc.html
flex_ast_lout := $(flex_root)/ast/fcalc.yy.c

ifeq (YES, $(has_bison))
flex_ast: $(flex_ast_binout)
flex_ast_test: flex_ast
	printf "x=sqrt((sqrt1=PI+e+618E-2))\n sqrt1\n e\n" | $(flex_ast_binout)
else
flex_ast:
	@echo "#skip $@, missing bison."
flex_ast_test: flex_ast
	@echo "#skip $@, missing bison."
endif # end of has_bison

flex_ast_clean:
	test ! -f $(flex_ast_yout) || rm $(flex_root)/ast/fcalc.tab.*
	test ! -f $(flex_ast_yhtml) || rm $(flex_root)/ast/fcalc.{html,xml}
	test ! -f $(flex_ast_lout) || rm $(flex_ast_lout)

$(flex_ast_binout): $(flex_root)/ast/ast.c \
                    $(flex_ast_yout) \
                    $(flex_ast_lout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) -DYYDEBUG=$(YYDEBUG) \
    $(bin_out)$@ $^ $(flex_lib_math)

$(flex_ast_yout): $(flex_root)/ast/fcalc.y
	bison -d -b $(flex_root)/ast/fcalc --html $^

$(flex_ast_lout): $(flex_root)/ast/fcalc.l
	flex -o $@ $^



# basic
flex_basic_binout := $(bin_path)/$(flex_prefix)_basic$(bin_ext)
flex_basic_lexout := $(tmp_path)/b_lex.yy.c

ifeq (YES, $(has_flex))
flex_basic: $(flex_basic_binout)
flex_basic_test: flex_basic
	$(flex_basic_binout) $(flex_root)/basic/b.in
else
flex_basic:
	@echo "#skip $@, missing flex."
flex_basic_test: flex_basic
	@echo "#skip $@, missing flex."
endif # end of has_flex

$(flex_basic_binout): $(flex_basic_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^ $(ldflags_flex)

$(flex_basic_lexout): $(flex_root)/basic/b.lex
	flex -o $@ $^



# c: comment code
flex_c_binout := $(bin_path)/$(flex_prefix)_c$(bin_ext)
flex_c_lexout := $(tmp_path)/c_lex.yy.c

ifeq (YES, $(has_flex))
flex_c: $(flex_c_binout)
flex_c_test: flex_c
	$(flex_c_binout) $(flex_root)/c/c.c
else
flex_c:
	@echo "#skip $@, missing flex."
flex_c_test: flex_c
	@echo "#skip $@, missing flex."
endif # end of has_flex

$(flex_c_binout): $(flex_c_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^ $(ldflags_flex)

$(flex_c_lexout): $(flex_root)/c/c.lex
	flex -o $@ $^


# calc
flex_calc_binout := $(bin_path)/$(flex_prefix)_calc$(bin_ext)
flex_calc_lexout := $(tmp_path)/calc.yy.c
flex_calc_yout := $(tmp_path)/calc.tab.c

ifeq (YES, $(has_flex_bison))
flex_calc: $(flex_calc_binout)
flex_calc_test: flex_calc
	printf "1 + 3 * 4 / 2 + |-5\n" | $(flex_calc_binout)
else
flex_calc:
	@echo "#skip $@, missing flex/bison."
flex_calc_test: flex_calc
	@echo "#skip $@, missing flex/bison."
endif # end of has_flex

$(flex_calc_binout): $(flex_calc_lexout) $(flex_calc_yout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^ $(ldflags_flex)

$(flex_calc_lexout): $(flex_root)/calc/calc.lex
	flex -o $@ $^
$(flex_calc_yout): $(flex_root)/calc/calc.y
	bison -d -b $(tmp_path)/calc $^



# lang: on ast
flex_lang_binout := $(bin_path)/$(flex_prefix)_lang$(bin_ext)
flex_lang_ytabc := $(flex_root)/lang/ast.tab.c
flex_lang_ytabh := $(flex_root)/lang/ast.tab.h
flex_lang_yout := $(flex_lang_ytabc) $(flex_lang_ytabh)
flex_lang_yhtml := $(flex_root)/lang/ast.html
flex_lang_lout := $(flex_root)/lang/ast.yy.c

ifeq (YES, $(has_bison))
flex_lang: $(flex_lang_binout)
flex_lang_test: flex_lang
	printf "let x=sqrt((PI+e+618E-2));\n x;\n" | $(flex_lang_binout)
else
flex_lang:
	@echo "#skip $@, missing bison."
flex_lang_test: flex_lang
	@echo "#skip $@, missing bison."
endif # end of has_bison

flex_lang_clean:
	test ! -f $(flex_lang_ytabc) || rm $(flex_lang_ytabc)
	test ! -f $(flex_lang_ytabh) || rm $(flex_lang_ytabh)
	test ! -f $(flex_lang_yhtml) || rm $(flex_root)/lang/ast.{html,xml}
	test ! -f $(flex_lang_lout) || rm $(flex_lang_lout)

$(flex_lang_binout): $(flex_root)/lang/lang.c \
                     $(flex_lang_ytabc) \
                     $(flex_lang_lout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) -DYYDEBUG=$(YYDEBUG) \
    $(bin_out)$@ $^ $(flex_lib_math)

$(flex_lang_yout): $(flex_root)/lang/ast.y
	bison -d -b $(flex_root)/lang/ast --html $^

$(flex_lang_lout): $(flex_root)/lang/ast.l $(flex_lang_ytabh)
	flex -o $@ $^



# rpn: reverse polish notatition calculation
flex_rpn_binout := $(bin_path)/$(flex_prefix)_rpn$(bin_ext)
flex_rpn_yout := $(tmp_path)/rpn.tab.c

ifeq (YES, $(has_bison))
flex_rpn: $(flex_rpn_binout)
flex_rpn_test: flex_rpn
	printf "6 2.0 3 4 5 + * / ^\n" | $(flex_rpn_binout)
else
flex_rpn:
	@echo "#skip $@, missing bison."
flex_rpn_test: flex_rpn
	@echo "#skip $@, missing bison."
endif # end of has_bison

$(flex_rpn_binout): $(flex_rpn_yout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^

$(flex_rpn_yout): $(flex_root)/rpn/rpn.y
	bison -d -b $(tmp_path)/rpn $^



# infix: algebraic calculation
flex_infix_binout := $(bin_path)/$(flex_prefix)_infix$(bin_ext)
flex_infix_yout := $(tmp_path)/infix.tab.c

ifeq (YES, $(has_bison))
flex_infix: $(flex_infix_binout)
flex_infix_test: flex_infix
	printf "6 ^ (2.0 / (3 * (4 + 5))) \n" | $(flex_infix_binout)
else
flex_infix:
	@echo "#skip $@, missing bison."
flex_infix_test: flex_infix
	@echo "#skip $@, missing bison."
endif # end of has_bison

$(flex_infix_binout): $(flex_infix_yout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^

$(flex_infix_yout): $(flex_root)/infix/infix.y
	bison -d -b $(tmp_path)/infix --html $^



# fn: funcation calculation
flex_fn_binout := $(bin_path)/$(flex_prefix)_fn$(bin_ext)
flex_fn_yout := $(flex_root)/fn/fcalc.tab.c

ifeq (YES, $(has_bison))
flex_fn: $(flex_fn_binout)
flex_fn_test: flex_fn
	printf "x=sqrt(2)\n x^2 %% 4\n PI\n e\n ln(e)\n" | $(flex_fn_binout)
else
flex_fn:
	@echo "#skip $@, missing bison."
flex_fn_test: flex_fn
	@echo "#skip $@, missing bison."
endif # end of has_bison

flex_fn_clean:
	test ! -f $(flex_fn_yout) || rm $(flex_root)/fn/fcalc.tab.*

$(flex_fn_binout): $(flex_root)/fn/fn.c \
                   $(flex_fn_yout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) -DYYDEBUG=$(YYDEBUG) \
    $(bin_out)$@ $^ $(flex_lib_math)

$(flex_fn_yout): $(flex_root)/fn/fcalc.y
	bison -b $(flex_root)/fn/fcalc --html=$(flex_root)/fn/fcalc.html $^



# wc
flex_wc_binout := $(bin_path)/$(flex_prefix)_wc$(bin_ext)
flex_wc_lexout := $(tmp_path)/wc_lex.yy.c

ifeq (YES, $(has_flex))
flex_wc: $(flex_wc_binout)
flex_wc_test: flex_wc
	echo 'abc'|$(flex_wc_binout) $(flex_root)/Makefile $(flex_root)/wc/wc.lex
else
flex_wc:
	@echo "#skip $@, missing flex."
flex_wc_test: flex_wc
	@echo "#skip $@, missing flex."
endif # end of has_flex

$(flex_wc_binout): $(flex_wc_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^ $(ldflags_flex)

$(flex_wc_lexout): $(flex_root)/wc/wc.lex
	flex -o $@ $^



.PHONY: flex_basic flex_basic_test              \
        flex_c flex_c_test                      \
        flex_fn flex_fn_test flex_fn_clean

#eof
