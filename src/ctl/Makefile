# ./configure --has-ctl


ctl_prefix := ctl

ctl_git_src := 'https://github.com/glouw/ctl.git'
ctl_home := $(ctl_root)/ctl_home


ctl: ctl_vec

ctl_test: ctl_vec_test


INC += -I$(root) -I$(ctl_root) -I$(ctl_home)/ctl


# _MEMORY_
ifeq (1, $(_MEMORY_))
ctl_cc_opt += $(f_sanitize)
ctl_ld_opt += $(f_sanitize)
endif # end of _MEMORY_


$(ctl_home):
	git clone --depth=1 --branch=master $(ctl_git_src) $@


# vec
ctl_vec_binout := $(bin_path)/$(ctl_prefix)_vec$(bin_ext)

ctl_vec: $(ctl_home) $(ctl_vec_binout)
ctl_vec_test: ctl_vec
	$(ctl_vec_binout)

$(ctl_vec_binout): $(ctl_root)/vec/vec1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


clean_ctl_home:
	-$(RM) -rf $(ctl_home)


.PHONY: ctl_clean_home


# eof
