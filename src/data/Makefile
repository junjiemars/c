#
# ./configure --has-data
#
# system data
#
#

ifeq ($(CC_NAME), msvc)
io:
	@echo "#skip ..."
data_test:
	@echo "#skip ..."
else

data: data_grp                                  \
      data_host                                 \
      data_login                                \
      data_pwd                                  \
      data_time                                 \
      data_uname

data_test: data_grp_test                        \
           data_host_test                       \
           data_login_test                      \
           data_pwd_test                        \
           data_time_test                       \
           data_uname_test

endif


# env
data_prefix := data
INC += $(nm_inc_opt)$(data_root) $(nm_inc_opt)$(root)/posix


ifeq ($(CC_NAME), msvc)
getopt_c := $(root)/posix/getopt.c
endif

_MEMORY_ ?= 0
ifeq ($(shell test $(_MEMORY_) -gt 0; echo $$?),0)
CFLAGS += $(cflags_sanitize)
endif


# grp
data_nam_binout := $(bin_path)/$(data_prefix)_grp_nam$(bin_ext)
data_gid_binout := $(bin_path)/$(data_prefix)_grp_gid$(bin_ext)

data_grp: $(data_nam_binout)                    \
          $(data_gid_binout)
data_grp_test: data_nam_test                    \
               data_gid_test

data_nam_test: $(data_nam_binout)
	$< root daemon

data_gid_test: $(data_gid_binout)
	$< 0 1

$(data_nam_binout): $(data_root)/grp/nam.c      \
                    $(data_root)/grp/pgr.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(data_gid_binout): $(data_root)/grp/gid.c      \
                    $(data_root)/grp/pgr.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# host
data_host_binout := $(bin_path)/$(data_prefix)_data_host$(bin_ext)

data_host: $(data_host_binout)
data_host_test: data_host
	$(data_host_binout)

$(data_host_binout): $(data_root)/host/h.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# login
data_login_binout := $(bin_path)/$(data_prefix)_login$(bin_ext)

data_login: $(data_login_binout)
data_login_test: data_login
	$(data_login_binout)
	-$(data_login_binout) $(LOGNAME)

$(data_login_binout): $(data_root)/login/l.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# pwd
data_pwd_nam_binout := $(bin_path)/$(data_prefix)_data_pwd_nam$(bin_ext)
data_pwd_uid_binout := $(bin_path)/$(data_prefix)_data_pwd_uid$(bin_ext)

data_pwd: $(data_pwd_nam_binout)                \
          $(data_pwd_uid_binout)
data_pwd_test: data_pwd_nam_test                \
               data_pwd_uid_test

data_pwd_nam_test: $(data_pwd_nam_binout)
	$< nobody $(LOGNAME)
	command -v finger && finger $(LOGNAME) || echo

data_pwd_uid_test: $(data_pwd_uid_binout)
	$< 0 1

$(data_pwd_nam_binout): $(data_root)/pwd/nam.c  \
                        $(data_root)/pwd/ppwd.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(data_pwd_uid_binout): $(data_root)/pwd/uid.c  \
                        $(data_root)/pwd/ppwd.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# time
data_time_conv_binout := $(bin_path)/$(data_prefix)_time_conv$(bin_ext)
data_time_date_binout := $(bin_path)/$(data_prefix)_time_date$(bin_ext)
data_time_high_binout := $(bin_path)/$(data_prefix)_time_high$(bin_ext)

data_time: $(data_time_conv_binout)             \
           $(data_time_date_binout)             \
           $(data_time_high_binout)
data_time_test: data_time_conv_test             \
                data_time_date_test             \
                data_time_high_test

data_time_conv_test: $(data_time_conv_binout)
	$(data_time_conv_binout)
	TZ='' $(data_time_conv_binout)
	TZ='GMT' $(data_time_conv_binout)

data_time_date_test: $(data_time_date_binout)
	$<
	TZ='GMT' $<

data_time_high_test: $(data_time_high_binout)
	$(data_time_high_binout)

$(data_time_conv_binout): $(data_root)/time/conv.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(data_time_date_binout): $(data_root)/time/d1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(data_time_high_binout): $(data_root)/time/high.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# uname
data_uname_binout := $(bin_path)/$(data_prefix)_uname$(bin_ext)

data_uname: $(data_uname_binout)
data_uname_test: data_uname
	$(data_uname_binout)

$(data_uname_binout): $(data_root)/uname/u.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
