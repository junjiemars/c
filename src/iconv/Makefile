#
# ./configure --has-iconv
# 
#

iconv: iconv_basic

iconv_test: iconv_basic_test

iconv_prefix := iconv

INC += -I$(iconv_root)
LDLIBS += -liconv


# basic
iconv_basic_binout := $(bin_path)$(iconv_prefix)_basic$(bin_ext)

iconv_basic: $(iconv_basic_binout)
iconv_basic_test: iconv_basic
	$(iconv_basic_binout)

$(iconv_basic_binout): $(iconv_root)b.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)

# eof
