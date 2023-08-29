#
# ./configure --has-unix
#

ifeq ($(NM_SYSTEM), WinNT)
unix:
	@echo "#skip ..."
unix_test: unix
	@echo "#skip ..."
else


unix: unix_brk                                  \
      unix_echo                                 \
      unix_ed \
      unix_exec                                 \
      unix_msq                                  \
	    unix_tcpwrapper

unix_test: unix_brk_test                        \
           unix_echo_test                       \
           unix_ed_test                                         \
           unix_exec_test                       \
           unix_msq_test                        \
           unix_tcpwrapper_test

endif

# env
unix_prefix := unix
INC += $(nm_inc_opt)$(unix_root) $(nm_inc_opt)$(root)/posix

ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(cflags_sanitize)
endif


# brk
unix_brk_binout := $(bin_path)/$(unix_prefix)_brk$(bin_ext)

unix_brk: $(unix_brk_binout)
unix_brk_test: unix_brk
	$(unix_brk_binout)

$(unix_brk_binout): $(unix_root)/brk/b.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# echo
unix_echo_binout := $(bin_path)/$(unix_prefix)_echo$(bin_ext)

unix_echo: $(unix_echo_binout)
unix_echo_test: unix_echo
	$(unix_echo_binout) -h
	$(unix_echo_binout) -n abc
	$(unix_echo_binout) abc 123 "xxx zzz"

$(unix_echo_binout): $(unix_root)/echo/e.c $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# ed
unix_ed_binout := $(bin_path)/$(unix_prefix)_ed$(bin_ext)

unix_ed: $(unix_ed_binout)
unix_ed_test: unix_ed
	# $(unix_ed_binout) -h
	echo $(unix_ed_binout)

$(unix_ed_binout): $(unix_root)/ed/ed.c $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# exec
unix_exec_binout := $(bin_path)/$(unix_prefix)_exec$(bin_ext)

unix_exec: $(unix_exec_binout)
unix_exec_test: unix_exec
	$(unix_exec_binout) "/bin/ls" "-lh" "."

$(unix_exec_binout): $(unix_root)/exec/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# msq
unix_msq_binout := $(bin_path)/$(unix_prefix)_msq$(bin_ext)

ifeq (Linux, $(NM_SYSTEM))
CFLAGS += -D_GNU_SOURCE
unix_msq: $(unix_msq_binout)
unix_msq_test: unix_msq
	$(unix_msq_binout) -s abcd ABCDEFGHIJKLMN
	$(unix_msq_binout) -r
	$(unix_msq_binout) -s abcd
	$(unix_msq_binout) -r -t 2
	$(unix_msq_binout) -r -t 1
else
unix_msq:
unix_msq_test: unix_msq
	@echo "#skip unix_msq_test ..."
endif

$(unix_msq_binout): $(unix_root)/msq/q.c
	$(CC) $(CFLAGS) $(msq_cflags) $(INC) $^ $(bin_out)$@


# tcp wrapper
unix_tcpwrapper_binout := $(bin_path)/$(unix_prefix)_tcpwrapper$(bin_ext)

ifeq (YES, $(has_tcpwrapper))
unix_tcpwrapper: $(unix_tcpwrapper_binout)
unix_tcpwrapper_test: unix_tcpwrapper
	$(unix_tcpwrapper_binout)
else
unix_tcpwrapper:
	@echo "#skip unix_tcpwrapper_test ..."
unix_tcpwrapper_test: unix_tcpwrapper
endif

$(unix_tcpwrapper_binout): $(unix_root)/tcpwrapper/tw.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(ldlibs_tcpwrapper)


# eof
