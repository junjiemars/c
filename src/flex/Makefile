#
# ./configure --has-flex -Wno-unused-function
# make --keep-going --no-builtin-rules --debug=b clean test
#

flex_prefix := flex
INC += -I$(flex_root)


flex: flex_basic																\
      flex_c

flex_test: flex_basic_test											\
           flex_c_test

ifeq (Linux, $(NM_SYSTEM))
CFLAGS += -D_POSIX_C_SOURCE=200809L
LDLIBS += -lfl
endif # end of Linux

ifeq (Darwin, $(NM_SYSTEM))
LDLIBS += -ll
endif # end of Darwin


# basic
flex_basic_binout := $(bin_path)/$(flex_prefix)_basic$(bin_ext)
flex_basic_lexout := $(tmp_path)/b_lex.c

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
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $^ $(bin_out)$@ $(LDLIBS)

$(flex_basic_lexout): $(flex_root)/basic/b.lex
	flex -o $@ $^

# c
flex_c_binout := $(bin_path)/$(flex_prefix)_c$(bin_ext)
flex_c_lexout := $(tmp_path)/c_lex.c

ifeq (YES, $(has_flex))
flex_c: $(flex_c_binout)
else
flex_c:
	@echo "#skip flex_test, missing flex."
endif # end of has_flex

flex_c_test: flex_c
	$(flex_c_binout) $(flex_root)/c/c.c

$(flex_c_binout): $(flex_c_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $^ $(bin_out)$@ $(LDLIBS)

$(flex_c_lexout): $(flex_root)/c/c.lex
	flex -o $@ $^


.PHONY: flex_basic flex_basic_test							\
        flex_c flex_c_test

#eof
