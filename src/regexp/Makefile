#
# ./configure --without-debug --has-regexp
#

regexp: regexp_pcre															\
        regexp_os
regexp_test: regexp_pcre_test										\
             regexp_os_test

regexp_prefix := regexp
INC += -I$(regexp_root) -I$(root)

ifeq ($(CC_NAME),msvc)
	getopt_c := $(root)posix/getopt.c
endif # end of msvc


ifeq ($(NM_SYSTEM),Linux)
	CFLAGS += -D_GNU_SOURCE
endif # end of Linux

ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(cflags_sanitize)
endif # end of sanitize

# pcre
has_pcre := $(shell pkg-config --exists libpcre && echo "YES")
ifeq ($(has_pcre),YES)
	pcre_cflags := $(shell pkg-config --cflags libpcre 2>/dev/null)
	pcre_libs := $(shell pkg-config --libs libpcre 2>/dev/null)
endif # end of has_pcre

ifeq ($(has_pcre),YES)
regexp_pcre: $(regexp_pcre_binout)
regexp_pcre_test: regexp_pcre
	$(regexp_pcre_binout) -h
	$(regexp_pcre_binout) -pca*r -scaaar
	$(regexp_pcre_binout) -pcaa*r -scr
else
regexp_pcre:
	@echo "skipped, pcre library no found"
regexp_pcre_test: regexp_pcre
endif # end of has_pcre

$(regexp_pcre_binout): $(regexp_root)pcre/a.c  $(getopt_c)
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
