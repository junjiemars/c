# src/unicode

unicode: utf8
unicode_test: utf8_test

unicode_prefix := unicode
INC += -I$(unicode_root)

# utf8
utf8_binout := $(bin_path)$(unicode_prefix)_utf8$(bin_ext)
utf8_cppout := $(tmp_path)$(unicode_prefix)_utf8$(cpp_ext)

utf8: $(utf8_binout)
utf8_test: utf8
	$(utf8_binout)

$(utf8_binout): $(utf8_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(utf8_cppout): $(unicode_root)utf8/utf8.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

