# -*- mode:makefile-gmake -*-
#
# ./configure --has-flex -Wno-unused-function
# make --keep-going --no-builtin-rules --debug=b clean test
#


flex: flex_basic                                \
      flex_c                                    \
      flex_calc

flex_test: flex_basic_test                      \
           flex_calc_test                       \
           flex_calc_test



# env
flex_prefix := flex

INC += $(nm_inc_opt)$(flex_root) $(nm_inc_opt)$(root)/posix
LDLIBS += -lfl

ifeq (Linux, $(NM_SYSTEM))
CFLAGS += -D_POSIX_C_SOURCE=200809L
endif # end of Linux

has_flex_bison := NO
ifeq (YES, $(has_flex))
ifeq (YES, $(has_bison))
has_flex_bison := YES
endif
endif



# basic
flex_basic_binout := $(bin_path)/$(flex_prefix)_basic$(bin_ext)
flex_basic_lexout := $(tmp_path)/b_lex.yy.c

ifeq (YES, $(has_flex))
flex_basic: $(flex_basic_binout)
flex_basic_test: flex_basic
	$(flex_basic_binout) $(flex_root)/basic/b.in
else
flex_basic:
	@echo "#skip flex_test, missing flex."
flex_basic_test: flex_basic
endif # end of has_flex

$(flex_basic_binout): $(flex_basic_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^ $(LDLIBS)

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
	@echo "#skip flex_test, missing flex."
flex_c_test: flex_c
endif # end of has_flex

$(flex_c_binout): $(flex_c_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^ $(LDLIBS)

$(flex_c_lexout): $(flex_root)/c/c.lex
	flex -o $@ $^


# calc
flex_calc_binout := $(bin_path)/$(flex_prefix)_calc$(bin_ext)
flex_calc_lexout := $(tmp_path)/calc.yy.c
flex_calc_yout := $(tmp_path)/calc.tab.c

ifeq (YES, $(has_flex_bison))
flex_calc: $(flex_calc_binout)
flex_calc_test: flex_calc
	printf "1 + 2\n" | $(flex_calc_binout)
else
flex_calc:
	@echo "#skip $@, missing flex/bison."
flex_calc_test: flex_calc
endif # end of has_flex

$(flex_calc_binout): $(flex_calc_lexout) $(flex_calc_yout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $(bin_out)$@ $^ $(LDFLAGS) -lfl

$(flex_calc_lexout): $(flex_root)/calc/calc.lex
	flex -o $@ $^
$(flex_calc_yout): $(flex_root)/calc/calc.y
	bison -d -b $(tmp_path)/calc $^



.PHONY: flex_basic flex_basic_test							\
        flex_c flex_c_test

#eof
