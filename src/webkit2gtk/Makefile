#
# ./configure --has-webkit2gtk
#
#

ifeq (no, $(has_webkit2gtk))
	@echo "#skip ..."
else

webkit2gtk: webkit2gtk_gtk                      \
            webkit2gtk_hi                       \
            webkit2gtk_punk

webkit2gtk_test: webkit2gtk_gtk_test            \
                 webkit2gtk_hi_test             \
                 webkit2gtk_punk_test

endif

# env
webkit2gtk_prefix := webkit2gtk

INC += $(nm_inc_opt)$(webkit2gtk_root) $(nm_inc_opt)$(root)/posix
CFLAGS += $(webkit2gtk_cflags)
LDLIBS += $(webkit2gtk_ldlibs)

ifeq (msvc, $(CC_NAME))
getopt_c := $(root)posix/getopt.c
endif


# gtk
webkit2gtk_gtk_binout := $(bin_path)/$(webkit2gtk_prefix)_gtk$(bin_ext)

webkit2gtk_gtk: $(webkit2gtk_gtk_binout)
webkit2gtk_gtk_test: webkit2gtk_gtk
	$(webkit2gtk_gtk_binout) abc 123

$(webkit2gtk_gtk_binout): $(webkit2gtk_root)/gtk/g1.c
	$(CC) $(CPPFLAGS) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)



# hi
webkit2gtk_hi_binout := $(bin_path)/$(webkit2gtk_prefix)_hi$(bin_ext)

webkit2gtk_hi: $(webkit2gtk_hi_binout)
webkit2gtk_hi_test: webkit2gtk_hi
	$(webkit2gtk_hi_binout)

$(webkit2gtk_hi_binout): $(webkit2gtk_root)/hi/h.c
	$(CC) $(CPPFLAGS) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)


# punk
webkit2gtk_punk_b1_binout := $(bin_path)/$(webkit2gtk_prefix)_punk_b1$(bin_ext)
webkit2gtk_punk_b2_binout := $(bin_path)/$(webkit2gtk_prefix)_punk_b2$(bin_ext)

webkit2gtk_punk: $(webkit2gtk_punk_b1_binout)   \
                 $(webkit2gtk_punk_b2_binout)
webkit2gtk_punk_test: webkit2gtk_punk_b1_test   \
                      webkit2gtk_punk_b2_test

webkit2gtk_punk_b1_test: $(webkit2gtk_punk_b1_binout)
	$(webkit2gtk_punk_b1_binout)

webkit2gtk_punk_b2_test: $(webkit2gtk_punk_b2_binout)
	$(webkit2gtk_punk_b2_binout) -V

$(webkit2gtk_punk_b1_binout): $(webkit2gtk_root)/punk/b1.c
	$(CC) $(CPPFLAGS) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)

$(webkit2gtk_punk_b2_binout): $(webkit2gtk_root)/punk/b2.c
	$(CC) $(CPPFLAGS) $(INC) $(CFLAGS) $^ $(bin_out)$@ $(LDLIBS)



# eof
