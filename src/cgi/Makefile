# -*- major-mode:makefile-gmake-mode -*-
#
# ./configure --has-cgi
#

cgi:  cgi_f_hi
cgi_test: cgi_f_hi_test

# env
cgi_prefix := cgi
posix_root ?= $(root)/posix
INC += $(nm_inc_opt)$(cgi_root) $(nm_inc_opt)$(posix_root)

ifeq ($(_MEMORY_),1)
CFLAGS += $(f_sanitize)
LDFLAGS += $(f_sanitize)
endif # end of _MEMORY_

ifeq ($(has_fcgi),yes)
f_inc := $(INC) $(fcgi_inc)
f_ldflags += $(fcgi_ldflags)
f_ldlibs += $(fcgi_ldlibs)
endif


# fcgi/hi
cgi_f_hi_binout := $(bin_path)/$(cgi_prefix)_f_hi$(bin_ext)

ifeq ($(has_fcgi),yes)
cgi_f_hi: $(cgi_f_hi_binout)
cgi_f_hi_test: cgi_f_hi
	echo "# skipped ... it's a fastcgi server, will block the making."
	# $(cgi_f_hi_binout)
else
cgi_f_hi:
	echo "# skipped ... no fcgi found"
cgi_f_hi_test:
	echo "# skipped ... no fcgi found"
endif

$(cgi_f_hi_binout): $(cgi_root)/fcgi/f1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(f_inc) $^ $(bin_out)$@ $(f_ldflags) $(f_ldlibs)



# eof
