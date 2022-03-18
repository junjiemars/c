#
# ./configure --has-sh
#
#

ifeq ($(CC_NAME), msvc)
sh: sh_bone
	@echo "#skip ..."
sh_test: sh_bone_test
	@echo "#skip ..."
else

sh: sh_bone

sh_test: sh_bone_test

endif


# env
sh_prefix := sh
INC += $(nm_inc_opt)$(sh_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(sh test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(cflags_sanitize)
endif


# bone
sh_bone_binout := $(bin_path)/$(sh_prefix)_bone$(bin_ext)

sh_bone: $(sh_bone_binout)
sh_bone_test: sh_bone
	echo "" | $(sh_bone_binout)

$(sh_bone_binout): $(sh_root)/sh1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
