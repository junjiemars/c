# ./configure --has-curl

curl: curl_basic
curl_test: curl_basic_test


curl_prefix := curl

INC += -I$(curl_root)

curl_inc = $(INC) $(shell curl-config --cflags)
curl_ldflags = $(shell curl-config --libs)

# basic
curl_basic_binout := $(bin_path)$(curl_prefix)_basic$(bin_ext)

curl_basic: $(curl_basic_binout)
curl_basic_test: curl_basic
	$(curl_basic_binout)

$(curl_basic_binout): $(curl_root)b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(curl_ldflags)

