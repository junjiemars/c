#
# ./configure --without-debug --has-regexp
#

regexp: regexp_pcre															\
        regexp_os
regexp_test: regexp_pcre_test										\
             regexp_os_test

regexp_prefix := regexp
INC += -I$(regexp_root)

ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(cflags_sanitize)
endif

# pcre
pcre_cflags := $(shell pkg-config --cflags libpcre 2>/dev/null)
pcre_libs := $(shell pkg-config --libs libpcre 2>/dev/null)

regexp_pcre_binout := $(bin_path)$(regexp_prefix)_pcre$(bin_ext)

ifneq ($(pcre_cflags),)
regexp_pcre: $(regexp_pcre_binout)
regexp_pcre_test: regexp_pcre
	$(regexp_pcre_binout) "ca*ar" "caaar"
	$(regexp_pcre_binout) "ca*ar" "Acaaa"
else
regexp_pcre:
	@echo "skipped, pcre library no found"
regexp_pcre_test: regexp_pcre
endif # end of pcre

$(regexp_pcre_binout): $(regexp_root)pcre/a.c
	$(CC) $(CFLAGS) $(pcre_cflags) $(INC) $^ $(bin_out)$@ $(LIBS) $(pcre_libs)

# os
regexp_os_binout := $(bin_path)$(regexp_prefix)_os$(bin_ext)

ifneq ($(NM_SYSTEM),WinNT)
regexp_os: $(regexp_os_binout)
regexp_os_test: regexp_os
	$(regexp_os_binout)
endif # end of Linux or Darwin

ifeq ($(NM_SYSTEM),WinNT)
regexp_os:
	@echo "skipped, no builtin support in msvc on WinNT"
regexp_os_test: regexp_os
endif # end of WinNT

$(regexp_os_binout): $(regexp_root)os/l.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
