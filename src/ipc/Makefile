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

ipc: ipc_bone

ipc_test: ipc_bone_test

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



# bone
ipc_bone_binout := $(bin_path)/$(ipc_prefix)_bone$(bin_ext)

ipc_bone: $(ipc_bone_binout)
ipc_bone_test: ipc_bone
	$(ipc_bone_binout)

$(ipc_bone_binout): $(ipc_root)/bone/b1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof