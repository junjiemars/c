# src/unicode

unicode: mb \
				 utf8

unicode_test: mb_test \
							utf8_test

unicode_prefix := unicode
INC += -I$(unicode_root)

# utf8
utf8_binout := $(bin_path)$(unicode_prefix)_utf8$(bin_ext)

utf8: $(utf8_binout)
utf8_test: utf8
	$(utf8_binout)

$(utf8_binout): $(unicode_root)utf8/utf8.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# mb
mb_binout := $(bin_path)$(unicode_prefix)_mb$(bin_ext)

mb: $(mb_binout)
mb_test: mb
	$(mb_binout)

$(mb_binout): $(unicode_root)mb/mb.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
