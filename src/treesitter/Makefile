# -*- mode:makefile-gmake -*-
#
# ./configure --has-nginx
#
#

treesitter_out := $(CURDIR)/$(out)/var/treesitter
treesitter_home := $(treesitter_root)/treesitter_home
treesitter_git_src := 'https://github.com/tree-sitter/tree-sitter.git'

treesitter: $(treesitter_home)                  \
            treesitter_lib                      \
            treesitter_c

treesitter_test: $(treesitter_home)             \
            treesitter_lib_test                 \
            treesitter_c_test



# env
treesitter_prefix := treesitter
INC += $(nm_inc_opt)$(treesitter_home)/lib/include

ifeq (1, $(_MEMORY_))
CFLAGS += $(f_sanitize)
endif # end of _MEMORY_

$(treesitter_home):
	git clone --depth=1 --branch=master $(treesitter_git_src) $@



# lib
treesitter_lib_libout := $(treesitter_home)/libtree-sitter.a

ifeq ($(CC_NAME),msvc)
treesitter_lib:
	@echo "#skip treesitter_lib_test ..."
treesitter_lib_test: treesitter_lib
else
treesitter_lib: $(treesitter_lib_libout)
treesitter_lib_test: treesitter_lib
endif

$(treesitter_lib_libout): $(treesitter_home)
	 make -C $(treesitter_home)



# c
treesitter_c_binout := $(bin_path)/$(treesitter_prefix)_c$(bin_ext)
treesitter_c_parser_git_src := 'https://github.com/tree-sitter/tree-sitter-c.git'
treesitter_c_parser_dir := $(treesitter_root)/c/parser
treesitter_c_parser_inc := $(nm_inc_opt)$(treesitter_root)/c/parser/src/treesitter
treesitter_c_parser := $(treesitter_root)/c/parser/src/parser.c
treesitter_c := $(treesitter_c_binout)
treesitter_c_test: $(treesitter_c_binout)
	$<

$(treesitter_c_binout): $(treesitter_root)/c/c1.c \
                        $(treesitter_c_parser)    \
                        $(treesitter_lib_libout)
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(treesitter_c_parser_dir):
	git clone --depth=1 --branch=master $(treesitter_c_parser_git_src) $@
$(treesitter_c_parser): $(treesitter_c_parser_dir)

# clean
treesitter_clean: clean                         \
                  clean_treesitter_home

clean_treesitter_home:
	make -C $(CURDIR)/$(treesitter_home) clean

.PHONY: treesitter_clean clean_treesitter_home

# eof
