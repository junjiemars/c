# ./configure --without-debug --has-lang

signal: basic
signal_test: basic_test

signal_prefix := signal
INC += -I$(signal_root)


# basic
basic_binout := $(bin_path)$(signal_prefix)_basic$(bin_ext)

basic: $(basic_binout)
basic_test: basic
	$(basic_binout)

$(basic_binout): $(signal_root)basic/sig.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
