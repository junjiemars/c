#
# ./configure --without-debug --has-os
#

os: os_brk																			\
    os_echo																			\
    os_exec																			\
    os_msq																			\
    os_tcpwrapper
os_test: os_brk_test														\
         os_echo_test														\
         os_exec_test														\
         os_msq_test														\
         os_tcpwrapper_test


os_prefix := os
INC += -I$(os_root) -I$(root)

ifeq (msvc, $(CC_NAME))
	getopt_c := $(root)/posix/getopt.c
endif # msvc

ifeq (1, $(_MEMORY_))
	CFLAGS += $(cflags_sanitize)
endif # _MEMORY_


# brk
os_brk_binout := $(bin_path)/$(os_prefix)_brk$(bin_ext)

ifeq (YES, $(has_brk))
os_brk: $(os_brk_binout)
os_brk_test: os_brk
	$(os_brk_binout)
else
os_brk:
	@echo "#skip os_brk_test ..."
os_brk_test: os_brk
endif														# LINUX


$(os_brk_binout): $(os_root)/brk/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# echo
os_echo_binout := $(bin_path)/$(os_prefix)_echo$(bin_ext)

os_echo: $(os_echo_binout)
os_echo_test: os_echo
	$(os_echo_binout) -h
	$(os_echo_binout) -n abc
	$(os_echo_binout) abc 123 "xxx zzz"

$(os_echo_binout): $(os_root)/echo/e.c $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# exec
os_exec_binout := $(bin_path)/$(os_prefix)_exec$(bin_ext)

os_exec: $(os_exec_binout)
os_exec_test: os_exec
	$(os_exec_binout) "/bin/ls" "-lh" "."

$(os_exec_binout): $(os_root)/exec/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# msq
os_msq_binout := $(bin_path)/$(os_prefix)_msq$(bin_ext)

ifeq (Linux, $(NM_SYSTEM))
CFLAGS += -D_GNU_SOURCE
os_msq: $(os_msq_binout)
os_msq_test: os_msq
	$(os_msq_binout) -s abcd ABCDEFGHIJKLMN
	$(os_msq_binout) -r
	$(os_msq_binout) -s abcd
	$(os_msq_binout) -r -t 2
	$(os_msq_binout) -r -t 1
else
os_msq: 
os_msq_test: os_msq
	@echo "#skip os_msq_test ..."
endif

$(os_msq_binout): $(os_root)/msq/q.c
	$(CC) $(CFLAGS) $(msq_cflags) $(INC) $^ $(bin_out)$@


# tcp wrapper
os_tcpwrapper_binout := $(bin_path)/$(os_prefix)_tcpwrapper$(bin_ext)

ifeq (YES, $(has_tcpwrapper))
os_tcpwrapper: $(os_tcpwrapper_binout)
os_tcpwrapper_test: os_tcpwrapper
	$(os_tcpwrapper_binout)
else
os_tcpwrapper:
	@echo "#skip os_tcpwrapper_test ..."
os_tcpwrapper_test: os_tcpwrapper
endif

$(os_tcpwrapper_binout): $(os_root)/tcpwrapper/tw.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ldlibs_tcpwrapper)


# eof
