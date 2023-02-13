#
# ./configure --has-ipc
#
#

ifeq ($(NM_SYSTEM),WinNT)
ipc:
	@echo "#skip ..."
ipc_test:
	@echo "#skip ..."
else

ipc: ipc_bone                                   \
     ipc_filter                                 \
     ipc_pager

ipc_test: ipc_bone_test                         \
          ipc_filter_test                       \
          ipc_pager_test

endif


# env
ipc_prefix := ipc
INC += $(nm_inc_opt)$(ipc_root) $(nm_inc_opt)$(root)/posix

ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(f_sanitize)
endif

stat := stat
ifeq ($(NM_SYSTEM),Darwin)
stat := stat -x
endif



# bone
ipc_bone_binout := $(bin_path)/$(ipc_prefix)_bone$(bin_ext)

ipc_bone: $(ipc_bone_binout)
ipc_bone_test: ipc_bone
	$(ipc_bone_binout)

$(ipc_bone_binout): $(ipc_root)/bone/b1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# filter
ipc_filter_d_binout := $(bin_path)/$(ipc_prefix)_filter_d$(bin_ext)
ipc_filter_calc_binout := $(bin_path)/$(ipc_prefix)_filter_calc$(bin_ext)
ipc_filter_file := $(tmp_path)/$(ipc_prefix)_filter.file

ipc_filter: $(ipc_filter_d_binout)              \
            $(ipc_filter_calc_binout)
ipc_filter_test: ipc_filter_d_test              \
                 ipc_filter_calc_test

ipc_filter_d_test: $(ipc_filter_d_binout)       \
                   $(ipc_filter_calc_binout)
	echo "3 + 5" | $< $(ipc_filter_calc_binout)

$(ipc_filter_d_binout): $(ipc_root)/filter/d.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

ipc_filter_calc_test: $(ipc_filter_calc_binout)
	echo "3 + 5" | $<
	echo "3 * 5" >$(ipc_filter_file) && $< 0<$(ipc_filter_file)

$(ipc_filter_calc_binout): $(ipc_root)/filter/calc1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# pager
ipc_pager_raw_binout := $(bin_path)/$(ipc_prefix)_pager_raw$(bin_ext)
ipc_pager_std_binout := $(bin_path)/$(ipc_prefix)_pager_std$(bin_ext)
ipc_pager_emu_binout := $(bin_path)/$(ipc_prefix)_pager_emu$(bin_ext)
ipc_pager_more_bin = $(shell command -v more)

ipc_pager: $(ipc_pager_raw_binout)              \
           $(ipc_pager_std_binout)              \
           $(ipc_pager_emu_binout)
ipc_pager_test: ipc_pager_raw_test              \
                ipc_pager_std_test              \
                ipc_pager_emu_test

ipc_pager_raw_test: $(ipc_pager_raw_binout)
	# $< $(CURDIR)/$(ipc_root)/pager/r1.c
	-$<

ipc_pager_std_test: $(ipc_pager_std_binout)
	# $< $(CURDIR)/$(ipc_root)/pager/s1.c
	-$<

ipc_pager_emu_test: $(ipc_pager_emu_binout)
	# $< $(CURDIR)/$(ipc_root)/pager/e1.c
	-$<

$(ipc_pager_raw_binout): $(ipc_root)/pager/p1.c \
                         $(ipc_root)/pager/r1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                    \
    $(nm_def_opt)DEF_PAGER="\"${ipc_pager_more_bin}\""  \
    $^ $(bin_out)$@

$(ipc_pager_std_binout): $(ipc_root)/pager/p1.c \
                         $(ipc_root)/pager/s1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                    \
    $(nm_def_opt)DEF_PAGER="\"${ipc_pager_more_bin}\""  \
    $^ $(bin_out)$@

$(ipc_pager_emu_binout): $(ipc_root)/pager/p1.c \
                         $(ipc_root)/pager/s1.c \
                         $(ipc_root)/pager/e1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC)                    \
    $(nm_def_opt)DEF_PAGER="\"${ipc_pager_more_bin}\""  \
    $^ $(bin_out)$@



# eof
