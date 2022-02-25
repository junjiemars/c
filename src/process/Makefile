#
# ./configure --has-process
#

ifeq ($(CC_NAME), msvc)
process:
	@echo "#skip ..."
process_test: process
	@echo "#skip ..."
else

process: process_main                           \
         process_argv                           \
         process_env                            \
         process_exec                           \
         process_layout                         \
         process_rlimit                         \
         process_zombie

process_test: process_main_test                 \
              process_argv_test                 \
              process_env_test                  \
              process_exec_test                 \
              process_layout_test               \
              process_rlimit_test               \
              process_zombie

endif

# process env
process_prefix := process
INC += $(nm_inc_opt)$(process_root) $(nm_inc_opt)$(root)/posix


# main
process_main_binout := $(bin_path)/$(process_prefix)_main$(bin_ext)
_RETURN_INT_ ?= 1
_WITH_RETURN_ ?= 1
_WITH_EXIT_ ?= 0

process_main: $(process_main_binout)
process_main_test: process_main
	-$(process_main_binout)

$(process_main_binout): $(process_root)/main/m99.c
	$(CC) $(CFLAGS) $(INC)                        \
    -D_RETURN_INT_=$(_RETURN_INT_)             \
    -D_WITH_RETURN_=$(_WITH_RETURN_)           \
    -D_WITH_EXIT_=$(_WITH_EXIT_)               \
    $^ $(bin_out)$@


# argv
process_argv_binout := $(bin_path)/$(process_prefix)_argv$(bin_ext)

process_argv: $(process_argv_binout)
process_argv_test: process_argv
	$(process_argv_binout)
	$(process_argv_binout) a b c

$(process_argv_binout): $(process_root)/argv/clargv.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# env
process_env_raw_binout := $(bin_path)/$(process_prefix)_env_raw$(bin_ext)
process_env_mem_binout := $(bin_path)/$(process_prefix)_env_mem$(bin_ext)
process_env_child_binout := $(bin_path)/$(process_prefix)_env_child$(bin_ext)

process_env: $(process_env_raw_binout)          \
             $(process_env_mem_binout)          \
             $(process_env_child_binout)
process_env_test: process_env
	$(process_env_raw_binout)
	$(process_env_mem_binout)
	$(process_env_child_binout)

process_env_mem_test: $(process_env_mem_binout)
	$(process_env_mem_binout)

process_env_child_test: $(process_env_child_binout)
	$(process_env_child_binout)

$(process_env_raw_binout): $(process_root)/env/raw.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ $(bin_out)$@

$(process_env_mem_binout): $(process_root)/env/mem.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_env_child_binout): $(process_root)/env/child.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# exec
process_exec_echo_binout := $(bin_path)/$(process_prefix)_exec_echo$(bin_ext)
process_exec_vary_binout := $(bin_path)/$(process_prefix)_exec_vary$(bin_ext)
process_exec_vary_cppout := $(tmp_path)/$(process_prefix)_exec_vary$(cpp_ext)
process_exec_child_binout := $(bin_path)/$(process_prefix)_exec_child$(bin_ext)

process_exec: $(process_exec_echo_binout)       \
              $(process_exec_vary_binout)       \
              $(process_exec_child_binout)
process_exec_test: process_exec                 \
                   process_exec_vary_test       \
                   process_exec_child_test
	$(process_exec_echo_binout)

process_exec_vary_test: $(process_exec_echo_binout) \
                        $(process_exec_vary_binout)
	$(process_exec_vary_binout) execl
	$(process_exec_vary_binout) execle
	$(process_exec_vary_binout) execv
	PATH="$(PATH):$(CURDIR)/$(bin_path)" $(process_exec_vary_binout) execlp
	PATH="$(PATH):$(CURDIR)/$(bin_path)" $(process_exec_vary_binout) execvp

process_exec_child_test: $(process_exec_echo_binout)  \
                         $(process_exec_child_binout)
	PATH="$(PATH):$(CURDIR)/$(bin_path)" $(process_exec_child_binout)

$(process_exec_echo_binout): $(process_root)/exec/echoa.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(process_exec_vary_binout): $(process_exec_vary_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(process_exec_vary_cppout): $(process_root)/exec/vary.c
	$(CC) $(CPPFLAGS) $(INC)                              \
    -D_PATH_NAME_=\"$(CURDIR)/$(process_exec_echo_binout)\" \
    -D_FILE_NAME_=\"$(process_prefix)_exec_echo$(bin_ext)\" \
    $(nm_stage_pre) $^ $(cpp_out)$@

$(process_exec_child_binout): $(process_root)/exec/child.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                        \
    -D_PATH_NAME_=\"$(CURDIR)/$(process_exec_echo_binout)\" \
    -D_FILE_NAME_=\"$(process_prefix)_exec_echo$(bin_ext)\" \
    -D_WAIT_=0                                              \
    $^ $(bin_out)$@


# layout
process_layout_binout := $(bin_path)/$(process_prefix)_layout$(bin_ext)
process_layout_asmout := $(tmp_path)/$(process_prefix)_layout$(asm_ext)
process_layout_static_binout := \
  $(bin_path)/$(process_prefix)_layout_static$(bin_ext)

process_layout: $(process_layout_binout)
process_layout_test: process_layout
	size $(process_layout_binout)
	nm $(process_layout_binout)

$(process_layout_binout): $(process_layout_asmout)
	$(LINK) $^ $(bin_out)$@

$(process_layout_asmout): $(process_root)/layout/mem.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_asm) $^ $(asm_out)$@

$(process_layout_static_binout): $(process_root)/layout/mem.c
	$(CC) $(CFLAGS) $(INC) -static $^ $(bin_out)$@


# rlimit
process_rlimit_binout := $(bin_path)/$(process_prefix)_rlimit$(bin_ext)

process_rlimit: $(process_rlimit_binout)
process_rlimit_test: process_rlimit
	$(process_rlimit_binout)

$(process_rlimit_binout): $(process_root)/rlimit/def.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# zombie
process_zombie_binout := $(bin_path)/$(process_prefix)_zombie$(bin_ext)

process_zombie: $(process_zombie_binout)
process_zombie_test: process_zombie
	$(process_zombie_binout)

$(process_zombie_binout): $(process_root)/zombie/z.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof