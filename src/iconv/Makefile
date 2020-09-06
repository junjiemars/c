#
# ./configure --has-iconv
# 
#

iconv: iconv_basic															\
       iconv_file

iconv_test: iconv_basic_test										\
            iconv_file_test

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


# file
iconv_file_binout := $(bin_path)$(iconv_prefix)_file$(bin_ext)

iconv_file: $(iconv_file_binout)
iconv_file_test: iconv_file
	$(iconv_file_binout) $(tmp_path)gb18030.out $(iconv_root)u8.in

$(iconv_file_binout): $(iconv_root)f.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)

# eof
