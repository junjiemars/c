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
         process_layout                         \
         process_rlimit                         \
         process_zombie

process_test: process_main_test                 \
              process_argv_test                 \
              process_env_test                  \
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
process_env_raw_binout := $(bin_path)/$(process_prefix)_env$(bin_ext)
process_env_mem_binout := $(bin_path)/$(process_prefix)_mem$(bin_ext)
process_env_child_binout := $(bin_path)/$(process_prefix)_child$(bin_ext)

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
