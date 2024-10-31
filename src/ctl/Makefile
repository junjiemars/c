# -*- mode:makefile-gmake -*-
#
# ./configure --has-ctl
#
# ctl: the C template library
# https://github.com/glouw/ctl.git
#

ctl: ctl_deq                                    \
     ctl_lst                                    \
     ctl_pqu                                    \
     ctl_que                                    \
     ctl_set                                    \
     ctl_stk                                    \
     ctl_str                                    \
     ctl_ust                                    \
     ctl_vec                                    \
     ctl_eg_astar                               \
     ctl_eg_json

ctl_test: ctl_deq_test                          \
          ctl_lst_test                          \
          ctl_pqu_test                          \
          ctl_que_test                          \
          ctl_set_test                          \
          ctl_stk_test                          \
          ctl_str_test                          \
          ctl_ust_test                          \
          ctl_vec_test                          \
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
ifeq ($(CC_NAME), clang)
  CFLAGS += -Wno-unused-but-set-variable
endif

$(ctl_home):
	git clone --depth=1 --branch=master $(ctl_git_src) $@

clean_ctl_home:
	-$(RM) -rf $(ctl_home)

ctl_objout := $(tmp_path)/$(ctl_prefix)$(obj_ext)

$(ctl_objout): $(ctl_root)/_ctl_.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@


# deq
ctl_deq_binout := $(bin_path)/$(ctl_prefix)_deq$(bin_ext)
ctl_deq_cppout := $(tmp_path)/$(ctl_prefix)_deq$(cpp_ext)

ctl_deq: $(ctl_home) $(ctl_deq_binout)
ctl_deq_test: ctl_deq
	$(ctl_deq_binout)

$(ctl_deq_binout): $(ctl_deq_cppout)            \
                   $(ctl_objout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_deq_cppout): $(ctl_root)/deq/deq1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# lst
ctl_lst_binout := $(bin_path)/$(ctl_prefix)_lst$(bin_ext)
ctl_lst_cppout := $(tmp_path)/$(ctl_prefix)_lst$(cpp_ext)

ctl_lst: $(ctl_home) $(ctl_lst_binout)
ctl_lst_test: ctl_lst
	$(ctl_lst_binout)

$(ctl_lst_binout): $(ctl_lst_cppout)            \
                   $(ctl_objout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_lst_cppout): $(ctl_root)/lst/lst1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# pqu
ctl_pqu_binout := $(bin_path)/$(ctl_prefix)_pqu$(bin_ext)
ctl_pqu_cppout := $(tmp_path)/$(ctl_prefix)_pqu$(cpp_ext)

ctl_pqu: $(ctl_home) $(ctl_pqu_binout)
ctl_pqu_test: ctl_pqu
	$(ctl_pqu_binout)

$(ctl_pqu_binout): $(ctl_pqu_cppout)            \
                   $(ctl_objout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_pqu_cppout): $(ctl_root)/pqu/pqu1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# que
ctl_que_binout := $(bin_path)/$(ctl_prefix)_que$(bin_ext)
ctl_que_cppout := $(tmp_path)/$(ctl_prefix)_que$(cpp_ext)

ctl_que: $(ctl_home) $(ctl_que_binout)
ctl_que_test: ctl_que
	$(ctl_que_binout)

$(ctl_que_binout): $(ctl_que_cppout)            \
                   $(ctl_objout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_que_cppout): $(ctl_root)/que/que1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# set
ctl_set_binout := $(bin_path)/$(ctl_prefix)_set$(bin_ext)
ctl_set_cppout := $(tmp_path)/$(ctl_prefix)_set$(cpp_ext)

ctl_set: $(ctl_home) $(ctl_set_binout)
ctl_set_test: ctl_set
	$(ctl_set_binout)

$(ctl_set_binout): $(ctl_set_cppout)            \
                   $(ctl_objout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_set_cppout): $(ctl_root)/set/set1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# stk
ctl_stk_binout := $(bin_path)/$(ctl_prefix)_stk$(bin_ext)
ctl_stk_cppout := $(tmp_path)/$(ctl_prefix)_stk$(cpp_ext)

ctl_stk: $(ctl_home) $(ctl_stk_binout)
ctl_stk_test: ctl_stk
	$(ctl_stk_binout)

$(ctl_stk_binout): $(ctl_stk_cppout)            \
                   $(ctl_objout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_stk_cppout): $(ctl_root)/stk/stk1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# str
ctl_str_binout := $(bin_path)/$(ctl_prefix)_str$(bin_ext)
ctl_str_objout := $(tmp_path)/$(ctl_prefix)_str$(obj_ext)
ctl_str_cppout := $(tmp_path)/$(ctl_prefix)_str$(cpp_ext)

ctl_str: $(ctl_home) $(ctl_str_binout)
ctl_str_test: ctl_str
	$(ctl_str_binout)

$(ctl_str_binout): $(ctl_str_objout)            \
                   $(ctl_objout)
	$(LINK) $^ $(bin_out)$@

$(ctl_str_objout): $(ctl_str_cppout)
	$(CC) $(nm_stage_c) $^ $(obj_out)$@

$(ctl_str_cppout): $(ctl_root)/str/str1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# ust
ctl_ust_binout := $(bin_path)/$(ctl_prefix)_ust$(bin_ext)
ctl_ust_cppout := $(tmp_path)/$(ctl_prefix)_ust$(cpp_ext)

ctl_ust: $(ctl_home) $(ctl_ust_binout)
ctl_ust_test: ctl_ust
	$(ctl_ust_binout)

$(ctl_ust_binout): $(ctl_ust_cppout)            \
                   $(ctl_objout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(ctl_ust_cppout): $(ctl_root)/ust/ust1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# vec
ctl_vec_binout := $(bin_path)/$(ctl_prefix)_vec$(bin_ext)
ctl_vec_objout := $(tmp_path)/$(ctl_prefix)_vec$(obj_ext)
ctl_vec_cppout := $(tmp_path)/$(ctl_prefix)_vec$(cpp_ext)

ctl_vec: $(ctl_home) $(ctl_vec_binout)
ctl_vec_test: ctl_vec
	$(ctl_vec_binout)

$(ctl_vec_binout): $(ctl_vec_objout)            \
                   $(ctl_objout)
	$(LINK) $(CFLAGS) $^ $(obj_out)$@

$(ctl_vec_objout): $(ctl_vec_cppout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(ctl_vec_cppout): $(ctl_root)/vec/vec1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


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
