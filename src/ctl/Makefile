# ./configure --has-ctl
#
# ctl: the C template library
# https://github.com/glouw/ctl.git
#



ctl: ctl_vec                                    \
     ctl_lst                                   \
     ctl_prefix                                 \
     ctl_eg_astar                               \
     ctl_eg_json

ctl_test: ctl_vec_test                          \
          ctl_vec_lst_test                     \
          ctl_prefix_test                       \
          ctl_eg_astar_test                     \
          ctl_eg_json_test


# env
ctl_prefix := ctl

ctl_git_src := 'https://github.com/glouw/ctl.git'
ctl_home := $(ctl_root)/ctl_home

INC += $(nm_inc_opt)$(root) $(nm_inc_opt)$(root)/posix
INC += $(nm_inc_opt)$(ctl_root) $(nm_inc_opt)$(ctl_home)/ctl


ifeq ($(_MEMORY_), 1)
	CFLAGS += $(f_sanitize)
endif

ifeq ($(CC_NAME), msvc)
	CFLAGS += -wd4127 -wd4267 -wd4244
endif

$(ctl_home):
	git clone --depth=1 --branch=master $(ctl_git_src) $@

clean_ctl_home:
	-$(RM) -rf $(ctl_home)



# vec
ctl_vec_binout := $(bin_path)/$(ctl_prefix)_vec$(bin_ext)
ctl_vec_cppout := $(tmp_path)/$(ctl_prefix)_vec$(cpp_ext)

ctl_vec: $(ctl_home) $(ctl_vec_binout)
ctl_vec_test: ctl_vec
	$(ctl_vec_binout)

$(ctl_vec_binout): $(ctl_vec_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_vec_cppout): $(ctl_root)/vec/vec1.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# lst
ctl_lst_binout := $(bin_path)/$(ctl_prefix)_lst$(bin_ext)
ctl_lst_cppout := $(tmp_path)/$(ctl_prefix)_lst$(cpp_ext)

ctl_lst: $(ctl_home) $(ctl_lst_binout)
ctl_lst_test: ctl_lst
	$(ctl_lst_binout)

$(ctl_lst_binout): $(ctl_lst_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_lst_cppout): $(ctl_root)/lst/lst1.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# prefix
ctl_prefix_binout := $(bin_path)/$(ctl_prefix)_prefix$(bin_ext)

ctl_prefix: $(ctl_home) $(ctl_prefix_binout)
ctl_prefix_test: ctl_prefix
	$(ctl_prefix_binout)

$(ctl_prefix_binout): $(ctl_root)/prefix/prefix1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eg/astar
ctl_eg_astar_binout := $(bin_path)/$(ctl_prefix)_eg_astar$(bin_ext)

ctl_eg_astar: $(ctl_home) $(ctl_eg_astar_binout)
ctl_eg_astar_test: ctl_eg_astar
	$(ctl_eg_astar_binout)

$(ctl_eg_astar_binout): $(ctl_home)/examples/astar.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eg/json
ctl_eg_json_binout := $(bin_path)/$(ctl_prefix)_eg_json$(bin_ext)

ctl_eg_json: $(ctl_home) $(ctl_eg_json_binout)
ctl_eg_json_test: ctl_eg_json
	$(ctl_eg_json_binout)

$(ctl_eg_json_binout): $(ctl_home)/examples/json.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



.PHONY: clean_ctl_home


# eof
