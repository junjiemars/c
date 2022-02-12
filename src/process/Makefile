#
# ./configure --has-process
#

ifeq ($(CC_NAME), msvc)
process:
	@echo "#skip ..."
process_test: process
	@echo "#skip ..."
else

process: process_pause

process_test: process_pause_test

endif

# env
process_prefix := process
INC += $(nm_inc_opt)$(process_root) $(nm_inc_opt)$(root)/posix


# main
process_main_binout := $(bin_path)/$(process_prefix)_main$(bin_ext)

process_main: $(process_main_binout)
process_main_test: process_main
	$(process_main_binout)

$(process_main_binout): $(process_root)/main/m99.c
	$(CC) $(CFLAGS) $(INC)                        \
     -D_RETURN_INT_=$(_RETURN_INT_)             \
     -D_WITH_RETURN_=$(_WITH_RETURN_)           \
     -D_WITH_EXIT_=$(_WITH_EXIT_)               \
     $^ $(bin_out)$@



# eof
