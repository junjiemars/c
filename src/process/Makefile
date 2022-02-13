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
         process_env

process_test: process_main_test                 \
              process_argv_test                 \
              process_argv_test

endif

# env
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
process_env_binout := $(bin_path)/$(process_prefix)_env$(bin_ext)

process_env: $(process_env_binout)
process_env_test: process_env
	$(process_env_binout)

$(process_env_binout): $(process_root)/env/e1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# eof
