#
# ./configure --has-limit
#

ifeq ($(CC_NAME), msvc)
limit:
	@echo "#skip ..."
limit_test: limit
	@echo "#skip ..."
else

limit: limit_posix

limit_test: limit_posix_test

endif

# limit env
limit_prefix := limit
INC += $(nm_inc_opt)$(limit_root) $(nm_inc_opt)$(root)/posix


# posix
limit_posix_binout := $(bin_path)/$(limit_prefix)_posix$(bin_ext)

limit_posix: $(limit_posix_binout)
limit_posix_test: limit_posix
	-$(limit_posix_binout)

$(limit_posix_binout): $(limit_root)/posix.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
