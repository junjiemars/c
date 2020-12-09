#
# ./configure --without-debug --has-os
#

os: os_msq
os_test: os_msq_test

os_prefix := os
INC += -I$(os_root)

ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(cflags_sanitize)
endif

# msq
os_msq_binout := $(bin_path)$(os_prefix)_msq$(bin_ext)

ifeq ($(NM_SYSTEM), Linux)
os_msq: $(os_msq_binout)
os_msq_test: os_msq
	$(os_msq_binout) -s
	$(os_msq_binout) -r
else
os_msq: 
os_msq_test: os_msq
	@echo "#skip os_msq_test ..."
endif

$(os_msq_binout): $(os_root)msq/m.c
	$(CC) $(CFLAGS) $(msq_cflags) $(INC) $^ $(bin_out)$@


# eof
