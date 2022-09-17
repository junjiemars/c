#
# ./configure --has-webkit2gtk
#
#

ifeq (no, $(has_webkit2gtk))
	@echo "#skip ..."
else

webkit2gtk: webkit2gtk_hi
webkit2gtk_test: webkit2gtk_hi_test

endif

# env
webkit2gtk_prefix := webkit2gtk

INC += $(nm_inc_opt)$(webkit2gtk_root) $(nm_inc_opt)$(root)/posix
CFLAGS += $(webkit2gtk_cflags)
LDLIBS += $(webkit2gtk_ldlibs)


ifeq (msvc, $(CC_NAME))
getopt_c := $(root)posix/getopt.c
endif


# hi
webkit2gtk_hi_binout := $(bin_path)/$(webkit2gtk_prefix)_hi$(bin_ext)


webkit2gtk_hi: $(webkit2gtk_hi_binout)
webkit2gtk_hi_test: webkit2gtk_hi
	$(webkit2gtk_hi_binout)

$(webkit2gtk_hi_binout): $(webkit2gtk_root)/hi/h.c
	$(CC) $(CPPFLAGS) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)



# eof
