# ./configure --has-stdio1
#
# An emulation of standard IO library
#


# env
stdio1_prefix := stdio1
INC += $(nm_inc_opt)$(stdio1_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(f_sanitize)
endif

stdio1_bin_binout := $(bin_path)/$(stdio1_prefix)_bin$(bin_ext)
stdio1_lib_objout := $(tmp_path)/$(stdio1_prefix)_lib$(obj_ext)
stdio1_bin_objout := $(tmp_path)/$(stdio1_prefix)_bin$(obj_ext)
stdio1_bin_cppout := $(tmp_path)/$(stdio1_prefix)_lib$(cpp_ext)
stdio1_out_file := $(tmp_path)/$(stdio1_prefix)_out.file

$(stdio1_bin_binout): $(stdio1_lib_objout)      \
                      $(stdio1_bin_objout)
	$(LINK) $(CFLAGS) $^ $(bin_out)$@

$(stdio1_lib_objout): $(stdio1_root)/l.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(stdio1_bin_objout): $(stdio1_bin_cppout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(stdio1_bin_cppout): $(stdio1_root)/m.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


ifeq ($(NM_SYSTEM),WinNT)
stdio1:
	@echo "#skip ..."
stdio1_test: stdio1
	@echo "#skip ..."
else


stdio1: $(stdio1_bin_binout)

stdio1_test: stdio1
	$(stdio1_bin_binout) 0< $(out)/nore.h
	$(stdio1_bin_binout) $(stdio1_root)/l.c $(stdio1_out_file)


endif 													#skip


# eof
