#
# ./configure --has-flex -Wno-unused-function
#

flex_prefix := flex
INC += -I$(flex_root)
LDLIBS += -ll

ifeq (WinNT, $(NM_SYSTEM))
flex:
	@echo "#skip flex_test ..."
else
flex: flex_basic																\
      flex_c
endif

flex_test: flex_basic_test											\
           flex_c_test

# basic
flex_basic_binout := $(bin_path)$(flex_prefix)_basic$(bin_ext)
flex_basic_lexout := $(tmp_path)b_lex.c

flex_basic: $(flex_basic_binout)
flex_basic_test: flex_basic
	$(flex_basic_binout) $(flex_root)basic/b.in

$(flex_basic_binout): $(flex_basic_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $^ $(bin_out)$@ $(LDLIBS)

$(flex_basic_lexout): $(flex_root)basic/b.lex
	flex -o $@ $^

# c
flex_c_binout := $(bin_path)$(flex_prefix)_c$(bin_ext)
flex_c_lexout := $(tmp_path)c_lex.c

flex_c: $(flex_c_binout)
flex_c_test: flex_c
	$(flex_c_binout) $(flex_root)c/c.c

$(flex_c_binout): $(flex_c_lexout)
	$(CC) $(CFLAGS) $(INC) $(LFLAGS) $^ $(bin_out)$@ $(LDLIBS)

$(flex_c_lexout): $(flex_root)c/c.lex
	flex -o $@ $^
