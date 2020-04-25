regexp: pcre

regexp_test: pcre_test

regexp_prefix := regexp

INC += -I$(regexp_root)


# pcre
pcre_cflags := $(CFLAGS) $(shell pkg-config --cflags libpcre)
pcre_libs := $(LIBS) $(shell pkg-config --libs libpcre)

pcre_test: pcre_basic_test
pcre_basic_binout := $(bin_path)$(regexp_prefix)_pcre_basic$(bin_ext)

pcre_basic: $(pcre_basic_binout)
pcre_basic_test: pcre_basic
	$(pcre_basic_binout) "ca*ar" "caaar"
	$(pcre_basic_binout) "ca*ar" "Acaaa"

$(pcre_basic_binout): $(regexp_root)pcre/a.c
	$(CC) $(pcre_cflags) $(INC) $^ $(bin_out)$@ $(pcre_libs)


