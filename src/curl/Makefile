#
# ./configure --has-curl
#

curl_prefix := curl
INC += -I$(curl_root)

curl: curl_basic																\
      curl_write																\
      curl_callback
curl_test: curl_basic_test											\
           curl_write_test											\
           curl_callback_test


CFLAGS += $(shell pkg-config --cflags libcurl)
LDLIBS += $(shell pkg-config --libs libcurl)

# basic
curl_basic_binout := $(bin_path)$(curl_prefix)_basic$(bin_ext)

curl_basic: $(curl_basic_binout)
curl_basic_test: curl_basic
	$(curl_basic_binout) 2>&1 > $(CURDIR)/$(tmp_path)$(curl_prefix)_basic_stdout.html

$(curl_basic_binout): $(curl_root)b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)

# write
curl_write_binout := $(bin_path)$(curl_prefix)_write$(bin_ext)

curl_write: $(curl_write_binout)
curl_write_test: curl_write
	$(curl_write_binout) $(CURDIR)/$(tmp_path)$(curl_prefix)_write.html

$(curl_write_binout): $(curl_root)w.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)

# callback
curl_callback_binout := $(bin_path)$(curl_prefix)_callback$(bin_ext)

curl_callback: $(curl_callback_binout)
curl_callback_test: curl_callback
	$(curl_callback_binout) $(CURDIR)/$(tmp_path)$(curl_prefix)_callback.html

$(curl_callback_binout): $(curl_root)callback.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)
