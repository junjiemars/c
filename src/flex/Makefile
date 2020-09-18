#
# ./configure --has-flex
#

flex_prefix := flex
INC += -I$(flex_root)
LDLIBS += -ll

flex: flex_basic

flex_test: flex_basic


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
