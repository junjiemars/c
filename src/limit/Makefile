#
# ./configure --has-limit
#

ifeq ($(CC_NAME), msvc)
limit:
	@echo "#skip ..."
limit_test: limit
	@echo "#skip ..."
else

limit: limit_l                                  \
       limit_path

limit_test: limit_l_test                        \
            limit_path_test
endif

# limit env
limit_prefix := limit
INC += $(nm_inc_opt)$(limit_root)


# posix
limit_l_binout := $(bin_path)/$(limit_prefix)_l$(bin_ext)
limit_l_source := $(tmp_path)/$(limit_prefix)_l.c
limit_l_awk := $(limit_root)/l.awk
limit_l_awk_in := $(limit_root)/l.awk.in

limit_l: $(limit_l_binout)
limit_l_test: limit_l
	$(limit_l_binout)

$(limit_l_binout): $(limit_l_source)
	$(CC) $(INC) $(CPPFLAGS) $(CFLAGS) $^ $(bin_out)$@

$(limit_l_source): $(limit_l_awk)               \
                   $(limit_l_awk_in)
	awk -f $^ > $@

# path
limit_path_binout := $(bin_path)/$(limit_prefix)_path$(bin_ext)

limit_path: $(limit_path_binout)
limit_path_test: limit_path
	$(limit_path_binout) / /dev /tmp ~/

$(limit_path_binout): $(limit_root)/path.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
