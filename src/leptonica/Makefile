# -*- mode:makefile-gmake -*-
#
# ./configure --has-leptonica
#

ifeq ($(has_leptonica_required),NO)
leptonica: leptonica_basic
leptonica_test: leptonica_basic_test
else
leptonica:
leptonica_test: leptonica
	@echo "#skip ... no all leptonica requirements found"
endif



# env
leptonica_prefix := leptonica

leptonica_out := $(CURDIR)/$(out)/var/leptonica
leptonica_git_src := 'https://github.com/DanBloomberg/leptonica.git'
leptonica_home := $(leptonica_root)/leptonica_home

leptonica_inc_dir := $(leptonica_out)/include
leptonica_lib_dir := $(leptonica_out)/lib
leptonica_lib_arout := $(leptonica_lib_dir)/libleptonica.a

leptonica_lib_ar := $(nm_lib_opt)z
leptonica_lib_ar += $(nm_lib_opt)png16
leptonica_lib_ar += $(nm_lib_opt)jpeg
leptonica_lib_ar += $(nm_lib_opt)openjp2
leptonica_lib_ar += $(nm_lib_opt)gif
leptonica_lib_ar += $(nm_lib_opt)tiff
leptonica_lib_ar += $(nm_lib_opt)webpmux
leptonica_lib_ar += $(nm_lib_opt)webp

leptonica_build := $(leptonica_inc_dir)/leptonica/allheaders.h
leptonica_build += $(leptonica_lib_dir)/libleptonica$(lib_ext)
leptonica_build += $(leptonica_lib_dir)/pkgconfig


INC += $(nm_inc_opt)$(root)
INC += $(nm_inc_opt)$(root)/posix
INC += $(nm_inc_opt)$(leptonica_root) $(nm_inc_opt)$(root)
INC += $(nm_inc_opt)$(leptonica_inc_dir)
leptonica_libs := $(nm_libdir_opt)$(leptonica_lib_dir) $(nm_lib_opt)leptonica

leptonica_cc_opt :=
leptonica_ld_opt :=
leptonica_debug_opt :=

leptonica_cc_opt += $(nm_release_opt)
leptonica_cc_opt += $(nm_optimize_opt)
leptonica_cc_opt += $(nm_symbol_opt)


ifeq (1, $(_MEMORY_))
leptonica_cc_opt += $(f_sanitize)
leptonica_ld_opt += $(f_sanitize)
endif # end of _MEMORY_


ifeq (1, $(_DEBUG_))
leptonica_debug_opt := --enable-debug
endif # end of _DEBUG_


ifeq (msvc, $(CC_NAME))
getopt_c := $(root)/posix/getopt.c
endif # end of msvc

# build leptonica
PKG_CONFIG_PATH = $(leptonica_lib_dir)/pkgconfig

$(leptonica_build): $(leptonica_home)
	cd $(leptonica_home) \
    && ./autogen.sh \
    && CFLAGS="$(leptonica_cc_opt)" \
       ./configure --prefix=$(leptonica_out) \
                   --disable-programs \
                   $(leptonica_enable_debug) \
    && make -C . -j4 install

$(leptonica_home):
	git clone --depth=1 --branch=master $(leptonica_git_src) $@



# basic
leptonica_basic_static_binout := $(bin_path)/$(leptonica_prefix)_basic_static$(bin_ext)
leptonica_basic_shared_binout := $(bin_path)/$(leptonica_prefix)_basic_shared$(bin_ext)
leptonica_basic_in_image := $(tmp_path)/$(leptonica_prefix)_basic_in.png


leptonica_basic: $(leptonica_build) \
                 $(leptonica_basic_in_image)
leptonica_basic_test: leptonica_basic_shared_test

leptonica_basic_static_test: $(leptonica_build) \
                             $(leptonica_basic_static_binout) \
                             $(leptonica_basic_in_image)
	$(leptonica_basic_static_binout) \
    -i $(CURDIR)/$(leptonica_basic_in_image) \
    -o $(CURDIR)/$(tmp_path)/$(leptonica_prefix)_basic_static_out.png
	$(leptonica_basic_static_binout) \
    -i $(CURDIR)/$(leptonica_basic_in_image) \
    -o $(CURDIR)/$(tmp_path)/$(leptonica_prefix)_basic_static_out_half.png \
    -x 0.50

leptonica_basic_shared_test: $(leptonica_build) \
                             $(leptonica_basic_shared_binout) \
                             $(leptonica_basic_in_image)
	LD_LIBRARY_PATH=$(leptonica_lib_dir) $(leptonica_basic_shared_binout) \
    -i $(CURDIR)/$(leptonica_basic_in_image) \
    -o $(CURDIR)/$(tmp_path)/$(leptonica_prefix)_basic_shared_out.png
	LD_LIBRARY_PATH=$(leptonica_lib_dir) $(leptonica_basic_shared_binout) \
    -i $(CURDIR)/$(leptonica_basic_in_image) \
    -o $(CURDIR)/$(tmp_path)/$(leptonica_prefix)_basic_shared_out_half.png \
    -x 0.50 \
    -y 0.25

$(leptonica_basic_static_binout): $(leptonica_root)/basic/b.c \
                                  $(getopt_c) \
                                  $(leptonica_lib_arout)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(leptonica_lib_ar)

$(leptonica_basic_shared_binout): $(leptonica_root)/basic/b.c \
                                  $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(leptonica_libs)

$(leptonica_basic_in_image): $(leptonica_root)/basic/b.png
	cp $< $@



# clean
leptonica_clean: clean \
                 clean_leptonica_home


clean_leptonica_home:
	-$(RM) -rf $(leptonica_home)

clean_leptonica_out:
	test ! -f $(CURDIR)/$(leptonica_home)/Makefile \
    || make -C $(CURDIR)/$(leptonica_home) clean
	test ! -d $(leptonica_out) || rm -r $(leptonica_out)

clean_leptonica_bin:
	test ! -f $(leptonica_basic_static_binout) \
    || rm $(leptonica_basic_static_binout)
	test ! -f $(leptonica_basic_shared_binout) \
    || rm $(leptonica_basic_shared_binout)


.PHONY: leptonica_clean                         \
        clean_leptoonica_home                   \
        clean_leptonica_out                     \
        clean_leptonica_bin                     \
        leptonica leptonica_test


# eof
