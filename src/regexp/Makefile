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
pcre_cflags := $(CFLAGS) $(shell pkg-config --cflags libpcre)
pcre_libs := $(LIBS) $(shell pkg-config --libs libpcre)

regexp_pcre: pcre_basic
regexp_pcre_test: pcre_basic_test

pcre_basic_binout := $(bin_path)$(regexp_prefix)_pcre_basic$(bin_ext)

pcre_basic: $(pcre_basic_binout)
pcre_basic_test: pcre_basic
	$(pcre_basic_binout) "ca*ar" "caaar"
	$(pcre_basic_binout) "ca*ar" "Acaaa"

$(pcre_basic_binout): $(regexp_root)pcre/a.c
	$(CC) $(pcre_cflags) $(INC) $^ $(bin_out)$@ $(pcre_libs)

# os
regexp_os: os_basic
regexp_os_test: os_basic_test

os_basic_binout := $(bin_path)$(regexp_prefix)_os_basic$(bin_ext)

os_basic: $(os_basic_binout)
os_basic_test: os_basic
	$(os_basic_binout) "ca*ar" "caaar"
	$(os_basic_binout) "ca*ar" "Acaaa"

ifeq ($(NM_SYSTEM),Linux)
$(os_basic_binout): $(regexp_root)os/l.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
else
$(os_basic_binout):
endif
