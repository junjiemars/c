#
# ./configure --has-daemon
#
#

ifeq ($(NM_SYSTEM), WinNT)
daemon:
	@echo "#skip ..."
daemon_test:
	@echo "#skip ..."
else

daemon: daemon_bone
daemon_test: daemon_bone_test

endif


# env
daemon_prefix := daemon
INC += $(nm_inc_opt)$(daemon_root) $(nm_inc_opt)$(root)/posix

ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(f_sanitize)
endif


# bone
daemon_bone_binout := $(bin_path)/$(daemon_prefix)_bone$(bin_ext)

daemon_bone: $(daemon_bone_binout)
daemon_bone_test: daemon_bone
	$(daemon_bone_binout)

$(daemon_bone_binout): $(daemon_root)/bone/b1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
