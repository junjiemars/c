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

data: data_id                                   \
      data_time

data_test: data_id_test                         \
           data_time_test

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
data_id_un_binout := $(bin_path)/$(data_prefix)_id_un$(bin_ext)
data_id_hn_binout := $(bin_path)/$(data_prefix)_id_hn$(bin_ext)

data_id: $(data_id_un_binout)                   \
         $(data_id_hn_binout)
data_id_test: data_id_un_test                   \
              data_id_hn_test

data_id_un_test: $(data_id_un_binout)
	$(data_id_un_binout)

data_id_hn_test: $(data_id_hn_binout)
	$(data_id_hn_binout)

$(data_id_un_binout): $(data_root)/id/un.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(data_id_hn_binout): $(data_root)/id/hn.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# time
data_time_conv_binout := $(bin_path)/$(data_prefix)_time_conv_un$(bin_ext)
data_time_conv_hn_binout := $(bin_path)/$(data_prefix)_time_conv_hn$(bin_ext)

data_time: $(data_time_conv_binout)
data_time_test: data_time_conv_test

data_time_conv_test: $(data_time_conv_binout)
	$(data_time_conv_binout)

$(data_time_conv_binout): $(data_root)/time/conv.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
