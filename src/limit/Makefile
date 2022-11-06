#
# ./configure --has-limit --with-std=no
#

ifeq ($(CC_NAME), msvc)
limit:
	@echo "#skip ..."
limit_test: limit
	@echo "#skip ..."
else

limit: limit_l                                  \
       limit_name

limit_test: limit_l_test                        \
            limit_name

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

# name
limit_name_binout := $(bin_path)/$(limit_prefix)_name$(bin_ext)

limit_name: $(limit_name_binout)
limit_name_test: limit_name
	$(limit_name_binout) / /dev /tmp ~/

$(limit_name_binout): $(limit_root)/name.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
