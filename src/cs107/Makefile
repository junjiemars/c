#
# ./configure --has-cs107
#


cs107: cs107_0
cs107_test: cs107_0_test


# env
cs107_prefix := cs107

INC += $(nm_inc_opt)$(cs107_root)

ifeq ($(NM_SYSTEM), WinNT)
	INC += $(nm_inc_opt)$(root)/posix
	getopt_c := $(root)/posix/getopt.c
endif

ifeq ($(NM_SYSTEM), Linux)
	CFLAGS += -D_POSIX_SOURCE -D_GNU_SOURCE
endif

ifeq ($(_MEMORY_), 1)
	CFLAGS += $(f_sanitize)
endif # end of _MEMORY_


# 0
cs107_0_binout := $(bin_path)/$(cs107_prefix)_0$(bin_ext)

cs107_0: $(cs107_0_binout)
cs107_0_test: cs107_0
	$(cs107_0_binout) 2

$(cs107_0_binout): $(cs107_root)/0/01-ruth-aaron/ruth-aaron-numbers.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(stdmath_lib)


# eof
