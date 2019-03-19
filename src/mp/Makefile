mp: basic

mp_test: basic_test

mp_prefix := mp

INC += -I$(mp_root)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif


# basic I/O
basic_binout := $(bin_path)$(mp_prefix)_basic$(bin_ext)

basic: $(basic_binout)
basic_test: basic
	$(basic_binout)

$(basic_binout): $(mp_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

