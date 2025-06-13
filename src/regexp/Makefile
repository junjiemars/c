#
# ./configure --without-debug --has-regexp
#

regexp: regexp_os \
        regexp_pcre

regexp_test: regexp_os_test \
             regexp_pcre_test



# env
regexp_prefix := regexp
posix_root ?= $(POSIX_ROOT)

INC += $(nm_inc_opt)$(regexp_root) $(nm_inc_opt)$(posix_root)

ifeq ($(use_sanitize),yes)
CFLAGS += $(f_sanitize)
endif

ifeq ($(CC_NAME),msvc)
posix_getopt_c := $(posix_root)/getopt.c
endif # end of msvc

ifeq ($(NM_SYSTEM),Linux)
	# CFLAGS += -D_GNU_SOURCE
	CFLAGS += -D_POSIX_C_SOURCE=200809L
endif # end of Linux



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
	$(regexp_os_binout) -p'(a*?)*((?i)bb)((?#comment)c{2,})' -s'aaaBBcc'
endif # end of WinNT

$(regexp_os_binout): $(regexp_root)/os/o1.c $(posix_getopt_c)
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

$(regexp_pcre_binout): $(regexp_root)/pcre/a.c $(posix_getopt_c)
	$(CC) $(CFLAGS) $(pcre_cflags) $(INC) $^ $(bin_out)$@ $(LIBS) $(pcre_ldlibs)

# eof
