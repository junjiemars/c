# ./configure --has-curl

curl: curl_basic																\
      curl_write
curl_test: curl_basic_test											\
           curl_write_test

curl_prefix := curl

INC += -I$(curl_root)

curl_inc = $(INC) $(shell curl-config --cflags)
curl_ldflags = $(shell curl-config --libs)

# basic
curl_basic_binout := $(bin_path)$(curl_prefix)_basic$(bin_ext)

curl_basic: $(curl_basic_binout)
curl_basic_test: curl_basic
	$(curl_basic_binout) 2>&1 > $(CURDIR)/$(tmp_path)$(curl_prefix)_basic_stdout.txt

$(curl_basic_binout): $(curl_root)b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(curl_ldflags)

# write
curl_write_binout := $(bin_path)$(curl_prefix)_write$(bin_ext)

curl_write: $(curl_write_binout)
curl_write_test: curl_write
	$(curl_write_binout) $(CURDIR)/$(tmp_path)$(curl_prefix)_write.txt

$(curl_write_binout): $(curl_root)w.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(curl_ldflags)
