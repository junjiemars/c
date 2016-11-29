
utf8_binout := $(bin_path)utf8$(bin_ext)

utf8: $(utf8_binout)

$(utf8_binout): $(src_path)utf8.c
	$(LINK) $(LFLAGS) $(INC) $^ $(bin_out)$@

utf8_test: utf8
	$(utf8_binout)

