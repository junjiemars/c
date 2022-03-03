#
# ./configure --has-limit
#

ifeq ($(CC_NAME), msvc)
limit:
	@echo "#skip ..."
limit_test: limit
	@echo "#skip ..."
else

limit: limit_int                                \
       limit_posix

limit_test: limit_int_test                      \
            limit_posix_test

endif

# limit env
limit_prefix := limit
INC += $(nm_inc_opt)$(limit_root) $(nm_inc_opt)$(root)/posix


# int
limit_int_binout := $(bin_path)/$(limit_prefix)_int$(bin_ext)
limit_int_cppout := $(tmp_path)/$(limit_prefix)_int$(cpp_ext)

limit_int: $(limit_int_binout)
limit_int_test: limit_int
	-$(limit_int_binout)

$(limit_int_binout): $(limit_int_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(limit_int_cppout): $(limit_root)/i.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# posix
limit_posix_binout := $(bin_path)/$(limit_prefix)_posix$(bin_ext)
limit_posix_cppout := $(tmp_path)/$(limit_prefix)_posix$(cpp_ext)

limit_posix: $(limit_posix_binout)
limit_posix_test: limit_posix
	-$(limit_posix_binout)

$(limit_posix_binout): $(limit_posix_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(limit_posix_cppout): $(limit_root)/posix.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# eof
