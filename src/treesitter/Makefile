# -*- mode:makefile-gmake -*-
#
# ./configure --has-nginx
#
#

treesitter_out := $(CURDIR)/$(out)/var/treesitter
treesitter_git_src := 'https://github.com/tree-sitter/tree-sitter.git'
treesitter_home := $(treesitter_root)/treesitter_home


treesitter: $(treesitter_home)                  \
            treesitter_lib

treesitter_test: $(treesitter_home)             \
            treesitter_lib_test



# env

ifeq (1, $(_MEMORY_))
CFLAGS += $(f_sanitize)
endif # end of _MEMORY_

$(treesitter_home):
	git clone --depth=1 --branch=master $(treesitter_git_src) $@



# lib
treesitter_lib_binout := $(treesitter_home)/libtree-sitter.a

ifeq ($(CC_NAME),msvc)
treesitter_lib:
	@echo "#skip treesitter_lib_test ..."
treesitter_lib_test: treesitter_lib
else
treesitter_lib: $(treesitter_lib_binout)
treesitter_lib_test: treesitter_lib
endif

$(treesitter_lib_binout): $(treesitter_home)
	 make -C $(treesitter_home)



# clean
treesitter_clean: clean                         \
                  clean_treesitter_home

clean_treesitter_home:
	make -C $(CURDIR)/$(treesitter_home) clean

.PHONY: treesitter_clean clean_treesitter_home

# eof
