#
# ./configure --has-syscall
#

ifeq ($(NM_SYSTEM),Linux)
syscall: syscall_bone

syscall_test: syscall_bone_test

else
syscall:
	@echo "#skip ..."
syscall_test: syscall
	@echo "#skip ..."
endif



syscall_prefix := syscall
INC += $(nm_inc_opt)$(syscall_root) $(nm_inc_opt)$(root)/posix




# bone
syscall_bone_binout := $(bin_path)/$(syscall_prefix)_bone$(bin_ext)

syscall_bone: $(syscall_bone_binout)
syscall_bone_test: syscall_bone
	$(syscall_bone_binout)

$(syscall_bone_binout): $(syscall_root)/bone/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
