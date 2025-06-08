#
# ./configure --without-debug --has-regexp
#

regexp: regexp_os \
        regexp_pcre

regexp_test: regexp_os_test \
             regexp_pcre_test



# env
regexp_prefix := regexp

INC += $(nm_inc_opt)$(regexp_root)/ $(nm_inc_opt)$(root) $(nm_inc_opt)$(root)/posix

ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif # end of msvc


ifeq ($(NM_SYSTEM),Linux)
	# CFLAGS += -D_GNU_SOURCE
	CFLAGS += -D_POSIX_C_SOURCE=200809L
endif # end of Linux


ifeq ($(_MEMORY_),1)
ifeq ($(has_sanitize),YES)
CFLAGS += $(cflags_sanitize)
endif # end of has_sanitize
endif # end of _MEMORY_



# os
regexp_os_binout := $(bin_path)/$(regexp_prefix)_os$(bin_ext)

ifeq ($(NM_SYSTEM),WinNT)
regexp_os:
	@echo "# skip, no builtin support in msvc on WinNT"
regexp_os_test: regexp_os
else
regexp_os: $(regexp_os_binout)
regexp_os_test: regexp_os
	$(regexp_os_binout)
endif # end of WinNT

$(regexp_os_binout): $(regexp_root)/os/o1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# pcre
regexp_pcre_binout := $(bin_path)/$(regexp_prefix)_pcre$(bin_ext)

ifeq (YES, $(has_libpcre))
regexp_pcre: $(regexp_pcre_binout)
regexp_pcre_test: regexp_pcre
	$(regexp_pcre_binout) -h
	$(regexp_pcre_binout) -pca*r -scaaar
	$(regexp_pcre_binout) -pcaa*r -scr
else
regexp_pcre:
	@echo "#skip, pcre library no found"
regexp_pcre_test: regexp_pcre
endif # end of has_libpcre

$(regexp_pcre_binout): $(regexp_root)/pcre/a.c $(getopt_c)
	$(CC) $(CFLAGS) $(pcre_cflags) $(INC) $^ $(bin_out)$@ $(LIBS) $(pcre_ldlibs)

# eof
