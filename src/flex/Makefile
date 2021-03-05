#
# ./configure --has-flex -Wno-unused-function
#

flex_prefix := flex
INC += -I$(flex_root)
LDLIBS += -ll

ifeq (WinNT, $(NM_SYSTEM))
flex:
	@echo "#skip flex_test ..."
flex_test: flex_basic_test
else
flex: flex_basic
flex_test: flex_basic_test
endif


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
