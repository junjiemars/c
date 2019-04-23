# ./configure --without-debug --has-lang

signal: basic \
				list \
				fork \

signal_test: basic_test \
						 list_test \
						 fork_test

signal_prefix := signal
INC += -I$(signal_root) -I$(root)posix

ifeq ($(NM_SYSTEM), Linux)
CFLAGS += $(nm_def_opt)_BSD_SOURCE
endif

# basic
basic_binout := $(bin_path)$(signal_prefix)_basic$(bin_ext)

basic: $(basic_binout)
basic_test: basic
	$(basic_binout)

$(basic_binout): $(signal_root)basic/sig.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# list
list_binout := $(bin_path)$(signal_prefix)_list$(bin_ext)

list: $(list_binout)
list_test: list
	$(list_binout)

$(list_binout): $(signal_root)list/list-sig.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# fork
fork_binout := $(bin_path)$(signal_prefix)_fork$(bin_ext)

fork: $(fork_binout)
fork_test: fork
	$(fork_binout)

$(fork_binout): $(signal_root)fork/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
