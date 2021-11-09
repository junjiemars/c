# ./configure --has-ctl


ctl: ctl_vec                                    \
     ctl_prefix                                 \
     ctl_eg_astar                               \
     ctl_eg_json

ctl_test: ctl_vec_test                          \
          ctl_prefix_test                       \
          ctl_eg_astar_test                     \
          ctl_eg_json_test


# env
ctl_prefix := ctl

ctl_git_src := 'https://github.com/glouw/ctl.git'
ctl_home := $(ctl_root)/ctl_home

INC += -I$(root) -I$(ctl_root) -I$(ctl_home)/ctl


ifeq ($(_MEMORY_), 1)
	CFLAGS += $(f_sanitize)
endif

ifeq ($(CC_NAME), msvc)
	CFLAGS += -wd4127 -wd4267
endif

$(ctl_home):
	git clone --depth=1 --branch=master $(ctl_git_src) $@


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



clean_ctl_home:
	-$(RM) -rf $(ctl_home)


.PHONY: clean_ctl_home


# eof
