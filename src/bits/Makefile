
bits_binout := $(bin_path)bits$(bin_ext)

bits: $(bits_binout)

bits_lflags += $(LFLAGS) $(INC) 

$(bits_binout): $(src_path)bits.c
	$(LINK) $^ $(bin_out)$@  $(bits_lflags)

bits_test: bits
	$(bits_binout)

