#
# ./configure --without-debug --has-os
#

os: os_exec																			\
    os_msq
os_test: os_exec_test														\
         os_msq_test

os_prefix := os
INC += -I$(os_root)

ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(cflags_sanitize)
endif

# exec
os_exec_binout := $(bin_path)$(os_prefix)_exec$(bin_ext)

os_exec: $(os_exec_binout)
ifeq ($(NM_SYSTEM),WinNT)
os_exec_test: os_exec
	$(os_exec_binout) "dir" "%userprofile%"
else
os_exec_test: os_exec
	$(os_exec_binout) "/bin/ls" "~/"
endif # end of WinNT

$(os_exec_binout): $(os_root)exec/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# msq
os_msq_binout := $(bin_path)$(os_prefix)_msq$(bin_ext)

ifeq ($(NM_SYSTEM), Linux)
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

$(os_msq_binout): $(os_root)msq/q.c
	$(CC) $(CFLAGS) $(msq_cflags) $(INC) $^ $(bin_out)$@


# eof
