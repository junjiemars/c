# -*- mode:makefile-gmake -*-
#
# ./configure --has-unicode
# make clean test
#

unicode: unicode_mb                             \
				 unicode_utf8

unicode_test: unicode_mb_test                   \
							unicode_utf8_test

# env
unicode_prefix := unicode
INC += $(nm_inc_opt)$(unicode_root) $(nm_inc_opt)$(root)/posix

ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(f_sanitize_address)
endif



# unicode_utf8
unicode_utf8_binout := $(bin_path)/$(unicode_prefix)_utf8$(bin_ext)

unicode_utf8: $(unicode_utf8_binout)
unicode_utf8_test: unicode_utf8
	$(unicode_utf8_binout)

$(unicode_utf8_binout): $(unicode_root)/utf8/utf8.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# mb
unicode_mb_binout := $(bin_path)/$(unicode_prefix)_mb$(bin_ext)

unicode_mb: $(unicode_mb_binout)
unicode_mb_test: unicode_mb
	$(unicode_mb_binout) "abc中文def"

$(unicode_mb_binout): $(unicode_root)/mb/mb.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
