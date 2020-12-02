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

