# -*- mode:makefile-gmake -*-
#
# ./configure --has-uemacs --with-error=no
#
#


uemacs: uemacs_core


uemacs_test: uemacs_core_test


# env
uemacs_out := $(CURDIR)/$(out)/var/uemacs

uemacs_git_src := "https://github.com/torvalds/uemacs.git"
uemacs_home_dir := $(CURDIR)/$(uemacs_root)/uemacs_home
uemacs_makefile := $(CURDIR)/$(inc_path)/uemacs.Makefile

ifeq ($(_MEMORY_),1)
uemacs_cflags += $(f_sanitize)
endif # end of _MEMORY_

uemacs_home: $(uemacs_makefile)

$(uemacs_makefile): $(uemacs_home_dir)
	sed -e"s/^CC=.*/CC=${CC}/g" \
      -e"s/^CFLAGS=.*/CFLAGS=${CFLAGS}/g" \
      -e"s#^BINDIR=.*#BINDIR=${bin_path}#g" \
      -e"s#^LIBDIR=.*#LIBDIR=${lib_path}#g" \
    $(uemacs_home_dir)/Makefile >${uemacs_makefile}

$(uemacs_home_dir):
	git clone --depth=1 --branch=master $(uemacs_git_src) $(uemacs_home_dir)



# core
uemacs_core_binout := $(bin_path)/$(uemacs_prefix)_em

uemacs_core: $(uemacs_core_binout)
uemacs_core_test: uemacs_core
	$(uemacs_core_binout) --version

$(uemacs_core_binout): $(uemacs_makefile)
	@make -f $< -C $(uemacs_home_dir)
	@cp $(uemacs_home_dir)/em $@

# clean
uemacs_clean: clean \
              clean_uemacs_home

clean_uemacs_home:
	-$(RM) -rf $(uemacs_home_dir)

clean_uemacs_out:
	@make -f $(uemacs_home_dir)/Makefile \
	  -C $(uemacs_home_dir) \
    clean


.PHONY: uemacs_home uemacs_clean clean_uemacs_home clean_uemacs_out


# eof
