#
# ./configure --without-debug --has-regexp
#

regexp: regexp_pcre															\
        regexp_os
regexp_test: regexp_pcre_test										\
             regexp_os_test

regexp_prefix := regexp

INC += -I$(regexp_root)


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

regexp_os: $(regexp_os_binout)
regexp_os_test: regexp_os
	$(regexp_os_binout)

$(regexp_os_binout): $(regexp_root)os/l.c
ifeq ($(NM_SYSTEM),Linux)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
endif # end of Linux
ifeq ($(NM_SYSTEM),Darwin)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
endif # end of Drawin
ifeq ($(NM_SYSTEM),WinNT)
	echo "skipped, there are no builtin support in msvc on WinNT"
endif

