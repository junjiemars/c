#
# ./configure --has-limit --with-std=no
#

ifeq ($(CC_NAME), msvc)
limit:
	@echo "#skip ..."
limit_test: limit
	@echo "#skip ..."
else

limit: limit_int                                \
       limit_gc

limit_test: limit_int_test                      \
            limit_gc_test

endif

# limit env
limit_prefix := limit
INC += $(nm_inc_opt)$(limit_root)


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
limit_l_binout := $(bin_path)/$(limit_prefix)_l$(bin_ext)
limit_l_source := $(tmp_path)/l.c
limit_l_awk_src := $(limit_root)/l.awk
limit_l_awk_in := $(limit_root)/l.awk.in
limit_l_awk_in_n := $(limit_root)/l.awk.in.n

limit_l: $(limit_l_binout)
limit_l_test: limit_l
	$(limit_l_binout)

$(limit_l_binout): $(limit_l_source)
	$(CC) $(INC) $(CPPFLAGS) $(CFLAGS) $^ $(bin_out)$@

$(limit_l_source): $(limit_l_awk_src)           \
                   $(limit_l_awk_in_n)          \
                   $(limit_l_awk_in)
	awk -f $^ > $@


# eof
