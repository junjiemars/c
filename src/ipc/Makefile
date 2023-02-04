#
# ./configure --has-ipc
#
#

ifeq ($(NM_SYSTEM),WinNT)
ipc:
	@echo "#skip ..."
ipc_test:
	@echo "#skip ..."
else

ipc: ipc_access

ipc_test: ipc_access_test

endif


# env
ipc_prefix := ipc
INC += $(nm_inc_opt)$(ipc_root) $(nm_inc_opt)$(root)/posix

ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(f_sanitize)
endif

stat := stat
ifeq ($(NM_SYSTEM),Darwin)
stat := stat -x
endif



# access
ipc_access_open_binout := $(bin_path)/$(ipc_prefix)_access_open$(bin_ext)
ipc_access_at_binout := $(bin_path)/$(ipc_prefix)_access_at$(bin_ext)

ipc_access_open_file := $(tmp_path)/$(ipc_prefix)_access_open_file
ipc_access_open_link := $(tmp_path)/$(ipc_prefix)_access_open_link

ipc_access: $(ipc_access_open_binout)             \
           $(ipc_access_at_binout)
ipc_access_test: ipc_access_open_test             \
                ipc_access_at_test

ipc_access_open_test: $(ipc_access_open_binout)   \
                     $(ipc_access_open_file)     \
                     $(ipc_access_open_link)
	ls -lh $(shell which passwd)
	$< $(ipc_access_open_file)
	# sudo chown root:root $(ipc_access_open_file)
	# sudo chown root $(ipc_access_open_binout) && sudo chmod u+s $<
	# $< $(ipc_access_open_file)

ipc_access_at_test: $(ipc_access_at_binout)       \
                   $(ipc_access_open_file)       \
                   $(ipc_access_open_link)
	ls -lh $(shell which passwd)
	$< $(ipc_access_open_file)

$(ipc_access_open_file):
	echo "#!/bin/sh\necho abc" > $@
	chmod 400 $@
	ls -lh $@

$(ipc_access_open_link): $(ipc_access_open_file)
	ln -s $(CURDIR)/$< $@

$(ipc_access_open_binout): $(ipc_root)/access/a.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(ipc_access_at_binout): $(ipc_root)/access/aat.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
