#
# ./configure --has-cs107
#


cs107: cs107_0
cs107_test: cs107_0_test


# env
cs107_prefix := cs107
ctl_git_src := 'https://github.com/glouw/ctl.git'
ctl_home := $(cs107_root)/ctl_home

INC += $(nm_inc_opt)$(cs107_root) $(nm_inc_opt)$(ctl_home)/ctl


ifeq ($(NM_SYSTEM), WinNT)
	INC += $(nm_inc_opt)$(root)/posix
	getopt_c := $(root)/posix/getopt.c
endif

ifeq ($(NM_SYSTEM), Linux)
	CFLAGS += -D_POSIX_SOURCE -D_GNU_SOURCE
endif

ifeq ($(_MEMORY_), 1)
	CFLAGS += $(f_sanitize)
endif # end of _MEMORY_


$(ctl_home):
	git clone --depth=1 --branch=master $(ctl_git_src) $@


# 0
cs107_0_ruth_aaron_binout := $(bin_path)/$(cs107_prefix)_0_ruth_aaron$(bin_ext)
cs107_0_word_games_binout := $(bin_path)/$(cs107_prefix)_0_word_games$(bin_ext)
cs107_0_words_file := $(CURDIR)/$(cs107_root)/0/02-word-games/words

cs107_0: cs107_0_ruth_aaron)                    \
         cs107_0_word_games
cs107_0_test: $(cs107_0_ruth_aaron_test)        \
              $(cs107_0_word_games_test)

cs107_0_ruth_aaron: $(cs107_0_ruth_aaron_binout)
cs107_0_word_games: $(ctl_home) $(cs107_0_word_games_binout)

cs107_0_ruth_aaron_test: cs107_0_ruth_aaron
	$(cs107_0_ruth_aaron_binout) 2
cs107_0_word_games_test: cs107_0_word_games
	echo "aria\n\0" | $(cs107_0_word_games_binout) $(cs107_0_words_file)

$(cs107_0_ruth_aaron_binout): $(cs107_root)/0/01-ruth-aaron/ruth-aaron-numbers.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(stdmath_lib_opt)

$(cs107_0_word_games_binout): $(cs107_root)/0/02-word-games/word-games.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
