#
# ./configure --has-curl
#

curl_prefix := curl
INC += -I$(curl_root)

curl: curl_easy
curl_test: curl_easy_test


CFLAGS += $(shell pkg-config --cflags libcurl)
LDLIBS += $(shell pkg-config --libs libcurl)

# easy
curl_easy_basic_binout := $(bin_path)$(curl_prefix)_easy_basic$(bin_ext)
curl_easy_write_binout := $(bin_path)$(curl_prefix)_easy_write$(bin_ext)
curl_easy_callback_binout := $(bin_path)$(curl_prefix)_easy_callback$(bin_ext)

curl_easy: $(curl_easy_basic_binout)						\
           $(curl_easy_write_binout)						\
           $(curl_easy_callback_binout)
curl_easy_test: curl_easy_basic_test						\
                curl_easy_write_test						\
                curl_easy_callback_test

curl_easy_basic_test: $(curl_easy_basic_binout)
	$(curl_easy_basic_binout) 2>&1 > $(CURDIR)/$(tmp_path)$(curl_prefix)_basic_stdout.txt
curl_easy_write_test: $(curl_easy_write_binout)
	$(curl_easy_write_binout) $(CURDIR)/$(tmp_path)$(curl_prefix)_write.html
curl_easy_callback_test: $(curl_easy_callback_binout)
	$(curl_easy_callback_binout) $(CURDIR)/$(tmp_path)$(curl_prefix)_callback.html


$(curl_easy_basic_binout): $(curl_root)easy/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)

$(curl_easy_write_binout): $(curl_root)easy/w.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)

$(curl_easy_callback_binout): $(curl_root)easy/callback.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)
