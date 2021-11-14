#
# ./configure --has-cs107
#
# website: https://see.stanford.edu/Course/CS107
#
# 
# 1. numbering on Lecture number
# 2. handouts and assignments associate to Lecture number
# 3. common typedef in _cs107_.h
# 4. transfer all C++ code to pure C code.
#

ctl_git_src := 'https://github.com/glouw/ctl.git'
ctl_home := $(cs107_root)/ctl_home


cs107: cs107_0                                  \
       cs107_1                                  \
       cs107_2

cs107_test: cs107_0_test                        \
            cs107_1_test                        \
            cs107_2_test


# env
cs107_prefix := cs107
cs107_prefix_bin := $(bin_path)/$(cs107_prefix)

INC += $(nm_inc_opt)$(cs107_root) $(nm_inc_opt)$(root)/posix
INC += $(nm_inc_opt)$(ctl_home)/ctl


getopt_c :=
ifeq ($(NM_SYSTEM), WinNT)
	getopt_c := $(root)/posix/getopt.c
endif


ifeq ($(_MEMORY_), 1)
	CFLAGS += $(f_sanitize)
endif # end of _MEMORY_


$(ctl_home):
	git clone --depth=1 --branch=master $(ctl_git_src) $@


# 0
cs107_0_assn_01_binout := $(cs107_prefix_bin)_ruth_aaron$(bin_ext)
cs107_0_assn_02_binout := $(cs107_prefix_bin)_word_games$(bin_ext)
cs107_0_assn_02_file := $(CURDIR)/$(cs107_root)/0/assn/02/words

cs107_0: cs107_0_assn_01                        \
         cs107_0_assn_02
cs107_0_test: cs107_0_assn_01_test              \
              cs107_0_assn_02_test

cs107_0_assn_01: $(cs107_0_assn_01_binout)
cs107_0_assn_02: $(ctl_home) $(cs107_0_assn_02_binout)

cs107_0_assn_01_test: cs107_0_assn_01
	$(cs107_0_assn_01_binout) 2
cs107_0_assn_02_test: cs107_0_assn_02
	echo "aria\n\0" | $(cs107_0_assn_02_binout) $(cs107_0_assn_02_file)

$(cs107_0_assn_01_binout): $(cs107_root)/0/assn/01/ruth-aaron-numbers.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(stdmath_lib_opt)

$(cs107_0_assn_02_binout): $(cs107_root)/0/assn/02/word-games.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# 1
cs107_1:
cs107_1_test:

# 2
cs207_2_rsg_binout := $(bin_path)/$(cs207_prefix)_rsg$(bin_ext)

cs207_2: cs207_2_rsg
cs207_2_test: cs207_2_rsg_test



# eof
