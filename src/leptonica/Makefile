#
# ./configure --has-leptonica
#

leptonica: leptonica_basic

leptonica_test: leptonica_basic_test


# env
leptonica_prefix := leptonica

leptonica_out := $(CURDIR)/$(out)/var/leptonica

leptonica_git_src := 'https://github.com/DanBloomberg/leptonica.git'
leptonica_home := $(leptonica_root)/leptonica_home


leptonica_inc_dir := $(leptonica_out)/include
leptonica_lib_dir := $(leptonica_out)/lib
leptonica_build := $(leptonica_inc_dir)/leptonica/allheaders.h  \
                   $(leptonica_lib_dir)/libleptonica$(lib_ext)


INC += $(nm_inc_opt)$(leptonica_root) $(nm_inc_opt)$(root)
INC += $(nm_inc_opt)$(leptonica_inc_dir)
LDFLAGS += $(nm_libdir_opt)$(leptonica_lib_dir)


leptonica_cc_opt :=
leptonica_ld_opt :=
leptonica_debug_opt :=


leptonica_cc_opt += $(nm_release_opt)
leptonica_cc_opt += $(nm_optimize_opt)
leptonica_cc_opt += $(nm_symbol_opt)
# leptonica_cc_opt += -Wno-unused-variable
# leptonica_cc_opt += -Wno-unused-const-variable
# leptonica_cc_opt += -Wno-unused-function


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


$(leptonica_build): $(leptonica_home)
	CFLAGS="$(leptonica_cc_opt)" cd $(leptonica_home) \
    && ./autogen.sh                                 \
    && ./configure --prefix=$(leptonica_out)        \
                   --disable-static                 \
                   --disable-programs               \
                   $(leptonica_enable_debug)        \
    && make -C . -j4 install


$(leptonica_home):
	git clone --depth=1 --branch=master $(leptonica_git_src) $@


# basic
leptonica_basic_binout := $(bin_path)/$(leptonica_prefix)_basic$(bin_ext)
leptonica_basic_in_image := $(tmp_path)/$(leptonica_prefix)_basic_in.png


ifeq (YES, $(has_leptonica_required))
leptonica_basic: $(leptonica_build)             \
                 $(leptonica_basic_binout)      \
                 $(leptonica_basic_in_image)
leptonica_basic_test: leptonica_basic
	LD_LIBRARY_PATH=$(leptonica_lib_dir) $(leptonica_basic_binout)  \
    -i $(CURDIR)/$(leptonica_basic_in_image)                      \
    -o $(CURDIR)/$(tmp_path)/$(leptonica_prefix)_basic_out.png
	LD_LIBRARY_PATH=$(leptonica_lib_dir) $(leptonica_basic_binout)          \
    -i $(CURDIR)/$(leptonica_basic_in_image)                              \
    -o $(CURDIR)/$(tmp_path)/$(leptonica_prefix)_basic_out_half_quad.png  \
    -x 0.50                                                               \
    -y 0.25
else
leptonica_basic:
	@echo "#skip leptonica_basic_test ..."
leptonica_basic_test: leptonica_basic
endif # end of has_leptonica_required


$(leptonica_basic_binout): $(leptonica_root)/basic/b.c  \
                           $(getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@                        \
    $(nm_libdir_opt)$(leptonica_lib_dir) $(nm_lib_opt)leptonica

$(leptonica_basic_in_image): $(leptonica_root)/basic/b.png
	cp $< $@

# clean
leptonica_clean: clean                          \
                 clean_leptonica_home


clean_leptonica_home:
	-$(RM) -rf $(leptonica_home)

clean_leptonica_out:
	test ! -f $(CURDIR)/$(leptonica_home)/Makefile  \
    || make -C $(CURDIR)/$(leptonica_home) clean
	test ! -d $(leptonica_out) || rm -rf $(leptonica_out)

clean_leptonica_bin:
	test ! -f $(leptonica_basic_binout) || rm -r $(leptonica_basic_binout)


.PHONY: leptonica_clean                         \
        clean_leptoonica_home                   \
        clean_leptonica_out                     \
        clean_leptonica_bin                     \
        leptonica_basic leptonica_basic_test


# eof
