# -*- mode:makefile-gmake -*-
#
# ./configure --has-iconv
#
#

ifneq ($(has_iconv),)
iconv: iconv_basic															\
       iconv_file

iconv_test: iconv_basic_test										\
            iconv_file_test

else
iconv:
	@echo "#skip ..."
iconv_test:
	@echo "#skip ..."

endif														# has_iconv

# env
iconv_prefix := iconv

INC += $(nm_inc_opt)$(iconv_root) $(nm_inc_opt)$(root)/posix
LDLIBS += $(has_iconv)

ifeq ($(_MEMORY_),1)
	CFLAGS += $(f_sanitize)
endif



# basic
iconv_basic_binout := $(bin_path)/$(iconv_prefix)_basic$(bin_ext)

iconv_basic: $(iconv_basic_binout)
iconv_basic_test: iconv_basic
	$(iconv_basic_binout)

$(iconv_basic_binout): $(iconv_root)/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)


# file
iconv_file_binout := $(bin_path)/$(iconv_prefix)_file$(bin_ext)
iconv_file_out := $(tmp_path)/gb18030.file

iconv_file: $(iconv_file_binout)
iconv_file_test: iconv_file
	$(iconv_file_binout) $(iconv_file_out) $(iconv_root)/u8.in

$(iconv_file_binout): $(iconv_root)/f.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)

# eof
