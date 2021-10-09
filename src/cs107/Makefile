#
# ./configure --has-cs107 --with-error=no
#

cs107: cs107_handout_10

cs107_test: cs107_handout_10_test

# env
cs107_prefix := cs107

INC += $(nm_inc_opt)$(cs107_root)

# handout 10
cs107_h10_binout := $(bin_path)/$(cs107_prefix)_h10$(bin_ext)

cs107_handout_10: $(cs107_h10_binout)
cs107_handout_10_test: cs107_handout_10
	$(cs107_h10_binout)

$(cs107_h10_binout): $(cs107_root)/handout10/h10.c 
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


