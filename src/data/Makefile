#
# ./configure --has-data
#
#

ifeq ($(CC_NAME), msvc)
io: data_id
	@echo "#skip ..."
data_test: data_id_test
	@echo "#skip ..."
else

data: data_id

data_test: data_id_test

endif


# env
data_prefix := data
INC += $(nm_inc_opt)$(data_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME),msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(cflags_sanitize)
endif


# id
data_id_binout := $(bin_path)/$(data_prefix)_id$(bin_ext)

data_id: $(data_id_binout)
data_id_test: data_id
	$(data_id_binout)

$(data_id_binout): $(data_root)/id/un.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@




# eof
