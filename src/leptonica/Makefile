#
# ./configure --has-leptonica
#


ifeq (Linux, $(NM_SYSTEM))
leptonica: leptonica_basic
leptonica_test: leptonica_basic_test
else
leptonica:
	@echo "#skip leptonica_test ..."
leptonica_test: leptonica
endif # end of msvc


# leptonica src & out
leptonica_home := $(leptonica_root)/leptonica_home
leptonica_git_src := 'https://github.com/DanBloomberg/leptonica.git'
leptonica_out_prefix := $(out)/var/leptonica
leptonica_out_incdir := $(leptonica_out_prefix)/include
leptonica_out_libdir := $(leptonica_out_prefix)/lib
leptonica_build := $(leptonica_out_incdir)/leptonica/allheaders.h	\
                   $(leptonica_out_libdir)/libleptonica$(lib_ext)


# env
leptonica_prefix := leptonica

INC += $(nm_inc_opt)$(leptonica_root) $(nm_inc_opt)$(root)
INC += $(nm_inc_opt)$(leptonica_out_incdir)
LDFLAGS += $(nm_libdir_opt)$(leptonica_out_libdir)

ifneq (msvc, $(CC_NAME))
leptonica_cc_opt += -O0 -g
leptonica_cc_opt += -Wno-unused-variable -Wno-unused-const-variable
endif # end of !msvc


ifeq (msvc, $(CC_NAME))
getopt_c := $(root)/posix/getopt.c
endif # end of msvc


$(leptonica_build): $(leptonica_home)
	CFLAGS="$(leptonica_cc_opt)" cd $(leptonica_home)						\
    && ./autogen.sh																						\
		&& ./configure --prefix=$(CURDIR)/$(leptonica_out_prefix)	\
                   --enable-share															\
                   --enable-debug															\
		&& make -j4 install

$(leptonica_home):
	git clone --depth=1 --branch=master $(leptonica_git_src) $@


# basic
leptonica_basic_binout := $(bin_path)/leptonica_basic$(bin_ext)
leptonica_basic_in_image := $(tmp_path)/b.png
leptonica_basic_out_image := $(tmp_path)/b-scaled.png


leptonica_basic: $(leptonica_build) 						\
                 $(leptonica_basic_binout)			\
                 $(leptonica_basic_in_image)
leptonica_basic_test: leptonica_basic
	LD_LIBRARY_PATH=$(leptonica_out_libdir) $(leptonica_basic_binout)	\
			-i $(CURDIR)/$(leptonica_basic_in_image)											\
			-o $(CURDIR)/$(tmp_path)/bs1.png
	LD_LIBRARY_PATH=$(leptonica_out_libdir) $(leptonica_basic_binout)	\
			-i $(CURDIR)/$(leptonica_basic_in_image)											\
			-o $(CURDIR)/$(tmp_path)/bs2.png															\
      -x 0.90																												\
      -y 0.75


$(leptonica_basic_binout): $(leptonica_root)/basic/b.c	\
                           $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@														\
		$(nm_libdir_opt)$(leptonica_out_libdir) $(nm_lib_opt)leptonica

$(leptonica_basic_in_image): $(leptonica_root)/basic/b.png
	cp $< $@

# clean
leptonica_clean: clean_leptonica_home


clean_leptonica_home:
	-$(RM) -rf $(leptonica_home)

clean_leptonica_objs:
	test ! -f $(CURDIR)/$(leptonica_home)/Makefile		\
		|| make -C $(CURDIR)/$(leptonica_home) clean

clean_leptonica_bin:
	test ! -f $(leptonica_basic_binout) || rm -r $(leptonica_basic_binout)


.PHONY: leptonica_clean clean_leptoonica_home clean_leptonica_objs	\
        leptonica_basic leptonica_basic_test 


# eof
